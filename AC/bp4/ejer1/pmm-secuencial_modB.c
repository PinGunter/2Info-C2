#include <stdlib.h>	// biblioteca con funciones atoi(), malloc() y free()
#include <stdio.h>	// biblioteca donde se encuentra la función printf()
#include <time.h>	// biblioteca donde se encuentra la función clock_gettime() 
#define VECTOR_DYNAMIC	// descomentar para que los vectores sean variables ...
			// dinámicas (memoria reutilizable durante la ejecución)

#ifdef VECTOR_GLOBAL
#define MAX 33554432	//=2^25
//#define MAX 4294967295  //=2^32 -1
   
double m1[MAX], m2[MAX], m3[MAX]; 
#endif
int main(int argc, char** argv){ 
  
  int i; 

  struct timespec inicio,fin; double tiempo; //para tiempo de ejecución

  //Leer argumento de entrada (nº de componentes del vector)
  if (argc<2){	
    printf("Faltan nº componentes del vector\n");
    exit(-1);
  }
  
  unsigned int n = atoi(argv[1]);	// Máximo N =2^32-1=4294967295 (sizeof(unsigned int) = 4 B)
  //printf("Tamaño Vectores:%u (%u B)\n",N, sizeof(unsigned int)); 
  #ifdef VECTOR_LOCAL
  double m1[N], m2[N], m3[N];   // Tamaño variable local en tiempo de ejecución ...
				// disponible en C a partir de C99 
  #endif
  #ifdef VECTOR_GLOBAL
  if (N>MAX) N=MAX;
  #endif
  #ifdef VECTOR_DYNAMIC
  double **m1, **m2, **m3;
  m1 = (double**) malloc(n*sizeof(double*));// malloc necesita el tamaño en bytes
  m2 = (double**) malloc(n*sizeof(double*));
  m3 = (double**) malloc(n*sizeof(double*));
  if ((m1 == NULL) || (m2 == NULL) || (m3 == NULL)) {	
    printf("No hay suficiente espacio para los vectores \n");
    exit(-2);
  }
  #endif
 
  //Reserva de memoria de las matrices
  for (int i=0; i < n; ++i){
    m1[i] = (double *) malloc (n*sizeof(double));
    m2[i] = (double *) malloc (n*sizeof(double));
    m3[i] = (double *) malloc (n*sizeof(double));
  }

  //inicializacion de los datos
  if (n <= 8){
    for (int i=0; i < n; i++){
      for (int j=0; j < n; j++){
        m1[i][j] = n * 0.1 + i * 0.1;
        m2[i][j] = n * 0.1 - i * 0.1;
        m3[i][j] = 0;
      }
    }
  } else{
    for (int i=0; i < n; ++i){
      for (int j=0; j < n; ++j){
        m1[i][j] = drand48();
        m2[i][j] = drand48();
        m3[i][j] = 0;
      }
    }
  }

  //calculo del producto
  clock_gettime(CLOCK_REALTIME,&inicio);
  
  for (int i=0; i < n; ++i){
    for (int k=0; k < n; ++k){
      for (int j=0; j < n; ++j){
        m3[i][j] += m1[i][k] * m2[k][j];
      }
    }
  }
  
  clock_gettime(CLOCK_REALTIME,&fin);
  tiempo=(double) (fin.tv_sec-inicio.tv_sec)+
       (double) ((fin.tv_nsec-inicio.tv_nsec)/(1.e+9));

  //Imprimir resultado de la suma y el tiempo de ejecución

  if (n <= 10){
    printf("MATRIZ 1\n");
    for (int i=0; i < n; ++i){
      for (int j=0; j < n; ++j)
        printf("%11.9f - ", m1[i][j]);
      printf("\n");
    }

    printf("MATRIZ 2\n");
    for (int i=0; i < n; ++i){
      for (int j=0; j < n; ++j)
        printf("%11.9f - ", m2[i][j]);
      printf("\n");
    }

    printf("MATRIZ RESULTADO\n");
    for (int i=0; i < n; ++i){
      for (int j=0; j < n; ++j)
        printf("%11.9f - ", m3[i][j]);
      printf("\n");
    }

    printf("Tiempo: %f s\n", tiempo);
  } else{
    printf("MATRIZ 1\n");
    printf("m1[0][0] = %11.9f --> m1[%d][%d] = %11.9f\n", m1[0][0], n-1, n-1, m1[n-1][n-1]);

    printf("MATRIZ 2\n");
    printf("m2[0][0] = %11.9f --> m2[%d][%d] = %11.9f\n", m2[0][0], n-1, n-1, m2[n-1][n-1]);

    printf("MATRIZ RESULTADO\n");
    printf("m3[0][0] = %11.9f --> m3[%d][%d] = %11.9f\n", m3[0][0], n-1, n-1, m3[n-1][n-1]);

    printf("Tiempo :%f s\n", tiempo);
  }
 

  #ifdef VECTOR_DYNAMIC
  for (int i=0; i < n; i++){
    free(m1[i]);
    free(m2[i]);
    free(m3[i]);
  }

  free(m1); free(m2); free(m3);
  #endif
  return 0; 
}
