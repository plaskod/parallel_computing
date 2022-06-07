#include <stdio.h>
#include <iostream>
#include <omp.h>
#include <time.h>

#define MIN 2
#define MAX 25000000
#define SIZE MAX-MIN+1
#define NUM_THREADS 2

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

inline int fast_mod(const int input, const int ceil) {
  return input >= ceil ? input % ceil : input;
}

void sieve(){
    //omp_set_dynamic(0); // FIXME
    omp_set_num_threads(NUM_THREADS);


    // every number from MIN to MAX
    int* numbers = create_array(SIZE);
    int* sito = new int[MAX];
    int* primes = new int[SIZE];

    unsigned int primes_id = 0;

    // primes from 2 to sqrt(MAX)
    for(int i = 2; i * i <= MAX; i++){
        if(isPrime(i))
            primes[primes_id++] = i;        
    }

    int shift = primes[primes_id - 1], block_size;
    block_size = (MAX - shift) / (NUM_THREADS) +1 ;
    double start = omp_get_wtime();

  // __fn_1(block_size, primes_size, shift);
  // __fn_2(block_size, primes_size, shift);
  // __fn_3(block_size, primes_size, shift);
  //__fn_3_fastest(block_size, primes_id, shift);

#pragma omp parallel num_threads(NUM_THREADS) default(none)                     \
    firstprivate(block_size, primes_id, shift) shared(sito, primes)
  for(int i=0 ; i<primes_id; i++) {
    int idx = omp_get_thread_num();
    int p = primes[i];
    int _j = shift + idx * block_size;
    for (int j = -fast_mod(_j, p); j <= block_size; j += p)
      sito[_j + j] = 1;
  }

  double end = omp_get_wtime();

  for(int i=shift ; i<MAX ; ++i)
  {
      if(sito[i] == 0) {
          primes[primes_id++] = i;
      }
  }

  int count = 0;
    for(int i=0; i<MAX; i++){
        if(primes[i]!=0)
            count++; 
    }
    printf("Number of primes numbers: %d\n", count);
    printf("Time: %f sec\n", ((double)(end-start)));

    delete[] primes;
    delete[] numbers;
    delete[] sito;
}

int main() {
    sieve();
}