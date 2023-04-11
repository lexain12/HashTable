#include "../List/AltList.h"


struct HashTable_t
{
    List_t** Table;
    size_t (*HashFunc)(Elem_t str);
    size_t NumOfLists;
};

//-------------Table functions --------------
void TableCtor   (HashTable_t* hashTable, size_t (*HashFunc)(Elem_t str), size_t NumOfLists);
void TableDtor   (HashTable_t* hashTable);
void tableAdd 	 (HashTable_t* hashTable, Elem_t element);
ListElement* TableFind (HashTable_t* hashTable, Elem_t element);
void TableDelete ();
void TableClear  ();
//-------------end of table functions -------

// ------------ Hash functions --------------
size_t Always1Hash    (Elem_t element);
size_t firstAsciiHash (Elem_t element);
size_t strlenHash     (Elem_t element);
// -------- end of hash functions -----------
