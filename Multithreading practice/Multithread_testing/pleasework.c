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
omp_set_nested(1);
int * a;
int * b;
int * c;
int n = ARRAY_SIZE;                 // number of array elements
int n_per_thread;                   // elements per thread
int total_threads = omp_get_num_threads();    // number of threads to use
int i;       // loop index
// allocating space for the arrays
a = (int *) malloc(sizeof(int)*n);
b = (int *) malloc(sizeof(int)*n);
c = (int *) malloc(sizeof(int)*n);
// initializing array a and b with consecutive integer values
for(i=0; i<n; i++) {
a[i] = i;
}
for(i=0; i<n; i++) {
b[i] = i;
}
omp_set_num_threads(total_threads);
// determining how many elements each process will work on
n_per_thread = n/total_threads;
#pragma omp parallel for shared(a, b, c) private(i) schedule(dynamic)
for(i=0; i<n; i++) {
c[i] = a[i]+b[i];
printf("Thread %d works on element%d\n", omp_get_thread_num(), i);
}
printf("i\ta[i]\t+\tb[i]\t=\tc[i]\n");
for(i=0; i<n; i++) {
printf("%d\t%d\t\t%d\t\t%d\n", i, a[i], b[i], c[i]);
}
// cleaning up memory
free(a);  free(b); free(c);
return 0;
}


/*
int main(int argc, char* argv[]){
// Beginning of parallel region
#pragma omp parallel
{
omp_set_num_threads(2);
printf("Hello World... from thread = %d\n",
omp_get_thread_num());
}
// Ending of parallel region
}
*/

/*
void main(){
    double A[1000];
    
    //omp_get_num_threads(4);
    #pragma omp parallel num_threads(4)
    {   
        //Executes number of thread that is currently executing code
        int ID_of_used_thread = omp_get_thread_num();
        //Returns total amount of threads avaliable
        int total_amnt_threads = omp_get_max_threads();
        //Total number of avaliable 
        int num_processors = omp_get_num_procs();
        printf("ID of used thread: %d\n", ID_of_used_thread);
        printf("Total amount of threads: %d\n", total_amnt_threads);
        printf("Number of processors: %d\n", num_processors);
        printf("----------------------------------------\n");
        omp_set_num_threads(2);
        ID_of_used_thread = omp_get_thread_num();
        //Returns total amount of threads avaliable
        total_amnt_threads = omp_get_max_threads();
        //Total number of avaliable 
        num_processors = omp_get_num_procs();
        printf("ID of used thread: %d\n", ID_of_used_thread);
        printf("Total amount of threads: %d\n", total_amnt_threads);
        printf("Number of processors: %d\n", num_processors);
        printf("----------------------------------------\n");

        start = omp_get_wtime();
        int i; double x, pi, sum = 0.0;
        step = 1.0/(double)num_steps;
        for(i=0;i<num_steps;i++){
            x = (i+0.5)*step;
            sum = sum + 4.0/(1.0+x*x);
        }
        pi = step*sum;
        printf("pi: %f\n", pi);

        end = omp_get_wtime(); 
        printf("Work took %f seconds\n", end - start);
    }
}
*/