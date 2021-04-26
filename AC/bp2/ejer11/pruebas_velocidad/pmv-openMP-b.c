#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

//#define VECTOR_GLOBAL

#define VECTOR_DYNAMIC

#ifdef VECTOR_GLOBAL
#define MAX 33554432

double matriz[MAX][MAX], v1[MAX], v3[MAX];
#endif

int main(int argc, char** argv) {
	int i,j;
	
	double tiempo;
	double inicio, final;

	if (argc != 2) {
		printf("Argumentos incorrectos. Uso: binario <tamaño>");
		exit(-1);
	}

	int dimension = atoi(argv[1]);

//reserva de memoria dinamica
#ifdef VECTOR_DYNAMIC
	double** m = (double**)malloc(dimension * sizeof(double *));
	double* v1 = (double*)malloc(dimension * sizeof(double));
	double* v3 = (double*)malloc(dimension * sizeof(double));

	for (i = 0; i < dimension; i++) {
		m[i] = (double*)malloc(dimension * sizeof(double));
	}
#endif

	//inicializacion de datos de la matriz y los vectores
	for (i = 0; i < dimension; i++) {
		v1[i] = 0.1*i;
		v3[i] = 0;
	#pragma omp parallel
		for (j = 0; j < dimension; j++) {
			m[i][j] = 0.1*i - 0.1*j;
		}
	}

	// calculo
	inicio = omp_get_wtime();
	int aux = 0;
	for (i = 0; i < dimension; i++) {
		#pragma omp parallel firstprivate(aux)
		{
			#pragma omp for
			for (j = 0; j < dimension; j++) {
				aux += m[i][j] * v1[j];
			}

			#pragma omp atomic
			v3[i] += aux;
		}
	}

	final = omp_get_wtime();
	tiempo = final - inicio;

	// muestra de resultados
	if (dimension <= 10) {
		printf("Matriz: \n");
		for (i = 0; i < dimension; i++) {
			for (j = 0; j < dimension; j++) {
				printf("%f\t", m[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		printf("Vector producto: \n");
		for (i = 0; i < dimension; i++)
			printf("%f", v1[i]);
		printf("\n");

		printf("Vector resultado: \n");
		for (i = 0; i < dimension; i++) {
			printf("%f", v3[i]);
		}
		printf("\n");

	}
	else {
		printf("Matriz m[0][0] = %f <--> m[%d][%d] = %f\n",
			m[0][0], dimension - 1, dimension - 1, m[dimension - 1][dimension - 1]);
		printf("V1[0] = %f <--> V1[%d] = %f\n",
			v1[0], dimension - 1, v1[dimension - 1]);
		printf("Resultado V3[0] = %f <--> V3[%d] = %f\n",
			v3[0], dimension - 1, v3[dimension - 1]);
	}
	printf("Tiempo: %f11.9\n", tiempo);
//liberacion de memoria dinamica
#ifdef VECTOR_DYNAMIC
	for (i = 0; i < dimension; i++)
		free(m[i]);
	free(m);
	free(v1);
	free(v3);
#endif
}