#include <stdio.h>
#include <omp.h>
int main() {
    //Sets 8 global threads
    //omp_set_num_threads(8);
    #pragma omp parallel
     {
        int thread_id = omp_get_thread_num();
        int n_threads = omp_get_num_threads();
        if (thread_id == 0) printf("There are %d threads\n", n_threads);
     }
return 0;
}
