#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

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
    unsigned int size; // curent size of the circular
};

struct circular* mkCircular()
{
    /** 
     * Return the pointer of the adress of the circular
     * 
     * @return the address of the pointer where the circular is starting
     * @author @YannisVanAchter
    */
    // set the circular and add the node to it
    struct circular* circular = malloc(sizeof(struct circular));
    circular->firstNode = NULL;
    circular->lastNode = NULL;
    circular->size = 0;
    return circular;
};

signed int extract(struct circular* cycle )
{
    /** 
     * return the value containd at curent node and pass to the next
     * @param cycle pointer to the circular
     * @return the data contained at the current node
     * @author @julien8vp
    */
    if (cycle->size == 0)
    {
        printf("Error the circular is empty\n");
        return NULL;
    }

    struct node* nodeToExtract = cycle->firstNode; 
    int dataExtracted = nodeToExtract->data; // extraction of the data of the 1st node (FIFO)
    cycle->firstNode = cycle->firstNode->next ; // replace the current 1st node by the next
    cycle->firstNode->previous = cycle->lastNode;
    cycle->size--; // increace of the size
    free(nodeToExtract);
    
    return dataExtracted; // return data of the extracted element
}

struct node* rotate(struct circular* cycle, int offset)
{
    /**
     * Apply a rotation to until we met the first odd or even value in the circular
     * 
     * @param cycle the address of the circular
     * @param offset 0 if we want odd value, 1 if we want even value
     * @return the address of the node wich contain an odd value 
     * @author @YannisVanAchter
     * If there is no odd value in the circular it return NULL
     */
     // check the offset to make sure it will respond as attend
     if (! (offset == 0 || offset == 1))
     {
        printf("The specified offset is invalid, make sure this is 0 or 1");
        exit(EXIT_FAILURE);
     }

    // allow memory for usefull variable
    struct node* nodeToReturn;
    struct node* tempNode;
    struct node* startingPoint = cycle->firstNode;

    do // loop until we met a node where the data corresponds to attend
    {
        nodeToReturn = ((cycle->firstNode)->next);
        tempNode = cycle->firstNode;
        cycle->lastNode = tempNode;
        cycle->firstNode = nodeToReturn;
    } 
    while ((cycle->firstNode)->data % 2 != offset && nodeToReturn != startingPoint);

    // If the circular does not contain attend we print message to inform and return null
    if (nodeToReturn == startingPoint && (cycle->firstNode)->data % 2 != offset)
    {
        // print message to inform there is no wanted data in the circular
        printf("The program did not find %s in the circular", (offset == 0) ? "odd\0" : "even\0");
        return NULL;
    }

    return nodeToReturn;
}

struct node* rotateToEven(struct circular* cycle)
{
    /**
     * Apply a rotation to until we met the first even value in the circular
     * 
     * @param cycle the address of the circular
     * @return the address of the node wich contain an even value 
     * @author @YannisVanAchter
     * If there is no even value in the circular it return NULL
     */
    return rotate(cycle, 0);
}

struct node* rotateToOdd(struct circular* cycle)
{
    /**
     * Apply a rotation to until we met the first odd value in the circular
     * 
     * @param cycle the address of the circular
     * @return the address of the node wich contain an odd value 
     * @author @YannisVanAchter
     * If there is no odd value in the circular it return NULL
     */
    return rotate(cycle, 1);
}

void insert(struct circular* cycle, signed int elt)
{
    /** 
     * Add at the node specified in the circular at the end
     * @param cycle the address of the circular where insert the value
     * @param elt  the value to insert
     * @author @julien8vp
     */
    struct node* newNode = malloc(sizeof(struct node));
    newNode->data = elt; // the new insert is the new last node (FIFO)
    if (cycle->size == 0)
    {
        newNode->previous = newNode;
        newNode->next = newNode;
        cycle->lastNode = newNode;
        cycle->firstNode = newNode;
    }
    else {
        newNode->next = cycle->lastNode->next; // set the next as the first created node 
        newNode->previous = cycle->lastNode; // set the previous as the last of cycle
        cycle->lastNode->next = newNode;
        cycle->lastNode = newNode; // the new node becomes the last one
    }
    cycle->size++; // increase the size
}

int main(int argc, char* argv[])
{
    /**
     * Main function where we write the test of the structure and the function
     * 
     * @param argc the number of arguments (int)
     * @param argv pointer to the arguments passed in command line (char [])
     * @return 0 on success
     */
    printf("Test is running\n");

    struct circular* cycle = mkCircular();
    signed int result = 0;

    insert(cycle, 0);
    if (cycle->size != 1) 
    {
        printf("Test failed line 173\n");
        exit(EXIT_FAILURE);
    }
    result = extract(cycle);
    if (result != 0)
    {
        printf("Test failed line 179\n");
        exit(EXIT_FAILURE);
    }

    // test greater cycle
    struct circular* cycle2 = mkCircular();
    for (int i = 0; i < 10; i++)
    {
        insert(cycle2, i);
    }
    if (cycle2->size != 10)
    {
        printf("Test failed line 190\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 10; i++)
    {
        struct node* node = rotateToOdd(cycle2);
        if (node->data % 2 != 1)
        {
            printf("Test failed line 197\nThe current value of iteration is %d\nThe current value of data is %d\n", i, node->data);
            exit(EXIT_FAILURE);
        }
        extract(cycle2);
    }

    struct node* hopeNullPointer = rotateToOdd(cycle2);
    if (hopeNullPointer != NULL)
    {
        printf("Test failed line 208\n");
        exit(EXIT_FAILURE);
    }
    
    printf("All test passed\n");
     return EXIT_SUCCESS;
}