import time
startTime = time.time()

fileOneName = "output.txt"
fileTwoName = "output3.txt"

setOne = []
setTwo = []

with open(fileOneName) as fileOne:
    for lineOne in fileOne.readlines():
        if(lineOne.strip() != "error: invalid characters"):
            setOne.append(lineOne[0:lineOne.index('###')])
      

with open(fileTwoName) as fileTwo:
    for lineTwo in fileTwo.readlines():
        if(lineTwo.strip() != "error: invalid characters"):
            setTwo.append(lineTwo[0:lineTwo.index('###')])

matchingCharacters = []

for checkOne in setOne:
    for checkTwo in setTwo:
        if checkOne == checkTwo:
            matchingCharacters.append(checkOne)

for output in matchingCharacters: 
    print("%s\n" % output)

print("DONE\n")
print("Complete in: {0}s".format(round(time.time() - startTime), 4))