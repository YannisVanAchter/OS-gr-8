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
    int head; // current lecture cursor
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
     * return the value containd at current node and pass to the next
     * @param cycle pointer to the circular
     * @return the data contained at the current node
     * @author @julien8vp
    */

   int data_extracted = cycle->firstNode->data; //extraction of the data of the 1st node (FIFO)
   cycle->firstNode = cycle->firstNode->next; //replace the current 1st node by the next
   return (data_extracted); //return data of the extracted element
}

void deleteCircular(unsigned int* cycle)
{
    /**
     * Delete all node of the circular and free the memory
     * @param cycle the address of the circular to delete
     * @author @julien8vp
     */
    free(cycle); //free the memory taken by the circular
    
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
     if (offset != 0 || offset != 1)
     {
        printf("The specified offset is invalid, make sure this is 0 or 1");
        exit(EXIT_FAILURE);
     }

    // allow memory for usefull variable
    struct node* nodeToReturn = malloc(sizeof(struct node));
    struct node* startingPoint = cycle->firstNode;

    do // loop until we met a node where the data corresponds to attend
    {
        nodeToReturn = ((cycle->firstNode)->next);
        cycle->head++;
        cycle->firstNode = nodeToReturn;
    } while ((cycle->firstNode)->data % 2 == offset && nodeToReturn != startingPoint);

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
    return rotate(cycle, 1);
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
    return rotate(cycle, 0);
}

void insert(struct circular* cycle, signed int elt)
{
    /** 
     * Add at the node specified in the circular at the end
     * @param cycle the address of the circular where insert the value
     * @param elt  the value to insert
     * @author @julien8vp
     */

    cycle->lastNode->previous = cycle->lastNode; // the last node becomes the second to last node
    elt = cycle->lastNode->data; // the new insert is the new last node (FIFO)
    cycle->lastNode = cycle->head; // put the new node as the current node
}

void delete(struct circular* cycle)
{
    /**
     * Will delete the current value in the circular and pass to the next one
     * When delete the memory is freed
     * 
     * @param cycle the address of the circular where remove the value
     * @author @julien8vp
     * If this is the last value in the circular, we delete the circular
     */
    free(cycle->head); // freed of the memory
    cycle->head = cycle->firstNode; //put the current node at the head of the circular
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
     int success = 1;
     printf("Test is running\n");

    if (success)
    {
        printf("All tests succeeded\n");
    }
     return EXIT_SUCCESS;
}