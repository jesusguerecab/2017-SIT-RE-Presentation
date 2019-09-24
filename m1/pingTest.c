#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define _ADDR     "8.8.8.8"

int main()
{
    int null, bak, statval;
    // juggling stdout to supress ping output
    null = open("/dev/null", O_WRONLY);
    bak = dup(STDOUT_FILENO);
    dup2(null, STDOUT_FILENO);
    close(null);
    // execute command
    if(fork() == 0) {
        execl("/bin/ping", "ping", "-c1 -w1", _ADDR,  NULL);
        exit(1);
    }
    else
    {
        // restore stdout
        dup2(bak, STDOUT_FILENO);
        close(bak);
        wait(&statval);
        if(WIFEXITED(statval) && WEXITSTATUS(statval) == 0)
            printf("\nSuccess");
        else
            printf("\nFailed");
    }
    return 0;
}
