//--------------------------------------------------------
// This file is my old code, that had a lot of warnings,
// but I checked them
#include <cstdint>
#include <cstdlib>
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
#pragma GCC diagnostic ignored "-Wparentheses"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
//--------------------------------------------------------

#include <cassert>
#include <stdio.h>
#include <stdarg.h>
#include <cstddef>
#include <cstring>
#include <immintrin.h>
#include <emmintrin.h>

#include "AltList.h"

char* Poison = nullptr;

extern FILE* LOGFILEPTR;

int listCtor (List_t* list)
{
    assert (list != nullptr);

    int errors = noErrors;
    ListElement* newDataPtr = (ListElement*) calloc (1, sizeof(*newDataPtr));

    if (newDataPtr == nullptr)
        return errors |= listptrError;

    list->nullElement = newDataPtr;
    list->size        = 0;
    list->status      = noErrors;

    list->nullElement->element = Poison;
    list->nullElement->prevElementInd = newDataPtr;
    list->nullElement->nextElementInd = newDataPtr;

    if (list->status |= listVerify (list))
    {
        listDump (list, "Error ctor\n");
    }

    return noErrors;
}

void listDtor (List_t* list)
{
    assert (list != nullptr);
    ListElement* cur  = list->nullElement;
    for (size_t i = 0; i < list->size; i++)
    {
        ListElement* next = cur->nextElementInd;
        free(cur);
        cur = next;
    }
}

ListElement* listInsertPrev (List_t* list, ListElement* anchorElement, Elem_t element)
{
    assert (list != nullptr);

    if (list->status |= listVerify (list))
    {
        listDump (list, "Error in listInsertPrev function, element: " Format_ ", before: %lu\n", element, anchorElement);
    }

    ListElement* newListElement = (ListElement*) calloc (1, sizeof (ListElement));
    assert (newListElement != nullptr);

    if (newListElement == nullptr)
        return nullptr;

    newListElement->element = element;
    newListElement->prevElementInd = anchorElement->prevElementInd;
    newListElement->nextElementInd = anchorElement;

    anchorElement->prevElementInd->nextElementInd = newListElement;
    anchorElement->prevElementInd = newListElement;

    list->size += 1;

    return newListElement;
}

ListElement* listHeadAdd (List_t* list, Elem_t element)
{
    assert (list != nullptr);

    return listInsertPrev (list, list->nullElement->nextElementInd, element);
}

ListElement* listTailAdd (List_t* list, Elem_t element)
{
    assert (list != nullptr);

    return listInsertAfter (list, list->nullElement->prevElementInd, element);
}

ListElement* listInsertAfter (List_t* list, ListElement* anchorIndex, Elem_t element)
{
    assert (list != nullptr);
    if (list->status |= listVerify (list))
    {
        listDump (list, "Error in listInsertAfter function, element: " Format_ ", before: %lu\n", element, anchorIndex);
    }

    return listInsertPrev (list, anchorIndex->nextElementInd, element);
}

void myGraph (List_t* list)
{
    assert (list != nullptr);

    if (list->status |= listVerify (list))
    {
        listDump (list, "Error in myGraph function, element: \n");
    }

    FILE* GraphFilePtr = fopen(GraphFile, "w");
    assert (GraphFilePtr != nullptr);
#define dumpprint(...) fprintf(GraphFilePtr, __VA_ARGS__);

    dumpprint ("digraph MyGraph {\n")
    dumpprint ("    node [color=black, shape=box, style=\"rounded, filled\"];\n")
    dumpprint ("    rankdir=LR;\n")
    dumpprint ("    size [fillcolor=\"#74c2f2\", label=\"size = %lu\"];\n", list->size)

    dumpprint ("    node[color=black, shape=record, style=\"rounded, filled\"];\n")
    dumpprint ("    edge[style = invis, constraint=true];\n")

    dumpprint ("    nd%p [fillcolor=\"#a1a1a1\", label=\"node %p | value: Poison | { <p> prev: %p | <n> next: %p  }\"];\n",
                list->nullElement, list->nullElement, list->nullElement->prevElementInd, list->nullElement->nextElementInd)

    ListElement* curElement = list->nullElement->nextElementInd;

    for (size_t index = 1; index <= list->size; ++index)
    {

        dumpprint ("    nd%p [", curElement)

        if (curElement->element == Poison)
            dumpprint ("fillcolor =\"#80f293\", label =\"node %p | value: Poison", curElement)

        else if (curElement == list->nullElement->nextElementInd)
            dumpprint ("fillcolor =\"#fcf400\", label =\"node %p | value:" Format_ , curElement, curElement->element)

        else if (curElement == list->nullElement->prevElementInd)
            dumpprint ("fillcolor =\"#fc8b00\", label =\"node %p | value:" Format_ , curElement, curElement->element)

        else
        {
            dumpprint ("fillcolor =\"#f280f0\", label =\"node %p | value:" Format_ , curElement, curElement->element)
        }
        dumpprint (" | { <p> prev: %p | <n> next: %p}\"];", curElement->prevElementInd, curElement->nextElementInd)
        dumpprint ("    nd%p -> nd%p;\n", curElement->prevElementInd, curElement)

        curElement = curElement->nextElementInd;
    }

    dumpprint("    edge [style=solid, constraint=false];\n")

        curElement = list->nullElement;

    for (size_t index = 0; index <= list->size; ++index)
    {
        if (curElement->prevElementInd != nullptr)
        {
            dumpprint("    nd%p -> nd%p;\n", curElement, curElement->prevElementInd);
        }
        dumpprint("    nd%p -> nd%p;\n\n", curElement, curElement->nextElementInd);

        curElement = curElement->nextElementInd;
    }

    dumpprint ("    edge [style = bold, constraint=false];\n")

    dumpprint ("}\n")

    fclose(GraphFilePtr);
    static int picVersion = 0;

    char buf[100] = "";
    sprintf(buf, "dot -Tsvg GraphFileAlt.txt > src/pic%d.svg", picVersion);
    picVersion++;

    system (buf);
#undef dumpprint
}

