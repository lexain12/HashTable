#include <cstdio>
#include <cassert>
#include <cstdlib>
#include "HashTable/HashTable.hpp"

size_t fileSize (FILE* file);
int readFile(FILE* openedFile, char** dest);

int main()
{
    HashTable_t hashTable = {};
    const size_t numberOfLists = 100;
    TableCtor (&hashTable, &Always1Hash, numberOfLists);
    Elem_t str = "Hello";
    tableAdd(&hashTable, str);
    listDump(hashTable.Table[1], "Usual dump");
}

size_t fileSize (FILE* file)
{
    fseek(file, 0l, SEEK_END); 
    size_t size = (size_t) ftell(file); 
    fseek(file, 0l, SEEK_SET);

    return size;
}

int readFile(FILE* openedFile, char** dest)
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

    size_t retBufSize = 100;
    char** retBuf = (char**) calloc (retBufSize, sizeof(char*));
    assert (retBuf != nullptr);

    size_t curRetBufLength = 0;
    for (size_t i = 0; i < strSize; ++i)
    {
	if (str[i - 1] == ' ')
	{
	    if (curRetBufLength > retBufSize - 10 )
	    {
		retBuf = (char**) realloc(retBuf, (retBufSize + 20) * sizeof (char*));
		assert (retBuf != nullptr);
	    }

	    retBuf[curRetBufLength] = str + i;
	    curRetBufLength += 1;
	}
    }

    *retBufSize = curRetBufLength;
    return retBuf;
}

void LoadWordsIntoTable (char** buffer, HashTable_t* hashTable, size_t bufLengt)
{
    for (size_t i = 1; i < strLength; ++i)
    {

    }
}
