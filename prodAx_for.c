#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


 void prodAx(int m, int n, double * restrict A, double * restrict x,
   double * restrict b);

 int main(int argc, char *argv[]) {
   double *A,*x,*b;
   int i, j, m, n;

   printf("Ingrese las dimensiones m y n de la matriz: ");
   scanf("%d %d",&m,&n);

   //---- Asignación de memoria para la matriz A ----
   if ( (A=(double *)malloc(m*n*sizeof(double))) == NULL )
    perror("memory allocation for A");

   //---- Asignación de memoria para el vector x ----
   if ( (x=(double *)malloc(n*sizeof(double))) == NULL )
    perror("memory allocation for x");

   //---- Asignación de memoria para el vector b ----
   if ( (b=(double *)malloc(m*sizeof(double))) == NULL )
    perror("memory allocation for b");

  printf("Initializing matrix A and vector x\n");

  //---- Inicialización con elementos aleatorios entre 1-7 y 1-13
  for (j=0; j<n; j++)
    x[j] = rand()%7+1;

  for (i=0; i<m; i++)
    for (j=0; j<n; j++)
      A[i*n+j] = rand()%13+1;

  double start_time = omp_get_wtime();

  printf("Calculando el producto Ax para m = %d n = %d\n", m, n);
  (void) prodAx(m, n, A, x, b); 

  double end_time = omp_get_wtime();
  double elapsed_time = end_time - start_time;

  printf("Tiempo total: %f segundos\n", elapsed_time);

  // Liberar memoria
  free(A);
  free(x);
  free(b);

  return 0;
}

/* ------------------------
 * prodAx
 * ------------------------
 */
void prodAx(int m, int n, double * restrict A, double * restrict x,
  double * restrict b){

    int i, j;

    for(i=0; i<m; i++){
      b[i]=0.0;

      #pragma omp parallel for
      for(j=0; j<n; j++){
        b[i] += A[i*n + j] * x[j];
      }
    }
  }//----prodAx----