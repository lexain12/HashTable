#include <cstring>
#include <stdio.h>
#include <cassert>

#include "HashTable.hpp"

void TableCtor(HashTable_t *hashTable, size_t (*HashFunc)(Elem_t), size_t NumOfLists)
{
    assert (hashTable != nullptr);



    hashTable->NumOfLists = NumOfLists;
    hashTable->HashFunc   = HashFunc;
    hashTable->Table      = (List_t**) calloc(NumOfLists, sizeof(List_t*));

    for (size_t i = 0; i < NumOfLists; ++i)
    {
	List_t* list = (List_t*) calloc(1, sizeof(*list));
	listCtor(list);
	hashTable->Table[i] = list;
    }
}

void TableDtor(HashTable_t* hashTable)
{
    assert (hashTable != nullptr);

    for (size_t i = 0; i < hashTable->NumOfLists; ++i)
    {
	listDtor (hashTable->Table[i]);
    }

    hashTable->NumOfLists = 0;
    hashTable->HashFunc   = nullptr;
    free (hashTable->Table);
}

void tableAdd (HashTable_t* hashTable, Elem_t element)
{
    assert (hashTable != nullptr);
    assert (element   != nullptr);

    size_t ListNumber = (hashTable->HashFunc) (element) % hashTable->NumOfLists;
    listHeadAdd(hashTable->Table[ListNumber], element);
}

ListElement* TableFind(HashTable_t* hashTable, Elem_t element)
{
    assert (hashTable != nullptr);
    assert (element   != nullptr);

    size_t ListNumber = 0;
    ListNumber = (hashTable->HashFunc) (element) % hashTable->NumOfLists;

    return findElementByValue(hashTable->Table[ListNumber], element);
}

