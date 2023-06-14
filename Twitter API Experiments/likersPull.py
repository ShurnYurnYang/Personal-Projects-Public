import tweepy

client = tweepy.Client('AAAAAAAAAAAAAAAAAAAAAHvJjAEAAAAA8kE9YxwMtiuH4%2BhQnkejcnKnqvE%3Ds2drXRc8MbwJm2h9DhIS3nASVhz8jA54f1JOy9TI8j6Hu4gHW2')

outputList = []

followers = client.get_liking_users(id=1589143860189728768) 

try:
    while True:
        followers = client.get_liking_users(id=1589143860189728768,pagination_token=followers.meta["next_token"])
        print(followers)
        for result in followers.data:
            if(result.name == 'a'):
                outputList.append(result.username)
except:
    f = open("likes.txt", "a")
    for index in outputList:
        try:
            f.write("%s\n" % index)
        except:
            f.write("%s\n" % "error: invalid characters")
    f.write("%s\n" % "next_token = " + followers.meta["next_token"])
    f.close()
    print("EXECUTION COMPLETE")
else:
    f = open("likes.txt", "a")
    for index in outputList:
        try:
            f.write("%s\n" % index)
        except:
            f.write("%s\n" % "error: invalid characters")
    f.close()
    print("EXECUTION COMPLETE: ALL DATA OBTAINED")