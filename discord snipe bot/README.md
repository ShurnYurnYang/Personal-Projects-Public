# Discord Snipe Bot
Created by Sean Yang

## Description
This python script using discord.py records the latest deleted message in a discord server and upon being called using '!snipe' sends the deleted message back along with the server name of the sender and the EST (by default) timestamp

## Installation
1. Install Python, discord.py, and pytz
2. Setup your bot through discord.com/developers/applications
3. Copy your bot's token and paste it into the Bot Token.txt
4. Download files and run snipeBot.py
5. profit???

## Commands
- **!snipe** recalls the last deleted message
- **!snipeall** recalls ALL deleted messages which MAY cause some problems
- **!snipen** recalls 'n' deleted messages where 'n' is an integer greater than 0)

## Updates
Initial upload: 2023/05/29
### Version 1.1 (2023/05/31)
- Reworked code to use a class and objects to store message data
- Bot can now remember much more than just the last deleted message
- New commands added to make use of new capabilities
- Bot token reader reworked to use relative file path by default
- Added **Commands** and **Updates** section to README

## Notes
- The UTC conversion timezone is EST by default, to change the timezone replace 'US/Eastern' with the pytz timezone of your choice
