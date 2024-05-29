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
#include <mpi.h>

int operation_count = 0;


#define X 15

void quickSort1(int *arr, int left, int right);

void quickSort(int *arr, int left, int right, int Psize) {
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
    if(right-left > Psize)
    {
      /* recursion */
        if (left < j)
            quickSort(arr, left, j, Psize);
        if (i < right)
            quickSort(arr, i, right, Psize);
    }
    else 
    {
        quickSort1(arr, left, right);
    }

}



void quickSort1(int *arr, int left, int right) {
  int i = left, j = right;
  int tmp;
  int pivot = arr[(left + right) / 2];
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
    quickSort1(arr, left, j);
  if (i < right)
    quickSort1(arr, i, right);
}




void merge(int *arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
  
    int L[n1], R[n2];
 
   
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
   
    i = 0;     j = 0; 
    k = l; 
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
 
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int *arr, int l, int r, int L_size)
{
  operation_count++;
   if (l < r)
   {
       int m = l+(r-l)/2;
        
      if(m-l > L_size)
       mergeSort(arr, l, m, L_size);
       else
        quickSort1(arr, l, m);
        if(r-m > L_size)
       mergeSort(arr, m+1, r, L_size);
      else
        quickSort1(arr, m+1, r);
       merge(arr, l, m, r);
   }
}






int main(int argc, char **argv)
{
          struct timeval start, end;

    int l_size = 128;
    int my_id, root_process, ierr, num_procs;
    MPI_Status status;
    int size = X;
    int *arr = (int *)malloc(sizeof(int) * size);
    int *Marr = (int*)malloc(pow(2,size) * sizeof(int));
    char file[11];
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



  ierr = MPI_Init(&argc, &argv);


  ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
  ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
  int Process = num_procs;


  char *send_buffer = (int *)malloc(sizeof(int) * size / Process);
  

 gettimeofday( &start, NULL );
  MPI_Scatter(arr, size / Process, MPI_INT, send_buffer, size / Process, MPI_INT, 0, MPI_COMM_WORLD);
    char *recv_buffer = (int *)malloc(sizeof(int) * size / Process);
    quickSort(send_buffer, 0, size / Process - 1, l_size);
  MPI_Gather(arr, size / Process, MPI_INT, recv_buffer, size / Process, MPI_INT, 0, MPI_COMM_WORLD);

  if (my_id == 0)
  {
    quickSort(arr, 0, pow(2,size) - 1, l_size);
    gettimeofday( &end, NULL );

    printf("I am Master \n");
    printf("Sorted array is \n");
    for (int i = 0; i < pow(2,size); i++)
    {
//      printf("%d \n", arr[i]);
    }
    }

        /* convert time to Gflop/s */
    double seconds = (end.tv_sec - start.tv_sec) +
            1.0e-6 * (end.tv_usec - start.tv_usec);
    double Gflops = 2e-9*operation_count/seconds;


  operation_count = 0;
    gettimeofday( &start, NULL );

  MPI_Scatter(Marr, size / Process, MPI_INT, send_buffer, size / Process, MPI_INT, 0, MPI_COMM_WORLD);
    char *recv_buffer2 = (int *)malloc(sizeof(int) * size / Process);
    mergeSort(send_buffer, 0, size / Process - 1,l_size);
  MPI_Gather(Marr, size / Process, MPI_INT, recv_buffer2, size / Process, MPI_INT, 0, MPI_COMM_WORLD);


    if(my_id == 0)
    {
        mergeSort(Marr, 0, pow(2,size) - 1,l_size);
  gettimeofday( &end, NULL );

        printf("I am Master \n");
        printf("Sorted array is \n");
        for (int i = 0; i < pow(2,size); i++)
        {
            printf("%d \n", Marr[i]);
        }
    }
        /* convert time to Gflop/s */
    seconds = (end.tv_sec - start.tv_sec) +
            1.0e-6 * (end.tv_usec - start.tv_usec);
    double Gflops1 = 2e-9*operation_count/seconds;
    
        FILE *quickSortFile = fopen("quickSort.txt", "w");

    for(int i = 0; i < pow(2,size); i++)
    {
        fprintf(quickSortFile, "%d \n", arr[i]);
    }
    close(quickSortFile);
    
    
    FILE *mergeSortFile = fopen("mergeSort.txt", "w");
    for(int i = 0; i < pow(2,size); i++)
    {
        fprintf(mergeSortFile, "%d \n", Marr[i]);
    }
    fclose(mergeSortFile);
  /* Stop this process */

  printf("Gflops for quickSort is %f \n", Gflops);
  printf("Gflops for mergeSort is %f \n", Gflops1);
  ierr = MPI_Finalize();
}