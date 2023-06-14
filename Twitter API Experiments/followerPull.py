import tweepy

client = tweepy.Client('AAAAAAAAAAAAAAAAAAAAAHvJjAEAAAAA8kE9YxwMtiuH4%2BhQnkejcnKnqvE%3Ds2drXRc8MbwJm2h9DhIS3nASVhz8jA54f1JOy9TI8j6Hu4gHW2',wait_on_rate_limit=True)

outputList = []

file = "output3.txt"

userID = 1545643138223443969

##nextToken = 

followers = client.get_users_followers(id=userID,max_results=1000,user_fields=["protected"]) 

try:
    while True:
        followers = client.get_users_followers(id=userID,max_results=1000,pagination_token=followers.meta["next_token"],user_fields=["protected"])
        for result in followers.data:
            if(result.protected == True):
                outputList.append(str(result.id) + "###" + result.username + '|' + result.name)
        ##print(followers)
except KeyError:
    ##print(*outputList, sep = "\n")
    f = open(file, "a")
    for index in outputList:
        try:
            f.write("%s\n" % index)
        except:
            f.write("%s\n" % "error: invalid characters")
    f.close()
    print("EXECUTION COMPLETE: NO MORE KEYS")
except Exception as e:
    f = open(file, "a")
    for index in outputList:
        try:
            f.write("%s\n" % index)
        except:
            f.write("%s\n" % "error: invalid characters")
    f.write("%s\n" % "next_token = " + followers.meta["next_token"])
    f.close()
    print("EXECUTION COMPLETE: OTHER ERROR")
    print(e)