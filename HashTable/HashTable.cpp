#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <cassert>

#include "HashTable.h"

struct HashTable_t
{
    List_t* Table;
    size_t (*HashFunc)(Elem_t str);
    size_t NumOfLists;
};

HashTable_t* TableCtor(size_t (*HashFunc)(Elem_t), const size_t NumOfLists)
{
    HashTable_t* hashTable = (HashTable_t*) calloc(1, sizeof(*hashTable));
    assert (hashTable != nullptr);

    hashTable->NumOfLists = NumOfLists;
    hashTable->HashFunc   = HashFunc;
    hashTable->Table      = (List_t*) calloc(NumOfLists, sizeof(List_t));

    for (size_t i = 0; i < NumOfLists; ++i)
    {
        List_t *list = (List_t*) calloc(1, sizeof(List_t));
        listCtor(list);
        hashTable->Table[i] = *list;
    }
    return hashTable;
}

void TableDtor(HashTable_t* hashTable)
{
    assert (hashTable != nullptr);

    for (size_t i = 0; i < hashTable->NumOfLists; ++i)
    {
        listDtor (hashTable->Table + i);
    }

    free (hashTable->Table);
}

ListElement* tableAdd (const HashTable_t* hashTable, const Elem_t element)
{
    assert (hashTable != nullptr);
    assert (element   != nullptr);

    size_t ListNumber = (hashTable->HashFunc) (element) % hashTable->NumOfLists;
    return listHeadAdd(hashTable->Table + ListNumber, element);
}

ListElement* TableFind(const HashTable_t* hashTable, const Elem_t element)
{
    assert (hashTable != nullptr);
    assert (element   != nullptr);

     size_t ListNumber = (hashTable->HashFunc) (element) % hashTable->NumOfLists;

    return findElementByValue(hashTable->Table + ListNumber, element);
}

void getStatistics (const char* csvFileName, const HashTable_t* hashTable)
{
    assert (csvFileName != NULL);
    assert (hashTable != NULL);

    FILE* fileptr = fopen (csvFileName, "a");
    assert (fileptr != nullptr);

    for (size_t i = 0; i < hashTable->NumOfLists; ++i)
    {
	    fprintf (fileptr, "%lu ;", i);
    }
    fprintf (fileptr, "\n");

    for (size_t i = 0; i < hashTable->NumOfLists; ++i)
    {
	    fprintf (fileptr, "%lu ;", hashTable->Table[i].size);
    }
    fprintf (fileptr, "\n");

    fclose (fileptr);
}

