#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

struct row {
    char email[100];
    char firstname[50];
    char lastname[50];
    char phone[100];
    int actif;
};

struct row typedef member;

int delete(char *email[], char filepath[])
{
    /**
    * Delete row of specified id (email)
    * @param email (char[]): email of member to delete
    * @param filepath (char[]): path of file where is the database
    * @return 0 on success, -1 on failure
    */
    return 0;
}

int insert(member member, char filepath[])
{
    /**
    * Insert member in the database
    * @param member (member): member to insert:
    *                         Contain email, first name, last name, phone number, actif
    * 
    * @param filepath (char[]): path of file where is the database
    */
    return 0;
}

member search(char *email[], char filepath[])
{
    /**
    * Search row of specified id (email)
    * @param email (char[]): email of member to search
    * @param filepath (char[]): path of file where is the database
    * @return member (member): struct member with email, first name, last name, phone number, actif
    */
}

int get_member(int actif, char filepath[], member* to_return[])
{
    /**
    * Get the members who are active or inactive
    * @param actif (int): 0 if member we search is inactive, 1 otherwise
    * @param filepath (char[]): path of file where is the database
    * @param to_return (member*): pointer where place the members found
    * @return -1 if there is no member who responds to actif, the size of to_return otherwise 
    */
}

int main(int *argc, char *argv[])
{
    char action;
    do {
        action = "0"
        printf("1. Add a member\n");
        printf("2. Remove a member");
        printf("3. Search for a member");
        printf("4. Search for inactive members\n");
        printf("5. Search for active members");

        printf("To quit programm press 'q'\nEnter your selection (the number): ");
        scanf("%c", &action);

        switch (action) {
            case 'q':
                break;
            case '1':
                // code
                break;
            case '2':
                // code
                break;
            case '3':
                // code
                break;
            case '4':
                // code
                break;
            case '5':
                // code
                break;
            default:
                printf("Unknown action %c\n", action);
                break;
        }

    } while (action != 'q');
    printf("Good bye!");
    
    return EXIT_SUCCESS;
}