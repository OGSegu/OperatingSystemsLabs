#include<stdio.h>
#include<unistd.h>
#include <sndfile.hh>

int main() {
    FILE* file;
    file = fopen("/home/vldf/CLionProjects/linux_lab_2/test.txt", "r");

    if (file == nullptr) {
        return 1;
    }

    if (fork()) {
        sleep(2);
        rewind(file);
        char str[256];
        while(fgets(str, sizeof(str), file)) {
            printf("parent process, content: %s", str);
        }
    } else {
        char str[256];
        while(fgets(str, sizeof(str), file)) {
            printf("child process, content: %s", str);
        }
    }
}
