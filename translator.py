
srcFile = open("HamletOrig.txt", "r+")
destFile = open("HamletFormated.txt", "w")

def deletePunctuation (str):
    returnString = ""

    for i in str:
        if i.isalpha():
            returnString += i


    return returnString

for line in srcFile:
    wordList = line.split()
    for word in wordList:
        destFile.write (deletePunctuation (word))
        destFile.write (" ")

