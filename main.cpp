#include <cstdio>
#include <cassert>
#include <cstdlib>
#include "HashTable/HashTable.hpp"

// This file must be started with space and be without \n to do this, use translator.py
const char*  Filename     = "HamletFormated.txt";

size_t fileSize (FILE* file);
size_t readFile(FILE* openedFile, char** dest);
char** splitStrIntoWords (char* str, size_t strSize, char splitSymbol, size_t* retBufSize);
void loadWordsIntoTable (char** buffer, HashTable_t* hashTable, size_t bufLength);
void getStatistics (const char* csvFileName, HashTable_t* hashTable);

int main()
{
    HashTable_t hashTable = {};
    const size_t numberOfLists = 100;
    TableCtor (&hashTable, &Always1Hash, numberOfLists);

    FILE* fileptr = fopen (Filename, "r");
    assert (fileptr != nullptr);

    char* stringOfWords  = nullptr;
    size_t numberOfChars = readFile (fileptr, &stringOfWords);

    size_t numberOfWords = 0;
    char** listOfWords = splitStrIntoWords (stringOfWords, numberOfChars, ' ', &numberOfWords);

    loadWordsIntoTable (listOfWords, &hashTable, numberOfWords);
    getStatistics ("Stats.csv", &hashTable);

    HashTable_t hashTable1 = {};
    TableCtor (&hashTable1, &firstAsciiHash, numberOfLists);
    loadWordsIntoTable (listOfWords, &hashTable1, numberOfWords);
    getStatistics ("Stats.csv", &hashTable1);

    HashTable_t hashTable2 = {};
    TableCtor (&hashTable2, &strlenHash, numberOfLists);
    loadWordsIntoTable (listOfWords, &hashTable2, numberOfWords);
    getStatistics ("Stats.csv", &hashTable2);

    HashTable_t hashTable3 = {};
    TableCtor (&hashTable3, &rolHash, numberOfLists);
    loadWordsIntoTable (listOfWords, &hashTable3, numberOfWords);
    getStatistics ("Stats.csv", &hashTable3);

    HashTable_t hashTable4 = {};
    TableCtor (&hashTable4, &asciiSumHash, numberOfLists);
    loadWordsIntoTable (listOfWords, &hashTable4, numberOfWords);
    getStatistics ("Stats.csv", &hashTable4);
}

size_t fileSize (FILE* file)
{
    fseek(file, 0l, SEEK_END); 
    size_t size = (size_t) ftell(file); 
    fseek(file, 0l, SEEK_SET);

    return size;
}

size_t readFile(FILE* openedFile, char** dest)
{
    assert (openedFile != nullptr);

    size_t numberOfChars = fileSize(openedFile);

    printf("filesize = %lu\n", numberOfChars);

    *dest = (char*) calloc(numberOfChars + 1, sizeof(char));

    size_t charsReaded = fread((void*) *dest, sizeof(char), numberOfChars, openedFile); // 
    if (charsReaded != numberOfChars)
        return 1;
    
    return numberOfChars;
}

char** splitStrIntoWords (char* str, size_t strSize, char splitSymbol, size_t* retBufSize)
{
    assert (str != nullptr);

    size_t maxBufSize = 100;
    char** retBuf = (char**) calloc (maxBufSize, sizeof(char*));
    assert (retBuf != nullptr);

    size_t curRetBufLength = 0;
    for (size_t i = 0; i < strSize; ++i)
    {
	if (str[i - 1] == splitSymbol)
	{
	    if (curRetBufLength > maxBufSize - 10 )
	    {
		retBuf = (char**) realloc(retBuf, (maxBufSize + 20) * sizeof (char*));
		assert (retBuf != nullptr);
	    }

	    int charsReaded = 0;
	    sscanf (str + i, "%*s%n ", &charsReaded);

	    retBuf[curRetBufLength] = (char*) calloc ((size_t) charsReaded, sizeof (char));
	    assert (retBuf[curRetBufLength] != nullptr);
	    sscanf (str + i, "%s ", retBuf[curRetBufLength]);

	    curRetBufLength += 1;
	}
    }

    *retBufSize = curRetBufLength;
    return retBuf;
}

void loadWordsIntoTable (char** buffer, HashTable_t* hashTable, size_t bufLength)
{
    for (size_t i = 0; i < bufLength; ++i)
    {
	tableAdd (hashTable, buffer[i]);
    }
}

void getStatistics (const char* csvFileName, HashTable_t* hashTable)
{
    FILE* fileptr = fopen (csvFileName, "a");
    assert (fileptr != nullptr);

    for (size_t i = 0; i < hashTable->NumOfLists; ++i)
    {
	fprintf (fileptr, "%lu ;", hashTable->Table[i]->size - 1); // -1 because list has shadow element
    }
    fprintf (fileptr, "\n");

    fclose (fileptr);
}

