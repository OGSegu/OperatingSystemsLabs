#include <stdio.h>
#include <sys/sem.h>
#include <unistd.h>


int main(void) {

    int semid;
    int result;

    printf("Enter semid: ");
    scanf("%d", &semid);

    while (1) {
        result = semctl(semid, 0, GETNCNT);
        if (result < 0) {
            printf("semid is not valid");
            return 0;
        }
        printf("%d are waiting \n", result);
        sleep(5);
    }
}

