#include <stdio.h>
#include <iostream>
#include <omp.h>
#include <time.h>

#define MIN 2
#define MAX 50000000
#define SIZE MAX-MIN+1

// --- SIEVE_SEQUENTIAL RESULTS ---
// test 1
// MIN 2
// MAX 50000000
// Time: 14.712000 sec

// test 2
// MIN 2
// MAX 25000000
// Time: 5.221000 sec

// test 3
// MIN 25000000
// MAX 50000000
// Time: 6.559000 sec

bool isPrime(int n){
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0) return false;
    }
    return true;
}

// create array of numbers from MIN to MAX
int* create_array(int ssize){
    int* arr = new int[ssize];
    unsigned int arr_id = 0;
    for(int i=MIN; i <= MAX; i++){
        arr[arr_id++] = i;
    }
    return arr;
}

void sieve_sequential(){
    // every number from MIN to MAX
    int* numbers = create_array(SIZE);

    int* primes = new int[SIZE];
    unsigned int primes_id = 0;


    double start = omp_get_wtime();
    // primes from 2 to sqrt(MAX)
    for(int i = 2; i * i <= MAX; i++){
        if(isPrime(i))
            primes[primes_id++] = i;        
    }

    // --- sieve of Erathostenes ---
    // iterate over every number
    for(int i=0; i<SIZE; i++){
        // for each number iterate over primes
        for(int j = 0; j < primes_id; j++){
            // if the number is the prime - break
            if(numbers[i]==primes[j]) break;
            // if the number is a multiple of a prime
            else if(numbers[i] % primes[j] == 0){
                numbers[i] = 0;
                break;
            }
        }
    }
    double end = omp_get_wtime();

    // count how many primes (nonzero numbers)
    int count = 0;
    for(int i=0; i<SIZE; i++){
        if(numbers[i]!=0)
            count++; 
    }
    printf("Number of primes numbers: %d\n", count);
    printf("Time: %f sec\n", ((double)(end-start)));

    delete[] primes;
    delete[] numbers;
}



int main()
{
    sieve_sequential();
}