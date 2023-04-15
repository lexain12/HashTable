
srcFile = open("HamletOrig.txt", "r+")
destFile = open("HamletFormated.txt", "w")

def deletePunctuation (str):
    returnString = ""

    for i in str:
        if i.isalpha():
            returnString += i


    return returnString

words = set()
for line in srcFile:
    wordList = line.split()
    for word in wordList:
        if len(word) <= 16:
            if word not in words:
                words.add (word)
                destFile.write (deletePunctuation (word))
                destFile.write (" ")

