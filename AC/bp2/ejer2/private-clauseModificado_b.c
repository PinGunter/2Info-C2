#include <stdio.h>
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif

int main()
{
    int i,n = 7;
    int a[n], suma = 1310;

    for (i=0; i < n; i++)
        a[i] = i;
    
    #pragma omp parallel private(suma)
    {
        #pragma omp for
        for (i=0; i < n; i++){
            suma = suma + a[i];
            printf(
                "thread %d suma a[%d]/", omp_get_thread_num(), i);
        }
        printf(
            "\n* thread %d suma=%d", omp_get_thread_num(), suma);
        
    }
    printf("\n");

    printf("--- fuera region parallel --- \n thread %d suma=%d\n", omp_get_thread_num(), suma);
}
