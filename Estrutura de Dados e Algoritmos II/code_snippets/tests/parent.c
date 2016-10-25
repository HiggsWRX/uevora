#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_COUNT 200
#define true 1
#define false 0

void child_process(void);
void parent_process(void);

void child_process(void)
{
    int i;

    for (i = 1; i <= MAX_COUNT; i++)
    {
        printf("This line is from child, value = %d\n", i);
    }
    printf("*** Child process is done ***\n");
}

void parent_process(void)
{
    int i;
    for (i = 1; i <= MAX_COUNT; i++)
    {
        printf("This line is from parent, value = %d\n", i);
    }
    printf("*** Parent process is done ***\n");
}

void main(void)
{
    pid_t pid;

    pid = fork();

    if (pid == 0)
        child_process();
    else
        parent_process();
}