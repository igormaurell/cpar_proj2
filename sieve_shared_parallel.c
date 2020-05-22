#include <stdio.h>
#include <time.h>
#include <omp.h> 

//Blocks division Macros
#define BLOCK_LOW(i,p,n) ((i)*(n)/(p))
#define BLOCK_HIGH(i,p,n) (BLOCK_LOW((i)+1,p,n)-1)
#define BLOCK_SIZE(i,p,n) (BLOCK_LOW(i+1,p,n)-BLOCK_LOW(i,p,n))
#define BLOCK_OWNER(index,p,n) (((p)*(index)+1)-1)/(n))


void sieve(int n)
{
    clock_t start, end;
    double cpu_time_used;

    int primes[n+1];
    int k, i, j, finish = 0;

    int procs = omp_get_num_procs();
    if((n+1) < procs) omp_set_num_threads(n+1);

    /*for(int a = 0; a < procs; a++){
        printf("THREAD %d\n", a);
        printf("block_low: %d ", BLOCK_LOW(a, procs, n+1));
        printf("block_high: %d ", BLOCK_HIGH(a, procs, n+1));
        printf("block_size: %d\n", BLOCK_SIZE(a, procs, n+1));
    }*/

    start = clock();
    #pragma omp parallel private(i,j)
    {
        //printf("Welcome to GFG from thread = %d\n", 
        //            omp_get_thread_num()); 
        #pragma omp parallel for
        for(i = BLOCK_LOW(omp_get_thread_num(), omp_get_num_threads(), n+1); i < BLOCK_SIZE(omp_get_thread_num(), omp_get_num_threads(), n+1); i++) {
            primes[i] = 1;
        }
        k = 2;

        while((k*k) <= n && finish == 0) {
            #pragma omp parallel for
            for(j = BLOCK_LOW(omp_get_thread_num(), omp_get_num_threads(), n+1); j < BLOCK_SIZE(omp_get_thread_num(), omp_get_num_threads(), n+1); j++) {
                if(j%k == 0 && j >= k*k) primes[j] = 0; 
            }
            #pragma omp master
            {
                //printf("%d", k);
                /*for(i = 0; i < n+1; i++) {
                    printf("%d ", i);
                }*/
                finish = 1;
                for (i = k+1; i < n+1; i++) {
                    if(primes[i] == 1) {
                        finish = 0;
                        k = i;
                        break;
                    }
                }
            }
            #pragma omp barrier
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    //Out
    int c = 0;
    for(int i = 2; i < n+1; i++) {
        if(primes[i] == 1) {
            c++;
        }
    }
    printf("PRIMES: %d\n", c);
    printf("TIME: %lf\n", cpu_time_used);
}

int main(){
    int n;
    scanf("%d", &n);

    sieve(n);
    return 0;
}