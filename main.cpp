#include <cstddef>
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include "HashTable/HashTable.h"

// This file must be started with space and be without \n to do this, use translator.py
const char* Filename = "HamletFormated.txt";

static size_t fileSize (FILE* file);
static size_t readFile(FILE* openedFile, char** dest);
static char** splitStrIntoWords (char* str, const size_t strSize, const char splitSymbol, size_t* retBufSize);
void loadWordsIntoTable (char** buffer, const HashTable_t* hashTable, const size_t bufLength);
void makeCsvFile (char** listOfWords, const size_t numberOfWords, size_t (**hashFuncs) (Elem_t elem));

int main()
{
    FILE* fileptr = fopen (Filename, "r");
    assert (fileptr != nullptr);

    char* stringOfWords  = nullptr;
    size_t numberOfChars = readFile (fileptr, &stringOfWords);

    size_t numberOfWords = 0;
    char** listOfWords = splitStrIntoWords (stringOfWords, numberOfChars, ' ', &numberOfWords);

    const size_t numberOfLists = 80009;
    HashTable_t* hashTable = TableCtor (&crc_32Fast, numberOfLists);
    loadWordsIntoTable(listOfWords, hashTable, numberOfWords);

    //size_t (*HashFuncs[]) (Elem_t elem) = {&Always1Hash, &firstAsciiHash, &strlenHash, &asciiSumHash, &rolHash, &crc_32};
    //makeCsvFile (listOfWords, numberOfWords, HashFuncs);

#if 1
    const int numberOfTests = 1000;
    for (size_t j = 0; j < numberOfTests; j++)
    {
        for (size_t i = 0; i < numberOfWords; i++)
        {
            TableFind(hashTable, listOfWords[i]);
        }
    }
#endif
}

void makeCsvFile (char** listOfWords, const size_t numberOfWords, size_t (**hashFuncs) (Elem_t elem))
{
    const size_t numberOfLists = 1000;
    for (int i = 0; hashFuncs[i] != NULL; i++)
    {
        HashTable_t* hashTable = TableCtor(hashFuncs[i], numberOfLists);
        loadWordsIntoTable(listOfWords, hashTable, numberOfWords);
        getStatistics("Stats.csv", hashTable);
        TableDtor(hashTable);
    }
}

static size_t fileSize (FILE* file)
{
    assert (file != NULL);

    fseek(file, 0l, SEEK_END);
    size_t size = (size_t) ftell(file);
    fseek(file, 0l, SEEK_SET);

    return size;
}

static size_t readFile(FILE* openedFile, char** dest)
{
    assert (openedFile != NULL);
    assert (dest != NULL);

    size_t numberOfChars = fileSize(openedFile);

    *dest = (char*) calloc(numberOfChars + 1, sizeof(char));

    size_t charsReaded = fread((void*) *dest, sizeof(char), numberOfChars, openedFile); //
    if (charsReaded != numberOfChars)
        return 1;

    return numberOfChars;
}

char** splitStrIntoWords (char* str, const size_t strSize, const char splitSymbol, size_t* retBufSize)
{
    assert (str != NULL);
    const size_t constStrLength = 16;

    size_t maxBufSize = 100;
    char** retBuf = (char**) calloc (maxBufSize, sizeof(char*));
    assert (retBuf != nullptr);

    size_t curRetBufLength = 0;
    for (size_t i = 1; i < strSize; ++i)
    {
	if (str[i - 1] == splitSymbol)
	{
	    if (curRetBufLength > maxBufSize - 10 )
	    {
            maxBufSize *= 2;
            retBuf = (char**) realloc(retBuf, (maxBufSize) * sizeof (char*));
            assert (retBuf != nullptr);
	    }

	    retBuf[curRetBufLength] = (char*) calloc (constStrLength + 1, sizeof (char)); // + 1 is space for '\0'
	    assert (retBuf[curRetBufLength] != nullptr);
	    sscanf (str + i, "%s ", retBuf[curRetBufLength]);

	    curRetBufLength += 1;
	}
    }

    *retBufSize = curRetBufLength;
    return retBuf;
}

void loadWordsIntoTable (char** buffer, const HashTable_t* hashTable, const size_t bufLength)
{
    assert (buffer != NULL);
    assert (hashTable != NULL);

    for (size_t i = 0; i < bufLength; ++i)
    {
        tableAdd (hashTable, buffer[i]);
    }
}

