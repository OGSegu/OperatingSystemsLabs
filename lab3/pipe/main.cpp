#include <stdlib.h>
#include <unistd.h>
 
int main (int argc, char ** argv) {
        int i;
        for(i = 1; i < argc - 1; i++) {
                int fds[2]; // массив для пайпа fds[0] - read, fds[1] - write
                pipe(fds); // создаем пайп
                if (fork() == 0) { // если в дочернем процессе
                        dup2(fds[1], STDOUT_FILENO); // перенаправляем stdout (дочерний) 
                        execlp(argv[i], argv[i], NULL); // выполняем команду
                        exit(1); // завершаем работу дочернего процесса
                }
                dup2(fds[0], STDIN_FILENO); // перенаправляем stdin (родительский) 
                close(fds[1]); // закрываем "вход" пайпы
        }
        execlp(argv[i], argv[i], NULL); // выполняем последнюю команду
        exit(1); // завершаем работу родителя
}
