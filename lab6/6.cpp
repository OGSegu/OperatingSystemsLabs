#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static int forkRes = -1;

void signalHandler(int sig) {
    if (!forkRes) {
        printf("child got signal %i\n", sig);
    } else {
        printf("parent got signal %i\n", sig);
    }
}

int main() {
    struct sigaction act;
    act.sa_handler = &signalHandler;
    sigfillset(&act.sa_mask);
    act.sa_flags = SA_RESTART;
    sigaction(1, &act, NULL);
    sigaction(2, &act, NULL);
    sigaction(3, &act, NULL);
    srand(42);

    forkRes = fork();
    if (forkRes < 0)
        printf("Can't create child process\n");
    else if (forkRes == 0) {
        int parentPid = getppid();
        while (1) {
            kill(parentPid, (rand() + 1) % 4);
            sleep(1);
        }
    }
    else {
        while (1) {
            kill(forkRes, (rand() + 1) % 4);
            sleep(1);
        }
    }
}
