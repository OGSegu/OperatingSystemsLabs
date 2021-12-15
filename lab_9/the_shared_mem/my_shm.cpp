#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1023

main(void) {
   int shmid, shmid2, shmid3;
   char *shm, *shm2, *shm3;
   char *s;
   if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
       exit(1);
   }
   if ((shm = (char *) shmat(shmid, 0, 0)) == (char *) -1) {
       exit(2);
   }
   if ((shmid2 = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
       exit(1);
   }
   if ((shm2 = (char *) shmat(shmid2, 0, 0)) == (char *) -1) {
       exit(2);
   }
   if ((shmid3 = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
       exit(1);
   }
   if ((shm3 = (char *) shmat(shmid, 0, 0)) == (char *) -1) {
       exit(2);
   }
   s = shm;
   // Изменим 1024 байт в разделяемой памяти
   s[1024] = '1';
   printf("Value of 1024 byte: %s\n", &s[1026]);
   printf("Addresses 1\n");
   printf("shared mem: %10p\n\n",
          shm);
   printf("Addresses 2\n");
   printf("shared mem: %10p\n\n",
          shm2);
   printf("Addresses 3\n");
   printf("shared mem: %10p\n\n",
          shm3);
   shmdt(shm);
   shmdt(shm2);
   shmdt(shm3);
   shmctl(shmid, IPC_RMID, 0);
   shmctl(shmid2, IPC_RMID, 0);
   shmctl(shmid3, IPC_RMID, 0);
   return 0;
}

