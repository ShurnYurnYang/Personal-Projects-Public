class messageEntry:
    def __init__(self, message, author, time):
        self.attributes = [message, author, time]

    def returnString(self):
        return '"' + self.attributes[0] + '" sent by ' + self.attributes[1] + ' at ' + self.attributes[2]