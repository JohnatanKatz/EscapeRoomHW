#include <stdio.h>
#include <string.h>
#include <malloc.h>

int binarySearchHelp(void** array,void* element,int array_size,int
(*compFunction) (void*,void*), int countPlace)
{
    if(array_size == 1) {
        if(compFunction(array[0],element)==0)
            return countPlace;
        else
            return -1;
    }

    if(compFunction(array[array_size/2],element)>0)
        return binarySearchHelp(array,element,array_size/2,
                                compFunction, countPlace);
    else
        return binarySearchHelp(&array[array_size/2],element,
                            array_size-(array_size/2),
                            compFunction,(array_size/2)+countPlace);
}

int binarySearch(void** array,void* element,int array_size,int(*compFunction)
        (void*,void*))
{
    return binarySearchHelp(array,element,array_size,compFunction, 0);
}

int compareInt(int* a,int* b)
{
    return *a-*b;
}
int main()
{
    int arrayInt[] = {0,1,2,3,4,5,6,7,8,9,100};
    int *array[] = {&arrayInt[0],&arrayInt[1],&arrayInt[2],&arrayInt[3],
                    &arrayInt[4],&arrayInt[5],&arrayInt[6],&arrayInt[7],
                    &arrayInt[8],&arrayInt[9],&arrayInt[10]};
    int test = 100;
    int k = binarySearch(array,&test,11,compareInt);
    printf("%d\n",k);
}


