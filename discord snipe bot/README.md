# Discord Snipe Bot
Created by Sean Yang

## Description
This python script using discord.py records the latest deleted message in a discord server and upon being called using '!snipe' sends the deleted message back along with the server name of the sender and the EST (by default) timestamp

## Installation
1. Install libraries in requirements.txt
2. Setup your bot through discord.com/developers/applications
3. Copy your bot's token and create .env 'DISCORD_API_TOKEN'
4. Download files and run main.py
5. profit???

## Commands
- **!snipe** recalls the last deleted message
- **!snipeall** recalls ALL deleted messages
- **!snipen** recalls 'n' deleted messages where 'n' is an integer greater than 0 but not greater than 10
- **!clear** clears all logged messages

## Changelog
Initial upload: 2023/05/29
### Version 1.1 (2023/05/31)
- Reworked code to use a class and objects to store message data
- Bot can now remember much more than just the last deleted message
- New commands added to make use of new capabilities
- Bot token reader reworked to use relative file path by default
- Added **Commands** and **Updates** section to README

### Version 1.2 (2023/06/01)
- Reworked code to make it friendly for hosting
- Bot Token.txt has been removed as the program now uses env variable 'DISCORD_API_TOKEN'
- deletedEntry class has been replaced by better named messageEntry
- snipeBot.py has been replaced by main.py for friendlier hosting
- requirements.txt has been added for user and friendlier hosting
- limited list to only 10 remembered messages to reduce memory usage and fix !snipeall giving a wall of text
- **Updates** changed to **Changelog**

### Version 1.2.1 (2023/06/01)
- Bugfix: added check for requested recall length smaller than 10 but larger than current list size
- Bugfix: replaced 'chanel' with 'channel' in line 47 (oops)

### Version 1.3 (2023/06/23)
- Support for recalling edited messages added
- Support for recalling images and other attachments added
- Contributed by @BillJJ and edited by @ShurnYurnYang

## Version 1.4 (2023/06/30)
- **!clear** function added which clears all logged messages
- Bugfix: added error catch for calling a snipe when no messages have been logged

## Notes
- The UTC conversion timezone is EST by default, to change the timezone replace 'US/Eastern' with the pytz timezone of your choice
- Program has been rewritten to make it easy for hosting services to host (personally tested and hosted with railway)
- If multiple attachments from the same message are recalled, the attachment link will be retained in the recall message
