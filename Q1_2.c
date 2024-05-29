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

int operation_count = 0;

//implements Quick sort for arr
void quickSort(int *arr, int left, int right) {
  int i = left, j = right;
  int tmp;
  int pivot = arr[(left + right) / 2];
    operation_count++;
  /* partition */
  while (i <= j) {
    while (arr[i] < pivot)
      i++;
    while (arr[j] > pivot)
      j--;
    if (i <= j) {
      tmp = arr[i];
      arr[i] = arr[j];
      arr[j] = tmp;
      i++;
      j--;
    }
  };

  /* recursion */
  if (left < j)
    quickSort(arr, left, j);
  if (i < right)
    quickSort(arr, i, right);
}

//implements Merge sort for Marr

void merge(int *arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int *arr, int l, int r)
{
   if (l < r)
   {
       // Same as (l+r)/2, but avoids overflow for
       // large l and h
       int m = l+(r-l)/2;
        operation_count++;
       // Sort first and second halves
       mergeSort(arr, l, m);
       mergeSort(arr, m+1, r);
 
       merge(arr, l, m, r);
   }
}


int main(int argc, char **argv)
{
    // right now not using arguments modify this line for it.

        struct timeval start, end;


    int size = atoi(argv[1]);
    char file[11];

    int *arr = (int*)malloc(pow(2,size) * sizeof(int));
    int *Marr = (int*)malloc(pow(2,size) * sizeof(int));

        file[0] = 'I';
        file[1] = 'n';
        file[2] = 'p';
        file[3] = 'u';
        file[4] = 't';
        file[7] = '.';
        file[8] = 't';
        file[9] = 'x';
        file[10] = 't';
    if(size == 11)
    {
        file[5] = '1';
        file[6] = '1';
    }
    else if(size == 13)
    {
        file[5] = '1';
        file[6] = '3';
    }
    else if(size == 15)
    {
        file[5] = '1';
        file[6] = '5';
    }
    else if(size == 17)
    {
        file[5] = '1';
        file[6] = '7';
    }
    else
    {
        printf("Invalid size");
    }
    printf("%s \n", file);

    FILE *fp = fopen(file, "r");
    if (fp == NULL)
    {
        printf("File not found");
    }
    else 
    {
        printf("File opened successfully \n");
    }

    // reading the file
    int file_iterator = 0;
    while(!feof(fp)){
        fscanf(fp,"%d", &arr[file_iterator]);
        Marr[file_iterator] = arr[file_iterator];
        file_iterator++;
    }
    close(fp);
    // sorting the array
    //------------------------------------------------------------- Quick Sort -------------------------------------------------------------
    gettimeofday( &start, NULL );
    quickSort(arr, 0, pow(2,size)-1);
    gettimeofday( &end, NULL );


    /* convert time to Gflop/s */
    double seconds = (end.tv_sec - start.tv_sec) +
            1.0e-6 * (end.tv_usec - start.tv_usec);
    double Gflops = 2e-9*operation_count/seconds;

    FILE *quickSortFile = fopen("quickSort.txt", "w");

    for(int i = 0; i < pow(2,size); i++)
    {
        fprintf(quickSortFile, "%d \n", arr[i]);
    }
    close(quickSortFile);

    //------------------------------------------------------------- Merge Sort -------------------------------------------------------------
    operation_count = 0;

    gettimeofday( &start, NULL );
    mergeSort(Marr, 0, pow(2,size)-1);
    gettimeofday( &end, NULL );

    /* convert time to Gflop/s */
    seconds = (end.tv_sec - start.tv_sec) +
            1.0e-6 * (end.tv_usec - start.tv_usec);
    double Gflops1 = 2e-9*operation_count/seconds;



    FILE *mergeSortFile = fopen("mergeSort.txt", "w");
    for(int i = 0; i < pow(2,size); i++)
    {
        fprintf(mergeSortFile, "%d \n", Marr[i]);
    }
    fclose(mergeSortFile);

    printf("Time taken for quick sort: %f Gflops \n", Gflops);
    printf("Time taken for merge sort: %f Gflops \n", Gflops1);
    return 0;    
}