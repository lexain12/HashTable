#include <cstring>

#include "HashTable.hpp"

size_t Always1Hash (Elem_t element)
{
    return 1;
}

size_t firstAsciiHash (Elem_t element)
{
    return element[0];
}

size_t strlenHash (Elem_t element)
{
    return strlen(element);
}

