#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>

#define EMAILSIZE 100
#define FIRSTNAMESIZE 50
#define LASTNAMESIZE 50
#define PHONESIZE 30
#define true 1
#define false 0
char comma = ',';
char entry = '\n';

struct row_t {
    char email[EMAILSIZE];
    char firstname[FIRSTNAMESIZE];
    char lastname[LASTNAMESIZE];
    char phone[PHONESIZE];
    int actif; // 1 or 0
};

struct row_t typedef member_t;

int min(int val1, int val2)
{
    if (val1 < val2)
        return val1;
    return val2;
}

int is_same_email(char email1[], char email2[])
{
    int len1 = strlen(email1);
    int len2 = strlen(email2);
    int size = min(len1, len2);
    for (int i = 0; i < size; i++)
    {
        if (email1[i] != email2[i])
            return false;
    }
    return true;
}

int copy_array(char *to_copy, char target[], int size, int *start)
{
    for (int i = 0; i < size; i++)
    {
        target[i] = *(to_copy + *start + i);
    }
    return true;
}

int len_to(char *sep, char string[], int *max)
{
    if (max == NULL)
        *max = strlen(string);
    
    int size = 0;
    while(size < *max && string[size] != *sep)
    {
        size++;
    }
    return size;
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
    member_t member;
    if (search_member(email, filepath, &member) == EXIT_FAILURE)
        return EXIT_SUCCESS;
    
    int database = open(filepath, O_RDWR);
    if (database == -1)
    {
        perror("open");
        return EXIT_FAILURE;
    }
    int max_size = EMAILSIZE + LASTNAMESIZE + FIRSTNAMESIZE + PHONESIZE + 2;
    char buffer[max_size];
    char current_email[EMAILSIZE];
    int readed;
    int current_len, sep_mail, sep_firstname, sep_lastname, sep_phone, sep_actif;
    int email_passed = 0;
    do {
        readed = read(database, buffer, max_size);
        if (readed > 0)
        {
            current_len = len_to(&entry, buffer, NULL);
            sep_mail = len_to(&comma, buffer, &current_len);

            for (int i = 0; i < sep_mail; i++)
                current_email[i] = buffer[i]; // copy email to compare
            
            if (! email_passed)
            { // go to the next row
                email_passed = is_same_email(current_email, email);
                lseek(database, (- readed) + current_len, SEEK_CUR);
            }
            else 
            {
                char *row = malloc(sizeof(char) * current_len);
                sep_firstname = len_to(&comma, buffer + sep_mail, &current_len);
                sep_lastname = len_to(&comma, buffer + sep_firstname, &current_len);
                sep_phone = len_to(&comma, buffer + sep_lastname, &current_len);
                sep_actif = len_to(&comma, buffer + sep_phone, &current_len);
                copy_array(buffer, row, sep_mail, NULL);
                copy_array(buffer, row, sep_firstname, &sep_mail);
                copy_array(buffer, row, sep_lastname, &sep_mail);
                copy_array(buffer, row, sep_phone, &sep_mail);
                copy_array(buffer, row, current_len, &sep_mail);
                free(row);
                lseek(database, -readed, SEEK_CUR);
                write(database, (void *)row, strlen(row));

            }
        }
    } while (readed > 0);

    close(database);
    return EXIT_SUCCESS;
}

int insert(char email[], char firstname[], char lastname[], char phone[], int actif, char filepath[])
{
    /**
    * Insert member in the database
    * @param member (member): member to insert:
    *                         Contain email, first name, last name, phone number, actif
    * 
    * @param filepath (char[]): path of file where is the database
    * @return (int): EXIT_FAILURE or EXIT_SUCCESS;
    */
    member_t member;
    if (search_member(email, filepath, &member) == EXIT_SUCCESS)
        return EXIT_FAILURE;

    int max_size = EMAILSIZE + LASTNAMESIZE + FIRSTNAMESIZE + PHONESIZE + 2; // one for int of actif and one for \n
    char row[max_size];
    sprintf(row, "%s,%s,%s,%s,%d\n", email, firstname, lastname, phone, actif);
    
    int database = open(filepath, O_WRONLY | O_CREAT);
    lseek(database, 0, SEEK_END);
    write(database, (void *)row, max_size);
    close(database);

    return EXIT_SUCCESS;
}

int search_member(char target[], char filepath[], member_t* to_return)
{
    /**
    * Search row of specified id (email)
    * @param target (char[]): email of member to search
    * @param filepath (char[]): path of file where is the database
    * @param to_return (pointer to member_t): struct member with email, first name, last name, phone number, actif
    * @return EXIT_code (int): 0 on success, 1 on failure
    */
    int max_size = EMAILSIZE + LASTNAMESIZE + FIRSTNAMESIZE + PHONESIZE + 2; // one for int of actif and one for \n
    char buffer[max_size]; // email + phone + name + lastname + 1 (actif as bool)
    int readed;
    int current_len;
    int sep_mail, sep_firstname, sep_lastname, sep_phone, sep_actif;
    int found = false;
    char email[EMAILSIZE];

    int database = open(filepath, O_RDONLY | O_CREAT);
    if (database == -1)
    {
        perror("open");
        return EXIT_FAILURE;
    }
    do {
        readed = read(database, buffer, max_size);
        if (readed > 0)
        {
            current_len = len_to(&entry, buffer, &readed);
            sep_mail = len_to(&comma, buffer, &current_len);
            printf("%s\n", buffer);
            for (int i = 0; i < sep_mail; i++)
                email[i] = buffer[i]; // copy email to compare
            
            if (is_same_email(email, target))
            {
                sep_firstname = len_to(&comma, buffer + sep_mail, &current_len);
                sep_lastname = len_to(&comma, buffer + sep_firstname, &current_len);
                sep_phone = len_to(&comma, buffer + sep_lastname, &current_len);
                sep_actif = len_to(&comma, buffer + sep_phone, &current_len);
                char firstname[FIRSTNAMESIZE];
                char lastname[LASTNAMESIZE];
                char phone[PHONESIZE];
                to_return->actif = buffer[current_len -2]; // -2 to avoid \n
                strcpy(to_return->email, email);
                copy_array(buffer, to_return->firstname, sep_firstname, &sep_mail);
                copy_array(buffer, to_return->lastname, sep_lastname, &sep_firstname);
                copy_array(buffer, to_return->phone, sep_phone, &sep_lastname);

                close(database);
                return EXIT_SUCCESS;
            }
            lseek(database, (- readed) + current_len, SEEK_CUR);
        }
    } while (readed > 0);
    close(database);

    return EXIT_FAILURE;
}

