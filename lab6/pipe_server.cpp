/* Программа pipe_server.cpp */
#include"p.h"
#include <sys/wait.h>

int main(void) {
    int n, done, dummyfifo, privatefifo, publicfifo;
    static char buffer[PIPE_BUF];
    FILE *fin;
    struct message msg;
    mknod(PUBLIC, S_IFIFO | 0666, 0);
    if (((publicfifo = open(PUBLIC, O_RDONLY)) == -1) || (dummyfifo = open(PUBLIC, O_WRONLY | O_NDELAY)) == -1) {
        perror(PUBLIC);
        exit(1);
    }

    while (read(publicfifo, (char *) &msg, sizeof(msg)) > 0) {
        int pid;
        if ((pid = fork() == 0)) {
            n = done = 0;
            do {
                if ((privatefifo = open(msg.fifo_name, O_WRONLY | O_NDELAY)) == -1)
                    sleep(3);
                else {
                    fin = popen(msg.cmd_line, "r");
                    write(privatefifo, "\n", 1);
                    while ((n = read(fileno(fin), buffer, PIPE_BUF)) > 0) {
                        write(privatefifo, buffer, n);
                        memset(buffer, 0x0, PIPE_BUF);
                    }
                    pclose(fin);
                    close(privatefifo);
                    done = 1;
                }
            } while (++n < 5 && !done);
            if (!done) {
                write(fileno(stderr), "\nNOTE: SERVER ** NEVER ** accessed private FIFO\n", 48);
                exit(1);
            }
            exit(0);
        }
        waitpid(pid, NULL, WNOHANG);
    }
    return 0;
}
