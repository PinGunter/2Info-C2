#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char** argv) {
	int i,j;
	
	double tiempo;
	struct timespec cgt1, cgt2;

	if (argc != 2) {
		printf("Argumentos incorrectos. Uso: binario <tamaño>");
		exit(-1);
	}

	int n = atoi(argv[1]);

//reserva de memoria dinamica
	double** m = (double**)malloc(n * sizeof(double *));
	double* v1 = (double*)malloc(n * sizeof(double));
	double* v3 = (double*)malloc(n * sizeof(double));

	for (i = 0; i < n; i++) {
		m[i] = (double*)malloc(n * sizeof(double));
	}

	//inicializacion de datos de la matriz y los vectores
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
            if (i < j)
                m[i][j] = 0;    // solo inicializamos los valores del triangulo inferior
            else
			    m[i][j] = 0.1*i*n - 0.1*j*n;
		}
		v1[i] = 0.1*i*n;
		v3[i] = 0;
	}

	// calculo
	clock_gettime(CLOCK_REALTIME, &cgt1);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
            if (i > j)
			    v3[i] += m[i][j] * v1[j];
		}
	}
	clock_gettime(CLOCK_REALTIME, &cgt2);
	tiempo = (double)(cgt2.tv_sec - cgt1.tv_sec) +
		(double)((cgt2.tv_nsec - cgt1.tv_nsec) / (1.e+9));
	// muestra de resultados
	if (n <= 10) {
		printf("Matriz: \n");
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				printf("%f\t", m[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		printf("Vector producto: \n");
		for (i = 0; i < n; i++)
			printf("%f", v1[i]);
		printf("\n");

		printf("Vector resultado: \n");
		for (i = 0; i < n; i++) {
			printf("%f", v3[i]);
		}
		printf("\n");

	}
	else {
		printf("Matriz m[0][0] = %f <--> m[%d][%d] = %f\n",
			m[0][0], n - 1, n - 1, m[n - 1][n - 1]);
		printf("V1[0] = %f <--> V1[%d] = %f\n",
			v1[0], n - 1, v1[n - 1]);
		printf("Resultado V3[0] = %f <--> V3[%d] = %f\n",
			v3[0], n - 1, v3[n - 1]);
	}
	printf("Tiempo: %f11.9\n", tiempo);
//liberacion de memoria dinamica
	for (i = 0; i < n; i++)
		free(m[i]);
	free(m);
	free(v1);
	free(v3);
}
