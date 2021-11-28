#include<stdio.h>
#include<unistd.h>
#include <sndfile.hh>

int main() {
    FILE* file;
    file = fopen("./test.txt", "r");

    if (file == nullptr) {
        return 1;
    }

    if (fork() == 0) {
        rewind(file);
        char str[256];
        for (int i = 0; i < 2; i++) {
	    fgets(str, sizeof(str), file);
            printf("child process, content: %s", str);
        }
    } else {
	sleep(1);
        char str[256];
        while(fgets(str, sizeof(str), file)) {
            printf("parent process, content: %s", str);
        }
    }
}
