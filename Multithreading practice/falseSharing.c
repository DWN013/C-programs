#include <stdio.h>
#include <omp.h>

int main() {
  int *x = new int[100];
  #pragma omp parallel
  {
    int i = omp_get_thread_num(),
         stride = 16;
    for (int k = 0; k < 2000000000; k++)
      x[i*stride]++;
  }
  delete [] x;
  return 0;
}
