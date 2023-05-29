import discord #imports the discord.py library
import pytz #imports pytz for converting utc to est
from datetime import datetime #imports datetime and creates datetime object for converting 24hr to 12hr

intents = discord.Intents.default() #sets the intents to default
intents.message_content=True #gives the bot the permission to see message contents

client = discord.Client(intents=intents) #this is the client, it connects the bot to discord

@client.event #decorator to register an event. because the library is async, perform a callback which is a function called when something happens
async def on_ready(): #this function is called when the bot has finished logging in and setting things up
    print(f'We have logged in as {client.user}') #prints to console a message telling us that the bot has finished setting up and logging  in

@client.event
async def on_message_delete(deletedMessage): #this function is called when a message has been deleted | 'message' is the message that was deleted
    global cachedMessage #makes the variable global across all events
    cachedMessage = [] #intialize cached message array
    cachedMessage.insert(0, deletedMessage.content) #inserts the content of the message into index 0 of the array 
    cachedMessage.insert(1, deletedMessage.author.display_name) #inserts the server display name of the author into index 1 of the array
    cachedMessage.insert(2, datetime.strptime(deletedMessage.created_at.astimezone(pytz.timezone('US/Eastern')).strftime("%H:%M"), "%H:%M").strftime("%I:%M %p")) #inserts the time of message sent into index 2 of the array
    #^^^converts UTC to EST and 12hr | striptime().strftime converts 24hr to 12hr | astimezone(pytz.timezone()).strftime converts UTC to est and formatted string
        
@client.event
async def on_message(message): #this function is called when a message is sent
    global cachedMessage
    if message.content.startswith('!snipe'): #checks if the message is sent using the bot identifier command
        await message.channel.send('"' + cachedMessage[0] + '" sent by ' + cachedMessage[1] + ' at ' + cachedMessage[2]) #sends the cached message back

def readBotToken(filePath): #this function reads from a file defined by the variable filePath
    try: #try except block to catch errors
        with open(filePath, 'r') as file: #opens the filePath as 'read' and creates object file
            fileData = file.read() #sets fileData to the data from file.read
            return fileData #returns fileData
    except FileNotFoundError: #catches FileNotFoundError
        print(f"File '{filePath}' not found.") #prints to console the file not found with the file path
        return None #returns none
    
filePath = r"" #file path converted to raw string and backslashes doubled to avoid unicoode escape errors
readData = readBotToken(filePath) #runs the read function and sets readData variable to the read string

client.run(readData) #this runs the bot using the bot token using the readData variable as the bot token string