#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct node 
{
    unsigned int* previous; // pointer to previous node
    signed int data; // current value of this node
    unsigned int* next; // pointer to next node
}

struct circular 
{
    struct node* curentnode; // curent node
    struct node* lastnode; // node where after wich we add the next value
    struct node* firstnode; // first node of the circular
    int head; // curent lecture cursor
    int tail; // curent size of the circular
};

struct circular* mkCircular()
{
    /** 
     * Return the pointer to adress of the wielding circular
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

struct node* rotateToEven(struct circular* cycle)
{
    /**
     * 
     */
}

struct node* rotateToOdd(struct circular* cycle)
{

}

void insert(unsigned int* cycle, signed int elt)
{
    /** 
     * Add at the next address the node specified in the circular
     * @param cycle the address of the circular where insert the value
     * @param value  the value to insert
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
