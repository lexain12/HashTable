#include "HashTable/HashTable.hpp"

int main()
{
    HashTable_t hashTable = {};
    const size_t numberOfLists = 100;
    TableCtor (&hashTable, &Always1Hash, numberOfLists);
}
