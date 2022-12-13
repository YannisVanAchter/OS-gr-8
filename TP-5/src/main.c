#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define EMAILSIZE 100
#define true 1
#define false 0
#define FILEPATH ".db.txt"

struct row_t {
    char email[EMAILSIZE];
    char firstname[50];
    char lastname[50];
    char phone[100];
    int actif;
};

struct row_t typedef member_t;

int is_same_email(char email1[], char email2[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (email1[i] != email2[i])
            return false;
    }
    return true;
}

int copy_array(int to_copy[], int target[], int size)
{
    for (int i = 0; i < size; i++)
    {
        target[i] = to_copy[i];
    }
    return true;
}

int search_member(char email[], char filepath[], member_t* to_return);

int delete(char email[], char filepath[])
{
    /**
    * Delete row of specified id (email)
    * @param email (char[]): email of member to delete
    * @param filepath (char[]): path of file where is the database
    * @return 0 on success, -1 on failure
    */
    int member_file = open(filepath, O_RDWR );
    char current_email[100];
    int bytes_read;

    member_t* current_member = malloc(sizeof(member_t));
    while (is_same_email((*current_member).email, email, EMAILSIZE))
    {
        bytes_read = read(member_file, current_member , sizeof(member_t));
        if (bytes_read < sizeof(member_t))
        {   
            close(member_file);
            return EXIT_FAILURE;
        }

        lseek(member_file , sizeof(member_t) , SEEK_CUR );
    }
    free(current_member);

    do {
        member_t* current_member = malloc(sizeof(member_t));
        bytes_read = read(member_file, current_member , sizeof(member_t));

        lseek(member_file, -sizeof(member_t), SEEK_CUR);
        write(member_file, current_member, sizeof(member_t));
        lseek(member_file , sizeof(member_t) , SEEK_CUR );

        free(current_member);
    } while (bytes_read <= 0);

    close(member_file);
    printf("Delete of %s has been successful", email);
    return EXIT_SUCCESS;
}

int insert(member_t *member, char filepath[])
{
    /**
    * Insert member in the database
    * @param member (member): member to insert:
    *                         Contain email, first name, last name, phone number, actif
    * 
    * @param filepath (char[]): path of file where is the database
    * @return (int): EXIT_FAILURE or EXIT_SUCCESS;
    */
    member_t *i = malloc(sizeof(member));
    if (search_member((*member).email, filepath, i) == EXIT_FAILURE) //the email address is already registered.
    {
        free(i);
        return EXIT_FAILURE;
    }
    free(i);

    //the email address isn't registered yet.
    int database = open(filepath, O_WRONLY);
    lseek(database, 0, SEEK_END);
    int fine = write(database, (void *) member, sizeof(member_t));
    if (fine != sizeof(member_t))
    {
        close(database);
        printf("Insersion occured unsuccessful");
        return EXIT_FAILURE;
    }
    close(database);
    printf("Insersion occured successfully");

    return EXIT_SUCCESS;
}

int search_member(char email[], char filepath[], member_t* to_return)
{
    /**
    * Search row of specified id (email)
    * @param email (char[]): email of member to search
    * @param filepath (char[]): path of file where is the database
    * @param to_return (pointer to member): struct member with email, first name, last name, phone number, actif
    * @return EXIT_code (int): 0 on success, 1 on failure
    */
    int readed;

    int database = open(filepath, O_RDONLY);

    if (database == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    do {
        readed = read(database, to_return, sizeof(member_t));

        if (is_same_email(email, to_return->email, EMAILSIZE)) 
        {   
            close(database);
            printf("The member found is %s %s, his phonenumber is %s\nHis email is: %s", to_return->firstname, to_return->lastname, to_return->phone, to_return->email);
            return EXIT_SUCCESS;
        }
        lseek(database, sizeof(member_t), SEEK_CUR);

    } while (readed != -1);

    close(database);

    return EXIT_FAILURE;
}

int get_member(int actif, char filepath[], member_t to_return[], int size_to_return)
{
    /**
    * Get the members who are active or inactive
    * @param actif (int): 0 if member we search is inactive, 1 otherwise
    * @param filepath (char[]): path of file where is the database
    * @param to_return (member*): pointer where place the members found
    * @return -1 if there is no member who responds to actif, the size of to_return otherwise 
    */
    member_t *current = malloc(sizeof(member_t));
    int address_to_return = 0;
    int readed;

    int database = open(filepath, O_RDONLY);

    if (database == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    do {
        readed = read(database, current, sizeof(member_t));

        if ((*current).actif == actif && size_to_return > address_to_return) 
        {   
            to_return[address_to_return] = *current;
            address_to_return++;
            printf("The member found is %s %s, his phonenumber is %s\nHis email is: %s", current->firstname, current->lastname, current->phone, current->email);
        }

    } while (readed != -1);

    close(database);

    return EXIT_SUCCESS;
}

int main(int *argc, char *argv[])
{
    char action;int success;
    do {
        action = "0";
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
                member_t* to_insert = malloc(sizeof(member_t));
                printf("Enter your email: ");
                scanf("%s", (*to_insert).email);
                printf("Enter your name: ");
                scanf("%s", (*to_insert).firstname);
                printf("Enter your last name: ");
                scanf("%s", (*to_insert).lastname);
                printf("Enter your phone number: ");
                scanf("%s", (*to_insert).phone);
                printf("Are you active ? (1 for yes, 0 for no): ");
                scanf("%i", (*to_insert).actif);
                success = insert(to_insert, FILEPATH);
                free(to_insert);
                break;
            case '2':
                char *email[EMAILSIZE];
                printf("Enter the mail of the member to delete: ");
                scanf("%s", email);
                success = delete(*email, FILEPATH);
                free(email);
                break;
            case '3':
                char *email[EMAILSIZE];
                printf("Enter the mail of the member to delete: ");
                scanf("%s", email);
                member_t member;
                success = search_member(*email, FILEPATH, member);
                free(email);
                break;
            case '4':
                member_t inactive_members[100];
                get_member(0, FILEPATH, inactive_members, 100);
                free(inactive_members);
                break;
            case '5':
                member_t active_members[100];
                get_member(0, FILEPATH, active_members, 100);
                free(active_members);
                break;
            default:
                printf("Unknown action %c\n", action);
                break;
        }
        if (success != EXIT_SUCCESS)
        {
            printf("Something went wrong :(\n");
        }
        success = EXIT_FAILURE;

    } while (action != 'q');
    printf("Good bye!");

    return EXIT_SUCCESS;
}