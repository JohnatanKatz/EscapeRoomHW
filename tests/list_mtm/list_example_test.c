#include "test_utilities.h"
#include "../../list_mtm1.h"
//#include "../../list.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

static void printStringList (List list)
{
    char * iterator = (char *)listGetFirst(list);
    printf("\n");
    while (iterator)
    {
        printf("%s\n",iterator);
        iterator = listGetNext(list);
    }
}
static ListElement copyString(ListElement str){
	assert(str);
	char* copy = malloc(strlen(str)+1);
	return copy != NULL ? strcpy(copy, str) : NULL;
}

static void freeString(ListElement str){
	free(str);
}

static bool strBigger(char* s1, char* s2)
{
	return strcmp(s1,s2);
}

static bool isLongerThan(ListElement element,ListFilterKey number) {
	char* string = element;
    return strlen(string) > *(int*)number;
}

static bool testListCreate() {
	ASSERT_TEST(listCreate(NULL,NULL) == NULL);
	ASSERT_TEST(listCreate(NULL,NULL) == NULL);
	ASSERT_TEST(listCreate(copyString,NULL) == NULL);
	ASSERT_TEST(listCreate(NULL,freeString) == NULL);

	return true;
}
static bool testListFilter() {
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	List list = listCreate(copyString,freeString);
	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
	int key = 5;
	List filtered = listFilter(list,isLongerThan, &key);
	ASSERT_TEST(listGetSize(filtered) == 1);
	ASSERT_TEST(strcmp(listGetFirst(filtered),a[3])==0);
	listDestroy(list);
	listDestroy(filtered);
	return true;
}
static bool testListCopy() {
    char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
    List list = listCreate(copyString,freeString);
    for (int i=0;i <5; ++i){
        listInsertFirst(list,a[i]);
    }
    List new = listCopy(list);
    char *e1 = listGetFirst(list);
    char *e2 = listGetFirst(new);
    while(e1 && e2)
    {
        ASSERT_TEST(strcmp(e1,e2)==0);
        e1 = listGetNext(list);
        e2 = listGetNext(new);
    }
	return true;
}

static bool testListGetSize() {
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	List list = listCreate(copyString,freeString);
	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
	ASSERT_TEST(listGetSize(list) == 5);
	listDestroy(list);
	return true;
}

static bool testListGetFirst() {
    char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
    List list = listCreate(copyString,freeString);
    for (int i=0;i <5; ++i){
        listInsertFirst(list,a[i]);
    }
    listSort(list,strBigger);
    char *k = listGetFirst(list);
    printStringList(list);
    ASSERT_TEST(strcmp(k,"I")==0);
    listDestroy(list);
    return true;
}

static bool testListGetNext() {
    char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
    List list = listCreate(copyString,freeString);
    for (int i=0;i <5; ++i){
        listInsertFirst(list,a[i]);
    }
    listSort(list,strBigger);
    listDestroy(list);
	return true;
}

static bool testListInsertFirst() {
	return true;
}

static bool testListInsertLast() {
	return true;
}

static bool testListInsertBeforeCurrent() {
	return true;
}

static bool testListInsertAfterCurrent() {
	return true;
}

static bool testListRemoveCurrent() {
	return true;
}

static bool testListSort() {
    char* a[7] = {"aaa","bbb","NI","PI 123","hello mister fish","I","AAAa",
                  "aaaa"};
    List list = listCreate(copyString,freeString);
    for (int i=0;i <7; ++i){
        listInsertFirst(list,a[i]);
    }
    char *e = listGetFirst(list);
    listSort(list,strBigger);
    return true;
}

static bool testListClear() {
	return true;
}

static bool testListDestroy() {
	return true;
}

int main (int argv, char** arc){
	RUN_TEST(testListCreate);
	RUN_TEST(testListFilter);
	RUN_TEST(testListCopy);
	RUN_TEST(testListGetSize);
	RUN_TEST(testListGetFirst);
	RUN_TEST(testListGetNext);
	RUN_TEST(testListInsertFirst);
	RUN_TEST(testListInsertLast);
	RUN_TEST(testListInsertBeforeCurrent);
	RUN_TEST(testListInsertAfterCurrent);
	RUN_TEST(testListRemoveCurrent);
	RUN_TEST(testListSort);
	RUN_TEST(testListClear);
	RUN_TEST(testListDestroy);
	return 0;
}

