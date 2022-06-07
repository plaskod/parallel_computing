#include <stdio.h>
#include <iostream>
#include <omp.h>
#include <time.h>

#define MIN 25000000
#define MAX 50000000
#define SIZE MAX-MIN+1

// --- SEQUENTIAL RESULTS ---
// --- test 1.3.1 (FINAL) ---
// MIN 2
// MAX 50000000
// Time: 64.202000 sec

// --- test 1.3.2 (FINAL) ---
// MIN 2
// MAX 25000000
// Time: 19.708000 sec

// --- test 1.3.3 (FINAL) ---
// MIN 25000000
// MAX 50000000
// Time: 35.405000 sec


bool isPrime(int n){
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0) return false;
    }
    return true;
}

void sequential(){
    int* numbers = new int[SIZE];
    int numbers_id = 0;

    // clock_t start, end;
    // start = clock();
    double start = omp_get_wtime();
    for(int i = MIN; i <= MAX; i++){
        if(isPrime(i)){
            numbers[numbers_id++] = i;
        }
    }
    double end = omp_get_wtime();

    // printf("SIZE: %d\n", SIZE);
    printf("Number of primes numbers: %d\n", numbers_id);
    printf("Time: %f sec\n", ((double)(end-start)));
    delete[] numbers;
}

int main()
{
    sequential();
}
// --- ADDITIONAL RESULTS --
// --- test 1.1 ---
// MIN 2
// MAX 10000000
// Time: 4.581000 sec

// --- test 1.2 ---
// MIN 2
// MAX 20000000
// Time: 15.359000 sec