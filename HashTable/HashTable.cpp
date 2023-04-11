#include <cassert>

#include "HashTable.hpp"

void TableCtor(HashTable_t *hashTable, size_t (*HashFunc)(char *, size_t), size_t NumOfLists)
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


