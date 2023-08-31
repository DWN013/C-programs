// Test OpenMP program
// Libraries needed
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Elapsed wall clock time function
double omp_get_wtime(void);
// Function to find estimated value of PI using Monte Carlo algorithm
void monteCarlo(int N, int K)
{
    // Stores X and Y coordinates
    // of a random point
    double x, y;
    // Stores distance of a random
    // point from origin
    double d;
    // Stores number of points
    // lying inside circle
    int pCircle = 0;
    // Stores number of points
    // lying inside square
    int pSquare = 0;
    int i = 0;

// Parallel calculation of random
// points lying inside a circle
#pragma omp parallel firstprivate(x, y, d, i) reduction(+ : pCircle, pSquare) num_threads(K)
    {
        K = omp_get_max_threads();
        int thread_id = omp_get_thread_num();
        int n_threads = omp_get_num_threads();
        printf("There are %d threads\n", K);
        // Initializes random points
        // with a seed
        srand48((int)time(NULL));
        for (i = 0; i < N; i++) {
            // Finds random X co-ordinate
            x = (double)drand48();
            // Finds random X co-ordinate
            y = (double)drand48();
            // Finds the square of distance
            // of point (x, y) from origin
            d = ((x * x) + (y * y));
            // If d is less than or equal to 1
            if (d <= 1) {
                // Increment pCircle by 1
                pCircle++;
            }
            // Increment pSquare by 1
            pSquare++;
        }
    }
    // Stores the estimated value of PI
    double pi = 4.0 * ((double)pCircle / (double)(pSquare));
    // Prints the value in pi
    printf("Final Estimation of Pi = %f\n", pi);
}
// Driver Code
int main()
{   
    double start; 
    double end; 
    start = omp_get_wtime();

    int N = 100000000;
    int K = 4;
    // Function call
    monteCarlo(N, K);

    end = omp_get_wtime(); 
    printf("Work took %f seconds\n", end - start);
}
// 2 cores takes  19.1656 sec
// 4 cores takes  19.0604 sec
// 8 cores takes  19.3731 sec
// 16 cores takes 19.0635 sec