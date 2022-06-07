#include <stdio.h>
#include <math.h>
#include <omp.h>
#define max(a, b) ((a>b)?(a):(b))
#define min(a, b) ((a>b)?(b):(a))

#define MIN 2
#define MAX 25000000
#define SIZE MAX-MIN+1
#define THREADS_NUM 8

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

void domain_par_erasto(bool *res, int a, int n, int thr){    
    int sq=0;
    res[0]=res[1]=0;
    sq=floor(sqrt(n));
    
    if (n>4) domain_par_erasto(res, 2, sq, thr);
    else{
        if (n>=4) res[0]=res[1]=res[4]=1;
        else res[0]=res[1]=1;
        return;
    }
    omp_set_num_threads(thr);
    double start = omp_get_wtime();

#pragma omp parallel
    {
        int thnum=omp_get_thread_num(), allth=omp_get_num_threads();
        int left=(n/allth)*thnum, i, j, based_left;
        int right=left+n/allth-1;
        if (thnum==allth-1) right=n;
        if (left<=sq) left=sq+1;

        for (i=0;i<=sq;i++){
            if (res[i]==0){
                based_left=max(modal(left, i), modal(a, i));
                for (j=based_left;j<=right;j+=i) res[j]=1;
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


int main()
{    
    bool* res = bool_create_array(MAX);
    domain_par_erasto(res, MIN, MAX, THREADS_NUM);

    delete[] res;
}