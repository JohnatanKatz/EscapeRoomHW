#include <stdio.h>
#include <malloc.h>
#include "list_mtm1.h"
#include <assert.h>

typedef struct iterator_t{
    ListElement element;
    struct iterator_t *nextElement;
} Iterator;

typedef struct list_t{
    int numOfElements;
    CopyListElement copyElement;
    FreeListElement freeElement;
    Iterator *firstElement;
    int placeOfCurrentElement;
};
static void printList(List list){
    Iterator *iterator = list->firstElement;
    printf("\n");
    int i = 1;
    while(iterator)
    {
        printf("%d Element: %s\n",i,(char*)iterator->element);
        iterator = iterator->nextElement;
        i++;
    }
}

static void printElement(void* element)
{
    printf("%s\n",(char*)element);
}

static ListElement listGetElement(List list, int numOfElement)
{
    if(!list || numOfElement < 1 || numOfElement > list->numOfElements)
        return NULL;
    Iterator *returnedElement = list->firstElement;
    for(int i = 1; i < numOfElement; i++)
        returnedElement = returnedElement->nextElement;
    return returnedElement->element;
}

static ListResult listInsertElement (List list, ListElement element,
                                     int numOfElement)
{
    if(!list)
        return LIST_NULL_ARGUMENT;
    if (numOfElement < 0 || numOfElement > list->numOfElements)
        return LIST_INVALID_CURRENT;
    Iterator *insertedElement = malloc(sizeof(*insertedElement));
    if (!insertedElement)
        return LIST_NULL_ARGUMENT;
    insertedElement->element = list->copyElement(element);
    if (!insertedElement->element)
        return LIST_NULL_ARGUMENT;
    Iterator *iteratorElement = list->firstElement;

    if(numOfElement == 0)
    {
        insertedElement->nextElement = list->firstElement;
        list->firstElement = insertedElement;
    }
    else{
        for(int i = 1; i < numOfElement; i++)
            iteratorElement = iteratorElement->nextElement;
        insertedElement->nextElement = iteratorElement->nextElement;
        iteratorElement->nextElement = insertedElement;
    }
    list->numOfElements++;
    if(list->placeOfCurrentElement > numOfElement)
        list->placeOfCurrentElement++;
    return LIST_SUCCESS;
}

static ListResult listRemoveElement (List list, int numOfElement)
{
    if(!list)
        return LIST_NULL_ARGUMENT;
    if (numOfElement < 1 || numOfElement > list->numOfElements)
        return LIST_INVALID_CURRENT;

    Iterator *iteratorElement = list->firstElement;
    Iterator *elementToFree;

    if(numOfElement == 1)
    {
        elementToFree = list->firstElement;
        list->firstElement = list->firstElement->nextElement;
        list->freeElement(elementToFree->element);
        elementToFree->nextElement = NULL;
        free(elementToFree);
    }
    else{
        for(int i = 1; i < numOfElement - 1; i++)
            iteratorElement = iteratorElement->nextElement;

        elementToFree = iteratorElement->nextElement;
        iteratorElement->nextElement = elementToFree->nextElement;
        list->freeElement(elementToFree->element);
        elementToFree->nextElement = NULL;
        free(elementToFree);
    }
    list->numOfElements--;
    if(list->placeOfCurrentElement > numOfElement)
        list->placeOfCurrentElement--;
    return LIST_SUCCESS;
}

List listCreate(CopyListElement copyElement, FreeListElement freeElement) {
    if (!copyElement || !freeElement)
        return NULL;
    List list = malloc(sizeof(*list));
    if (!list)
        return NULL;
    list->numOfElements = 0;
    list->copyElement = copyElement;
    list->freeElement = freeElement;
    list->firstElement = NULL;
    list->placeOfCurrentElement = 0;
    return list;
}

