#include <stdio.h>
#include <math.h>
#include <omp.h>
#define max(a, b) ((a>b)?(a):(b))
#define min(a, b) ((a>b)?(b):(a))

#define MIN 2
#define MAX 25000000
#define SIZE MAX-MIN+1
#define THREADS_NUM 2

inline int modal(int a, int b){
    return a-a%b+((a%b==0)?0:b);
}

// create array of numbers from MIN to MAX
bool* bool_create_array(int ssize){
    bool* arr = new bool[ssize];
    unsigned int arr_id = 0;
    for(int i=MIN; i <= MAX; i++){
        arr[arr_id++] = 0;
    }
    return arr;
}
void primitive_finder(bool *res, int a, int n, int thr){
    int i;

    omp_set_num_threads(thr);
    double start = omp_get_wtime();

#pragma omp parallel for
    for (i=a;i<=n;i++){
        for (int j=2;j*j<=i;j++){
            if (i%j==0) {
                res[i]=1;
                break;
            }
        }
    }

    double end = omp_get_wtime();

    int count = 0;
    for(int i=MIN; i<MAX; i++){
        if(res[i] == 0) {
            count++;
        }
    }
    printf("Number of primes numbers: %d\n", count);
    printf("Time: %f sec\n", ((double)(end-start)));

}



int main(int argc, char *argv[])
{
    bool* res = bool_create_array(MAX);
    primitive_finder(res, MIN, MAX, THREADS_NUM);

    delete[] res;
}