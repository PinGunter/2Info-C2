#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char ** argv){
    if (argc != 2){
        printf("Error en la llamda. Hace falta el parámetro N (tamaño de vector)\n");
        exit(EXIT_FAILURE);
    }

    struct timespec inicio, fin;
    double tiempo;

    const int N = atoi(argv[1]);
    double a = 13.42;
    double x[N];
    double y[N];

    // inicalizacion de los vectores
    for (int i=0; i < N; ++i){
        srand48(time(NULL));
        x[i] = drand48();
        srand48(time(NULL));;
        y[i] = drand48();
    }
    clock_gettime(CLOCK_REALTIME, &inicio);
    for (int i=0;i<N;i++) y[i]= a*x[i] + y[i];
    clock_gettime(CLOCK_REALTIME, &fin);

    tiempo = (double) (fin.tv_sec-inicio.tv_sec)+
       (double) ((fin.tv_nsec-inicio.tv_nsec)/(1.e+9));
    printf("Tiempo: %11.9f\n",tiempo);
}