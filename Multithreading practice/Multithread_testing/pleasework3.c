// OpenMP program proof of concept
// Libraries needed
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static long num_steps = 100000000;
double step;
double start; 
double end; 

#define ARRAY_SIZE 8  //Size of arrays whose elements will be added
int main (int argc, char *argv[]){

// elements of arrays a and b will be added
// and stored in array c

//omp_set_nested(1);

int n = ARRAY_SIZE;                 // number of array elements
int n_per_thread;                   // elements per thread
int total_threads = 8;   // number of threads to use
int i;       // loop index

omp_set_num_threads(total_threads);
// determining how many elements each process will work on

#pragma omp parallel for private(i) schedule(dynamic)
for(i=0; i<n; i++) {
   printf("Thread %d works on element %d\n", omp_get_thread_num(), i);
}
return 0;
}

