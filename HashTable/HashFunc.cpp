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

size_t asciiSumHash (Elem_t element)
{
    size_t sum = 0;

    for (size_t index = 0; element[index] != '\0'; ++index)
    {
	sum += (unsigned long) element[index];
    }
    return sum;
}

size_t myRor(size_t num, size_t shift)
{
    return (num >> shift) | (num << (32 - shift));
}

unsigned int myRol(unsigned int num, unsigned int shift)
{
    return (num << shift) | (num >> (32 - shift));
}

size_t rolHash (Elem_t element)
{
    unsigned int mask  = 0;
    unsigned int index = 0;

    while (element[index])
    {
	mask = myRol(mask, 1) ^ (unsigned int) element[index];
	index += 1;
    }
    return mask;
}

size_t rorHash (Elem_t element)
{
    size_t mask  = 0;
    size_t index = 0;

    while (element[index])
    {
	mask = myRor(mask, 1) ^ (unsigned long) element[index];
	index += 1;
    }
    return mask;
}


