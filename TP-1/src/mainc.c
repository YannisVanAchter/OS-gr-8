#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

// use preprocessor to change size_max to 50 if this is not already declared
#ifndef size_max
#define size_max 50
#endif

char STRINGGGG[size_max];
int i;
int caugth_signal = 0; // Lorsque le SIGALRM est perçu, passe la valeur à 1

void handler(int signum)
{
    if (signum == SIGALRM)
    {
        if (STRINGGGG[0] == 0)
        {
            // exit prog if first char is NULL
            printf("\nend\n");
            exit(EXIT_SUCCESS);
        }

        alarm(5);
        int index = 0;
        while (index < size_max)
        {
            // print stored STRINGGGG
            putchar(STRINGGGG[index]);
            index++;
        }
        memset(STRINGGGG, 0, size_max); // empty the list
        i = 0;
        caugth_signal = 1;
    }
}

int main(void)
{
    signal(SIGALRM, handler);
    alarm(5);
    printf("Enter your characters: ");
    char c;
    i = 0;
    while (1)
    {
        if (caugth_signal) // if signal is cought set i to zero
        {
            i = 0;
            caugth_signal = 0;
        }
        c = getchar();
        if (c >= 97 & c <= 122) // The value come from ASCII table please referet to it
        {
            c -= 32; // set in upper case if this is not (-32 in ascii table)
        }

        // printf("%s", i);
        STRINGGGG[i] = c;
        i++;
    }
    return EXIT_SUCCESS;
}