//Сгенерировать в каждом из N процессов вектор чисел. Размерность вектора – М. Произвести поэлементную обработку всех векторов и поместить результирующий вектор в каком-либо процессе. В работе использовать средства MPI для организации распределенных вычислений. N = 4 M = 20 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#define M 20
int main(int argc, char* argv[])
{
int n = 1;
short int vec[M];
short int res_vec[M] = { 0 };
int numprocs, myid;
srand(time(NULL));
MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
MPI_Comm_rank(MPI_COMM_WORLD, &myid);
for (size_t i = 0; i < M; i++)
vec[i] = myid+1;
printf("Process %d init vector:\n", myid);
for (size_t i = 0; i < M; i++)
printf("%d ", vec[i]);
printf("\n\n");
MPI_Reduce(vec, res_vec, M, MPI_SHORT, MPI_PROD, 0, MPI_COMM_WORLD);
if (myid == 0) {
printf("---------------------------------\n");
printf("Process %d result vector:\n", myid);
for (size_t i = 0; i < M; i++) printf("%d ", res_vec[i]);
printf("\n---------------------------------\n");
}
MPI_Finalize();
}
