# MPI Parallel Sorting Algorithms

## Overview
This project demonstrates the implementation of both serial and parallel versions of quicksort and mergesort using MPI in C. The project involves sorting arrays of various sizes and analyzing the performance in terms of GFLOPS.

## Instructions
### Compilation
To compile the programs, navigate to the `src` directory and use the following commands:
```bash
# Serial version
mpicc -o serial_quicksort serial_quicksort.c
mpicc -o serial_mergesort serial_mergesort.c

# Parallel version
mpicc -o parallel_quicksort parallel_quicksort.c -lm
mpicc -o parallel_mergesort parallel_mergesort.c -lm
