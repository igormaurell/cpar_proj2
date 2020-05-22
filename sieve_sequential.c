#include <stdio.h>
#include <time.h>

#define MAX_SIZE (unsigned long)2E10

unsigned char primes[MAX_SIZE];

void sieve(unsigned long n)
{
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    //Init
    unsigned char finish;
    unsigned long i, k, j;
    for(i = 0; i < n+1; i++) primes[i] = 1;

    //Process
    /*for(k = 2; (k*k) <= n; ) {
        for(j = k*k; j<=n; j++) {
            if(j%k == 0) primes[j] = 0; 
        }
        finish = 1;
        for (i = k+1; i < n+1; i++) {
            if(primes[i] == 1) {
                finish = 0;
                k = i;
                break;
            }
        }
        if(finish == 1) break;
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    //Out
    unsigned long c = 0;
    for(int i = 2; i < n+1; i++) {
        if(primes[i] == 1) {
            c++;
        }
    }
    printf("PRIMES: %lu\n", c);
    printf("TIME: %lf\n", cpu_time_used);*/
}

int main(){
    unsigned long n;
    scanf("%lu", &n);

    sieve(n);
    return 0;
}