#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <assert.h>

typedef  struct node_t* Node;
struct node_t {
    int n;
    Node next;
};

typedef bool (*filterNodeRule)(int);

void toString(Node a);
bool unevenRule(int n);
bool primeRule(int n);
Node concatLists(Node head1, Node head2, filterNodeRule filterRule);
Node filter(Node a, filterNodeRule filterRule);
Node mergeNodes(Node node1, Node node2);
Node copyNodeList(Node a);
Node createNewNodeList(int* n, int length);
Node createNewNode(int n);

int main() {
    printf("Hello, World!\n");
    int q[] = {1, 2, 3, 4, 16, 17};
    int n[] = {5, 6, 7, 8, 9};
    Node node1=createNewNodeList(q, 6);
    Node node2=createNewNodeList(n, 5);
    Node concatedListPrime=concatLists(node1, node2, primeRule);
    Node concatedListUnEven=concatLists(node1, node2, unevenRule);
    toString(concatedListPrime);
    toString(concatedListUnEven);
    return 0;
}

//Returns true if n is uneven otherwise false.
bool unevenRule(int n)
{
    printf("%n",n);
    if(n%2==1){
        return true;
    }
    return false;
}

//returns true if n is primse otherwise false.
bool primeRule(int n)
{
    for(int i=2; i<=n/2; ++i)
    {
        if(n%i==0)
        {
            return false;
        }
    }
    return true;
}

//Prints out an entire list
void toString(Node a)
{
    while(a!=NULL){
        printf("%d\n", a->n);
        a=a->next;
    }
}

//Puts togather to lists and then checks through a generic function which
// nodes should stay in the list
Node concatLists(Node head1, Node head2, filterNodeRule filterRule)
{
    Node returnNode=mergeNodes(head1, head2);
    returnNode = filter(returnNode, filterRule);
    return returnNode;
}

//Gets a node and uses a function to check which node doesn't fit the
// function statment, then it removes them from the list
Node filter(Node a, filterNodeRule filterRule)
{
    Node lastNode=NULL;
    Node returnNode=a;
    Node iterator;
    while(a!=NULL)
    {
        if(!filterRule(a->n) && lastNode==NULL){
            returnNode=a->next;
            iterator=a;
            a=a->next;
            free(iterator);
        }
        if(!filterRule(a->n)){
            lastNode->next=a->next;
            iterator=a;
            a=a->next;
            free(iterator);
        }else {
            lastNode=a;
            a = a->next;
        }
    }
    return returnNode;
}

//Merges two nodes togather into one and then returns it
Node mergeNodes(Node node1, Node node2)
{
    assert(node1!=NULL);
    Node returnNode = copyNodeList(node1);
    Node iterator=returnNode;
    while(iterator->next!=NULL) {
        iterator = iterator->next;
    }
    iterator->next = copyNodeList(node2);
    return returnNode;
}

//Creates a copy of a nodelist and then returns it.
Node copyNodeList(Node a)
{
    assert(a!=NULL);
    Node returnNode=createNewNode(a->n);
    a=a->next;
    Node iterator=returnNode;
    while(a!=NULL)
    {
        iterator->next=createNewNode(a->n);
        a=a->next;
        iterator=iterator->next;
    }
    return returnNode;
}

//Creates a chain of nodes from an array
Node createNewNodeList(int* n, int length)
{
    Node returnNode = createNewNode(n[0]);
    Node iterator=returnNode;
    for(int i=1; i<length; i++){
        iterator->next= createNewNode(n[i]);
        iterator=iterator->next;
    }
    return returnNode;
}

//creates a single node with a given integer n
Node createNewNode(int n)
{
    Node returnNode = malloc(sizeof(Node*));
    returnNode->n=n;
    returnNode->next=NULL;
    return returnNode;
}