int get_member(char actif, char filepath[], member_t to_return[], int size_to_return)
{
    /**
    * Get the members who are active or inactive
    * @param actif (char): N if member we search is inactive, 1 otherwise
    * @param filepath (char[]): path of file where is the database
    * @param to_return (member*): pointer where place the members found
    * @param size_to_return (int): maximum element of the list given 
    * @return -1 if there is no member who responds to actif, the size of to_return otherwise 
    */
    int max_size = EMAILSIZE + LASTNAMESIZE + FIRSTNAMESIZE + PHONESIZE + 2; // one for int of actif and one for \n
    char buffer[max_size]; // email + phone + name + lastname + 1 (actif as bool)
    int readed;
    int current_len;
    int sep_mail, sep_firstname, sep_lastname, sep_phone, sep_actif;
    int found = false;
    char email[EMAILSIZE];
    int current_index_to_return = 0;

    int database = open(filepath, O_RDONLY | O_CREAT);
    if (database == -1)
    {
        perror("open");
        return EXIT_FAILURE;
    }
    
    do {
        readed = read(database, buffer, max_size);
        if (readed > 0)
        {
            current_len = len_to(&entry, buffer, NULL);
            int current_actif = buffer[current_len -1]; // -2 to avoid \n
            
            if (current_actif == actif)
            {
                sep_mail = len_to(&comma, buffer, &current_len);
                sep_firstname = len_to(&comma, buffer + sep_mail, &current_len);
                sep_lastname = len_to(&comma, buffer + sep_firstname, &current_len);
                sep_phone = len_to(&comma, buffer + sep_lastname, &current_len);
                sep_actif = len_to(&comma, buffer + sep_phone, &current_len);

                for (int i = 0; i < sep_mail; i++)
                    email[i] = buffer[i]; // copy email to compare
                
                char firstname[FIRSTNAMESIZE];
                char lastname[LASTNAMESIZE];
                char phone[PHONESIZE];
                (to_return + current_index_to_return)->actif = buffer[current_len -1]; 
                strcpy((to_return + current_index_to_return)->email, email);
                copy_array(buffer, (to_return + current_index_to_return)->firstname, sep_firstname, &sep_mail);
                copy_array(buffer, (to_return + current_index_to_return)->lastname, sep_lastname, &sep_firstname);
                copy_array(buffer, (to_return + current_index_to_return)->phone, sep_phone, &sep_lastname);

                current_index_to_return++;
            }
            lseek(database, (- readed) + current_len, SEEK_CUR);
        }
    } while (readed <= 0 && current_index_to_return < size_to_return);
    close(database);

    return EXIT_FAILURE;
}

int main(int *argc, char *argv[])
{
    char action;int success;
    char FILEPATH[8] =  ".db.txt\0";
    member_t to_insert; //= malloc(sizeof(member_t));
    char *email[EMAILSIZE];
    char *email_2[EMAILSIZE];
    member_t member;
    member_t inactive_members[100];
    member_t active_members[100];

    do {
        char action;
        printf("1. Add a member\n");
        printf("2. Remove a member\n");
        printf("3. Search for a member\n");
        printf("4. Search for inactive members\n");
        printf("5. Search for active members\n");

        printf("To quit programm press 'q'\nEnter your selection (the number): ");
        scanf("%c", &action);

        char email1[EMAILSIZE], firstname1[EMAILSIZE], lastname1[EMAILSIZE], phone1[EMAILSIZE];
        int actif1;
        switch (action) {
            case 'q':
                break;
            case '1':
                printf("Enter your email: ");
                scanf("%s", &email1);
                printf("Enter your name: ");
                scanf("%s", &firstname1);
                printf("Enter your last name: ");
                scanf("%s", &lastname1);
                printf("Enter your phone number: ");
                scanf("%s", &phone1);
                printf("Are you active ? (1 for yes, 0 for no): ");
                scanf("%i", &actif1);
                success = insert(email1, firstname1, lastname1, phone1, actif1, FILEPATH);
                break;
            case '2':
                printf("Enter the mail of the member to delete: ");
                scanf("%s", email);
                success = delete(*email, FILEPATH);
                break;
            case '3':
                printf("Enter the mail of the member to search: ");
                scanf("%s", email_2);
                success = search_member(*email_2, FILEPATH, &member);
                break;
            case '4':
                get_member('N', FILEPATH, inactive_members, 100);
                break;
            case '5':
                get_member('Y', FILEPATH, active_members, 100);
                break;
            default:
                printf("Unknown action: %c\n", action);
                break;
        }
        if (success != EXIT_SUCCESS)
        {
            printf("Something went wrong :(\n");
        }
        success = EXIT_FAILURE;

    } while (action != 'q');
    printf("Good bye!\n");
    // free(to_insert);
    free(email);
    free(email_2);
    free(inactive_members);
    free(active_members);

    return EXIT_SUCCESS;
}