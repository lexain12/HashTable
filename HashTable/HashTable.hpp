#include "../List/AltList.h"


struct HashTable_t
{
    List_t** Table;
    size_t (*HashFunc)(char* str, size_t strLength);
    size_t NumOfLists;
};

void TableCtor   (HashTable_t* hashTable, size_t (*HashFunc)(char* str, size_t strLength), size_t NumOfLists);
void TableDtor   (HashTable_t* hashTable);
void TableClear  ();
void TableAdd    ();
void TableFind   ();
void TableDelete ();
