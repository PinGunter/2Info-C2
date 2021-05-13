#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif

int main(int argc, char **argv)
{
    int i, n=200, chunk, a[n], suma=0;
    
    if(argc < 3)
    {
        fprintf(stderr,"\nFalta iteraciones o chunk\n");
        exit(-1);
    }

    n = atoi(argv[1]);
    if (n>200)
        n=200;

    chunk = atoi(argv[2]); 

    for (i=0; i<n; i++)
        a[i] = i; 
    
    omp_sched_t kind;

    #pragma omp parallel for firstprivate(suma) \
                lastprivate(suma) schedule(dynamic,chunk)
    for (i=0; i<n; i++)
    {
        if (i==0)
        {
            printf("ANTES DE MODIFICAR\n");
            omp_get_schedule(&kind,&chunk);
            printf("Dentro de PARALLEL:\ndyn-var: %d, nthreads-var: %d run-sched-var : kind: %d, chunk: %d\n",
                omp_get_dynamic(), omp_get_max_threads(), kind, chunk );
        }

        if (i==2){
            omp_set_dynamic(1);
            omp_set_num_threads(3);
            omp_set_schedule(omp_sched_guided,4);

            printf("DESPUÉS DE MODIFICAR\n");
            omp_get_schedule(&kind,&chunk);
            printf("Dentro de PARALLEL:\ndyn-var: %d, nthreads-var: %d run-sched-var : kind: %d, chunk: %d\n",
                omp_get_dynamic(), omp_get_max_threads(), kind, chunk );
        }
        suma = suma + a[i];
        printf(" thread %d suma a[%d]=%d suma=%d \n",
               omp_get_thread_num(),i,a[i],suma);
    }
    omp_get_schedule(&kind,&chunk);
    printf("Fuera de PARALLEL:\ndyn-var: %d, nthreads-var: %d run-sched-var : kind: %d, chunk: %d\n",
        omp_get_dynamic(), omp_get_max_threads(), kind, chunk );

    printf("MODIFICADO DESPUÉS FUERA de Parallel\n");
    omp_set_dynamic(0);
    omp_set_num_threads(5);
    omp_set_schedule(omp_sched_dynamic,1);

    omp_get_schedule(&kind,&chunk);
    printf("dyn-var: %d, nthreads-var: %d run-sched-var : kind: %d, chunk: %d\n",
        omp_get_dynamic(), omp_get_max_threads(), kind, chunk );
    
    
    printf("Fuera de 'parallel for' suma=%d\n",suma); 
}

