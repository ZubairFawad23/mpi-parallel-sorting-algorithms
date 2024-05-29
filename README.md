# MPI Parallel Sorting Algorithms

## Overview
This project demonstrates the implementation of both serial and parallel versions of quicksort and mergesort using MPI in C. The project involves sorting arrays of various sizes and analyzing the performance in terms of GFLOPS.

## Instructions
### Compilation
To compile the programs, navigate to the `src` directory and use the following commands:
```bash
# Serial version
mpicc -o serial_quicksort Q1.c
mpicc -o serial_mergesort Q1_2.c

# Parallel version
mpicc -o parallel_quicksort Q2.c -lm
