import discord #imports the discord.py library
import pytz #imports pytz for converting utc to est
from messageEntry import messageEntry
from datetime import datetime #imports datetime and creates datetime object for converting 24hr to 12hr
import os #imports functions for working with environment variables

intents = discord.Intents.default() #sets the intents to default
intents.message_content=True #gives the bot the permission to see message contents

client = discord.Client(intents=intents) #this is the client, it connects the bot to discord

cachedMessage = [] #intialize cached message array

@client.event #decorator to register an event. because the library is async, perform a callback which is a function called when something happens
async def on_ready(): #this function is called when the bot has finished logging in and setting things up
    print(f'We have logged in as {client.user}') #prints to console a message telling us that the bot has finished setting up and logging  in

@client.event
async def on_message_delete(deletedMessage): #this function is called when a message has been deleted | 'message' is the message that was deleted
    global cachedMessage #makes the variable global across all events
    entry = messageEntry(deletedMessage.content, deletedMessage.author.display_name, datetime.strptime(deletedMessage.created_at.astimezone(pytz.timezone('US/Eastern')).strftime("%H:%M"), "%H:%M").strftime("%I:%M %p"))
    if len(cachedMessage) >= 10: #this block ensures the list size is max 10         #^^^converts UTC to EST and 12hr | striptime().strftime converts 24hr to 12hr | astimezone(pytz.timezone()).strftime converts UTC to est and formatted string             
        del cachedMessage[0]  #deletes the first element (oldest remembered message)
    cachedMessage.append(entry) #adds entry to the end of the list                                         

@client.event
async def on_message(message): #this function is called when a message is sent
    global cachedMessage
    if message.content == '!snipe': #checks if the message is sent using the bot identifier command
        await message.channel.send(cachedMessage[-1].returnString()) #sends the cached message back
    elif message.content == '!snipeall': #checks for the '!snipeall' command
        for i in cachedMessage: #for loop iterates through the array and outputs ALL delted messages
            await message.channel.send(i.returnString())
    elif message.content.startswith('!snipe'): #checks for all other commands beginning with '!snipe'
        selected = message.content[6:len(message.content)] #substrings the command with all characters after '!snipe'
        try: #catches error from cast to int
            selected = int(selected) 
            if selected <= 0: #prevents 0 or negative recall length
                await message.channel.send("Sorry, you seem to have selected an unrecognized recall length")
            elif selected > 10 or selected > len(cachedMessage): #prevents recall length being greater than 10 (max array length) or greater than the current array length
                await message.channel.send("Sorry, I don't remember that far back!")
            else: ##accepted
                try: 
                    for i in range(len(cachedMessage)-(selected),len(cachedMessage)): #END VALUE OF RANGE IS EXCLUSIVE
                        await message.channel.send(cachedMessage[i].returnString())  
                except IndexError: #SHOULD NOT BE POSSIBLE
                    message.chanel.send("error???")
        except ValueError: ##catches error if the user enters non number
            await message.channel.send("Error: integer not detected directly after '!snipe'")

readData = os.environ['DISCORD_API_TOKEN'] #runs the read function and sets readData variable to the read string

client.run(readData) #this runs the bot using the bot token using the readData variable as the bot token string