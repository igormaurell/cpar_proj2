#include <stdio.h>
#include <time.h>

void sieve(int n)
{
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    //Init
    int primes[n+1];
    for(int i = 0; i < n+1; i++) primes[i] = 1;
    int k, finish;

    //Process
    for(k = 2; (k*k) <= n; ) {
        for(int j = k*k; j<=n; j++) {
            if(j%k == 0) primes[j] = 0; 
        }
        finish = 1;
        for (int i = k+1; i < n+1; i++) {
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
    printf("PRIMES: ");
    for(int i = 2; i < n+1; i++) {
        if(primes[i] == 1) {
            printf("%d ", i);
        }
    }
    printf("\nTIME: %lf\n", cpu_time_used);
}

int main(){
    int n;
    scanf("%d", &n);

    sieve(n);
    return 0;
}