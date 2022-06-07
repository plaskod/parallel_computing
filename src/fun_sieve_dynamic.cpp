#include <stdio.h>
#include <math.h>
#include <omp.h>
#define max(a, b) ((a>b)?(a):(b))
#define min(a, b) ((a>b)?(b):(a))

#define MIN 2
#define MAX 50000000
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

void erasto_fun_dynschedule(bool *res, int a, int n, int thr){
    int i, sq=0;
    res[0]=res[1]=0;
    sq=floor(sqrt(n));
    
    if (n>4) erasto_fun_dynschedule(res, 2, sq, thr);
    else{
        if (n>=4) res[0]=res[1]=res[4]=1;
        else res[0]=res[1]=1;
        return;
    }

    omp_set_num_threads(thr);

#pragma omp parallel for schedule(dynamic)
    for (i=0;i<=sq;i++){
        if (res[i]==1) continue;
        int sv=sq+1;
        int j=sv-sv%i+((sv%i==0)?0:i);
        for (j=max(i*i, j); j<=n; j+=i) res[j]=1;
    }

    int count = 0;
    for(int i=MIN; i<MAX; i++){
        if(res[i] == 0) {
            count++;
        }
    }
    printf("Number of primes numbers: %d\n", count);
    // printf("Time: %f sec\n", ((double)(end-start)));
}


int main(){    
    bool* res = bool_create_array(MAX);
    erasto_fun_dynschedule(res, MIN, MAX, THREADS_NUM);

    delete[] res;
}