#include <stdlib.h>	
#include <stdio.h>
#include <time.h>

struct tipo {
        int a;
        int b;
};
 
int main(int argc, char ** argv)
{
    //control de errores
    if (argc != 3){
        printf("Faltan argumentos: N y M\n");
        exit(-1);
    }

    // declaraciones de variables
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    struct tipo s[N];
    int R[M];
    struct timespec inicio,fin; double tiempo;

    // inicializacion
    if (N <= 8){
        for (int i=0; i < N; i++){
            s[i].a = N * 0.1 + i * 0.1;
            s[i].b = N * 0.1 - i * 0.1;

        }
    } else{
        for (int i=0; i < N; i++){
            s[i].a = drand48();
            s[i].b = drand48();

        }
    }
    for (int i=0; i < M; i++){
        R[i] = 0;
    }


    //medicion
    clock_gettime(CLOCK_REALTIME,&inicio);
    int ii, i, X1, X2;
    for (ii=0; ii<M;ii++) {
        X1=0; X2=0;
        for(i=0; i<N;i++)  X1+=2*s[i].a+ii;
        for(i=0; i<N;i++)  X2+=3*s[i].b-ii;

        if (X1<X2)  R[ii]=X1;  else  R[ii]=X2;
    }
    clock_gettime(CLOCK_REALTIME,&fin);
    // fin medicion
    tiempo = (double) (fin.tv_sec-inicio.tv_sec)+
       (double) ((fin.tv_nsec-inicio.tv_nsec)/(1.e+9));

    printf("Tiempo: %f\n", tiempo);
}
