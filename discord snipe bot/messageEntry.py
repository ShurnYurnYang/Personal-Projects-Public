class messageEntry:
    def __init__(self, message, author, time, urlList, hasImage=False):
        self.attributes = [message, author, time, urlList, hasImage]

    def __str__(self):
        if self.attributes[4]:
            if len(self.attributes[0]) == 0:
                return '\n'.join(self.attributes[3]) #return only images and no text
            else:
                return '"' + self.attributes[0] + '" sent by ' + self.attributes[1] + ' at ' + self.attributes[2] + '\n' + '\n'.join(self.attributes[3]) #return images and text
            
        return '"' + self.attributes[0] + '" sent by ' + self.attributes[1] + ' at ' + self.attributes[2] #default return if no images