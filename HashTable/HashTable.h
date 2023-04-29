#pragma once
#include "../List/AltList.h"

struct HashTable_t;

//-------------Table functions --------------
void getStatistics (const char* csvFileName, const HashTable_t* hashTable);
HashTable_t* TableCtor(size_t (*HashFunc)(Elem_t), const size_t NumOfLists);
void TableDtor   (HashTable_t* hashTable);
ListElement* tableAdd (const HashTable_t* hashTable, const Elem_t element);
ListElement* TableFind(const HashTable_t* hashTable, const Elem_t element);
void TableDelete ();
void TableClear  ();
//-------------end of table functions -------

// ------------ Hash functions --------------
size_t Always1Hash    (Elem_t element);
size_t firstAsciiHash (Elem_t element);
size_t strlenHash     (Elem_t element);
size_t asciiSumHash   (Elem_t element);
size_t rorHash        (Elem_t element);
size_t rolHash        (Elem_t element);
size_t crc_32         (Elem_t element);
size_t crc_32Fast     (Elem_t element);
// -------- end of hash functions -----------
