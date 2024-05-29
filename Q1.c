#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <sys/sysinfo.h>
#include <math.h>
#include <unistd.h>
#include <sched.h>

#define NUM_CPU 4


int main() {

    struct timeval start, end;

//int *arr = (int*)malloc(n * sizeof(int));
    int * Array = (int*)malloc(pow(2,11)*sizeof(int));
    int * Array1 = (int*)malloc(pow(2,13)*sizeof(int));
    int * Array2= (int*)malloc(pow(2,15)*sizeof(int));
    int * Array3 = (int*)malloc(pow(2,17)*sizeof(int));

    for(int i = 0; i < pow(2,11); i++)
    {
        Array[i] = rand();
    }
    for(int i = 0; i < pow(2,13); i++)
    {
        Array1[i] = rand();
    }
    for(int i = 0; i < pow(2,15); i++)
    {
        Array2[i] = rand();
    }
    for(int i = 0; i < pow(2,17); i++)
    {
        Array3[i] = rand();
    }

  FILE *fp1 = fopen("Input11.txt", "w");

  for (int i = 0; i < pow(2,11); i++) {
    fprintf(fp1, "%d \n", Array[i]);
  }

  fclose(fp1);

  FILE *fp2 = fopen("Input13.txt", "w");

  for (int i = 0; i < pow(2,13); i++) {
    fprintf(fp2, "%d \n", Array1[i]);
  }

  fclose(fp2);

  FILE *fp3 = fopen("Input15.txt", "w");

  for (int i = 0; i < pow(2,15); i++) {
    fprintf(fp3, "%d \n", Array2[i]);
  }

  fclose(fp3);

  FILE *fp4 = fopen("Input17.txt", "w");

  for (int i = 0; i < pow(2,17); i++) {
    fprintf(fp4, "%d \n", Array3[i]);
  }

  fclose(fp4);


//    cpu_set_t cpu_s[NUM_CPU];



//    gettimeofday( &start, NULL );


}