void listDump (List_t* list, const char* str, ...)
{
    assert(list != nullptr);

    va_list argPtr = {};
    va_start (argPtr, str);

    fprintf(LOGFILEPTR, "<hr>\n");

    fprintf (LOGFILEPTR, "<h2>");
    vfprintf (LOGFILEPTR, str, argPtr);
    fprintf (LOGFILEPTR, "</h2>\n");

    fprintf (LOGFILEPTR, "<h2>Status:</h2>\n");

if (list->status)
    {
        fprintf(LOGFILEPTR, "<h2>(ERROR: %d)</h2>\n", list->status);
        fprintf(LOGFILEPTR, "-----------------Errors-------------------\n");
    #define ErrorPrint(error, text)                                       \
                if (error & list->status)                                       \
                {                                                         \
                    fprintf(LOGFILEPTR, "ERROR ["#error"] " #text "\n"); \
                }

        ErrorPrint(noErrors,             No errors);
        ErrorPrint(listptrError,          Wrong ptr on structure with list);
        ErrorPrint(capacityError,        Wrong capacity);
        ErrorPrint(dataError,            No pointer on data (list with elements));
        ErrorPrint(sizeError,            Bad Size of list);
        ErrorPrint(sizeAndCapacityError, Size bigger than capacity => problem with list size)
        ErrorPrint(listResizeUpError,    Cannot resizeUp the list);
        ErrorPrint(memAllocError,        Cannot allocate memory);
        ErrorPrint(listResizeDownError,  Cannot resize down);
        fprintf(LOGFILEPTR, "-------------End-of-errors----------------\n");
    }
    else
        fprintf(LOGFILEPTR, "<h2> (no errors) </h2>\n");

    myGraph (list);
    static int picVersion = 0;
    fprintf(LOGFILEPTR, "<img src = \"src/pic%d.svg\"/>\n", picVersion++);

    return;
}


void listDelete (List_t* list, ListElement* anchorElement)
{
    assert (list != nullptr);

    if (list->status |= listVerify (list))
    {
        listDump (list, "Error in listDelete function, delete %lu element \n", anchorElement);
    }

    if (anchorElement->prevElementInd == nullptr)
    {
        listDump (list, "Error in listDelete function, can't delete element %lu \n", anchorElement);
        return;
    }

    anchorElement->prevElementInd->nextElementInd = anchorElement->nextElementInd;
    anchorElement->nextElementInd->prevElementInd = anchorElement->prevElementInd;

    anchorElement->element        = Poison;
    anchorElement->nextElementInd = nullptr;
    anchorElement->prevElementInd = nullptr;

    list->size--;
    free (anchorElement);

    if (list->status |= listVerify (list))
    {
        listDump (list, "Error after listDelete function, delete %lu element \n", anchorElement);
    }

    return;
}

int listVerify (List_t* list)
{
    assert (list != nullptr);

    size_t epsiloh = SIZE_MAX;

    if (list)
    {
        if (list->size         > epsiloh)
            list->status |= sizeError;

        if (!list->nullElement)
            return list->status |= dataError;
    }
    else
        list->status |= listptrError;

    return list->status;
}

size_t logicalNumberToPhysical (List_t* list, ListElement* anchorElement)
{
    assert (list != nullptr);

    if (list->status |= listVerify (list))
    {
        listDump (list, "Error in logicalNumberToPhysical function, logicalNumber %lu\n", anchorElement);
    }

    size_t index  = 0;
    ListElement* curElement = list->nullElement->nextElementInd;
    while (curElement != anchorElement)
    {
        curElement = curElement->nextElementInd;
        index++;
    }

    if (list->status |= listVerify (list))
    {
        listDump (list, "Error after logicalNumberToPhysical function, logicalNumber %lu\n", anchorElement);
    }

    return index;
}

static inline int fastStrCmp(char* str1, char* str2)
{

    const int EqualConst = 0xFFFF;
    __m128i Str1 = *((__m128i*) str1);
    __m128i Str2 = *((__m128i*) str2);


    __m128i result = _mm_cmpeq_epi32 (Str1, Str2);

    if (_mm_movemask_epi8 (result) == EqualConst)
        return 0;

    return 1;
}

#if 0
ListElement* findElementByValue (List_t* list, Elem_t value)
{

    ListElement* curElement = list->nullElement->nextElementInd;

    size_t i = 0;
    for (; i < list->size - 1;)
    {
        curElement = curElement->nextElementInd;
        if (fastStrCmp(curElement->element, value) == 0)
        {
            break;
        }

	i++;
    }

    if (i == list->size - 2)
    {
        return nullptr;
    }

    return curElement;
}

#endif
