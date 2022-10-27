#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node 
{
    struct node* previous; // pointer to previous node
    signed int data; // current value of this node
    struct node* next; // pointer to next node
};

struct circular 
{
    struct node* lastNode; // node where after wich we add the next value
    struct node* firstNode; // first node of the circular
    int head; // curent lecture cursor
    unsigned int size; // curent size of the circular
};

struct circular* mkCircular()
{
    /** 
     * Return the pointer of the adress of the circular
     * 
     * @return the address of the pointer where the circular is starting
    */
};

signed int extract(struct circular* cycle )
{
    /** 
     * return the value containd at curent node
     * @param cycle pointer to the circular
     * @return the data contained at the current node
    */
}

void deleteCircular(unsigned int* cycle)
{
    /**
     * Delete all node of the circular and free the memory
     * @param cycle the address of the circular to delete
     */
}

struct node* rotate(struct circular* cycle, int offset)
{
    struct node* nodeToReturn;
    struct node* startingPoint = cycle->currentNode;
    do
    {
        nodeToReturn = *((cycle->currentNode)->next);
        cycle->head++;
    
    } while ((cycle->currentNode)->data % 2 == offset && nodeToReturn != startingPoint);

    if (nodeToReturn == startingPoint && (cycle->currentNode)->data % 2 != offset)
    {
        char type = (offset == 0) ? 'odd' : 'even';
        printf("The program did not find %s in the circular", type);
    }

    return nodeToReturn;
}

struct node* rotateToEven(struct circular* cycle)
{
    /**
     * 
     */
    return rotate(cycle, 1);
}

struct node* rotateToOdd(struct circular* cycle)
{
    return rotate(cycle, 0);
}

void insert(unsigned int* cycle, signed int elt)
{
    /** 
     * Add at the next address the node specified in the circular
     * @param cycle the address of the circular where insert the value
     * @param elt  the value to insert
     */
}

void delete(unsigned int* cycle)
{
    /**
     * @param cycle the address of the circular where remove the value
     * 
     * If this is the last value in the circular, we delete the circular
     */
}

int main(int argc, char* argv[])
{
    /**
     * @param argc the number of arguments (int)
     * @param argv pointer to the arguments passed in command line (char [])
     * @return 0 on success
     */

     return EXIT_SUCCESS;
}