List listCopy(List list)
{
    if(!list)
        return NULL;
    List newList = listCreate(list->copyElement, list->freeElement);
    newList->numOfElements = list->numOfElements;
    newList->placeOfCurrentElement = list->placeOfCurrentElement;
    Iterator *oldElement = list->firstElement;
    Iterator *newElement;
    Iterator *nextNewElement;
    Iterator *nextOldElement;
    if(list->numOfElements > 0) {
        newElement = malloc(sizeof(*newElement));
        if (!newElement)
            return NULL;
        newList->firstElement = newElement;
        newElement->element = list->copyElement(oldElement->element);
        if(!newElement->element)
            return NULL;
        for (int i = 1; i < list->numOfElements; i++) {
            newElement->nextElement = malloc(sizeof(*newElement->nextElement));
            if (!newElement->nextElement)
                return NULL;
            nextNewElement = newElement->nextElement;
            nextOldElement = oldElement->nextElement;
            nextNewElement->element =list->copyElement(nextOldElement->element);
            if(!nextNewElement->element)
                return NULL;
            newElement = nextNewElement;
            oldElement = nextOldElement;
        }
        newElement->nextElement = NULL;
    }
    return newList;
}

int listGetSize(List list)
{
    if(!list)
        return -1;
    return list->numOfElements;
}

ListElement listGetFirst(List list){
    if(!list || !list->firstElement)
        return NULL;
    list->placeOfCurrentElement = 1;
    return listGetElement(list,1);
}

ListElement listGetNext(List list)
{
    if(!list || !list->firstElement)
        return NULL;
    if(list->placeOfCurrentElement >= list->numOfElements ||
            list->placeOfCurrentElement < 1)
        return NULL;
    list->placeOfCurrentElement++;
    return listGetElement(list,list->placeOfCurrentElement);
}

ListElement listGetCurrent(List list)
{
    if(!list || !list->firstElement)
        return NULL;
    if(list->placeOfCurrentElement > list->numOfElements ||
       list->placeOfCurrentElement < 1)
        return NULL;
    return listGetElement(list,list->placeOfCurrentElement);
}

ListResult listInsertFirst(List list, ListElement element){
    if(!list || !element)
        return LIST_NULL_ARGUMENT;
    return listInsertElement(list,element,0);
}

ListResult listInsertLast(List list, ListElement element){
    if(!list || !element)
        return LIST_NULL_ARGUMENT;
    return listInsertElement(list,element,list->numOfElements);
}

ListResult listInsertBeforeCurrent(List list, ListElement element){
    if(!list || !element)
        return LIST_NULL_ARGUMENT;
    return listInsertElement(list,element,list->placeOfCurrentElement-1);
}

ListResult listInsertAfterCurrent(List list, ListElement element){
    if(!list || !element)
        return LIST_NULL_ARGUMENT;
    return listInsertElement(list,element,list->placeOfCurrentElement);
}

ListResult listRemoveCurrent(List list){
    if(!list)
        return LIST_NULL_ARGUMENT;
    int place_of_current_element =list->placeOfCurrentElement;
    list->placeOfCurrentElement =0;
    return listRemoveElement(list,place_of_current_element);
}

ListResult listSort(List list, CompareListElements compareElement){
    if(!list || !compareElement)
        return LIST_NULL_ARGUMENT;
    ListElement currentElement;
    ListElement nextElement;
    for(int i = list->numOfElements; i>1; i--) {
        for (int j = 1; j < i; j++) {
            currentElement = listGetElement(list, j);
            nextElement = listGetElement(list, j+1);
            if (compareElement(currentElement,nextElement)>0)
            {
                listRemoveElement(list,j);
                listInsertElement(list,nextElement,j-1);
                listRemoveElement(list,j+1);
                listInsertElement(list,currentElement,j);
            }
        }
    }
    return LIST_SUCCESS;
}

List listFilter(List list, FilterListElement filterElement, ListFilterKey key){
    if(!list,!filterElement,!key)
        return NULL;
    List newList = listCopy(list);
    for(int i = 1;i <= newList->numOfElements; i++)
        if (!filterElement(listGetElement(newList, i), key)) {
            listRemoveElement(newList, i);
            i--;
        }
    newList->placeOfCurrentElement = 1;
    return newList;
}

ListResult listClear(List list){
    if(!list)
        return LIST_NULL_ARGUMENT;
    while(list->firstElement)
        listRemoveElement(list,1);
    list->placeOfCurrentElement = 0;
    assert(list->numOfElements == 0);
    list->numOfElements = 0;
    return LIST_SUCCESS;
}

void listDestroy(List list){
    listClear(list);
    list->copyElement = NULL;
    list->freeElement = NULL;
    free(list);
}