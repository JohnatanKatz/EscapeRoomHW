#include <stdio.h>
#include <string.h>
#include "set.h"
#include "list.h"
#include <malloc.h>
#include <stdlib.h>

typedef struct kosta_t{
    int a;
    int b;
} *Num;

int compareNum(Num num1, Num num2)
{
    if(num1->a-num2->a != 0)
        return  num1->a-num2->a;
    else
        return num1->b-num2->b;
}

ListElement copyNum(ListElement num_in){
    Num num = num_in;
    Num num_return = malloc(sizeof(*num_return));
    num_return->a = num->a;
    num_return->b = num->b;
    return num_return;
}

void  freeNum(ListElement num_in){
    Num num = num_in;
    free(num);
}

int main()
{
    /*Num kosta = malloc(sizeof(*kosta)*10);
    kosta[0].a = 111;
    kosta[0].b = 607;
    kosta[1].a = 908;
    kosta[1].b = 347;
    kosta[2].a = 908;
    kosta[2].b = 470;
    kosta[3].a = 215;
    kosta[3].b = 60;
    kosta[4].a = 111;
    kosta[4].b = 423;
    kosta[5].a = 908;
    kosta[5].b = 949;
    kosta[6].a = 111;
    kosta[6].b = 493;
    kosta[7].a = 908;
    kosta[7].b = 95;
    kosta[8].a = 111;
    kosta[8].b = 210;
    kosta[9].a = 215;
    kosta[9].b = 918;

    List list = listCreate(copyNum,freeNum);
    for(int i = 0; i< 10; i++)
        listInsertFirst(list,&(kosta[i]));
    listSort(list,compareNum);
    LIST_FOREACH(Num,num,list){
        printf("%d : %d\n",num->a,num->b);
    }
    return 0;*/
}