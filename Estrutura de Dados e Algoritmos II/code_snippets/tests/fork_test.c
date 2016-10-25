#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void fork_test()
{
    puts("TESTE FORK:\n");

    pid_t pid;

    pid = fork();

    if(pid > 0) {
        printf("Processo PAI PID: %d\n", pid);
    } else {
        printf("Processo FILHO PID: %d\n", pid);
    }
    puts("FIM");
}

void main()
{
    fork_test();
}