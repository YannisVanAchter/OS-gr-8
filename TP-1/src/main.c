#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

char buffer[1024];

void handler(int signum);

int main(void)
{
    signal(SIGALRM, handler);
    while (1) // infinity loop
    {
        alarm(5);
        printf("Enter char:\n");
        char string[1024];
        scanf("%s", string);
        strcat(buffer, string);
    }
    return EXIT_SUCCESS;
}
void handler(int signum)
{
    if (signum == SIGALRM)
    {
        int lenght = strlen(buffer);
        printf("Lenght: %d\n", lenght);
        if (lenght == 0)
        {
            exit(EXIT_SUCCESS);
        }
        printf("The input was:\n");
        printf("%s",buffer);
        printf("\n");
        memset(buffer,0,lenght);
        alarm(5);
    }
}