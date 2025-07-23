/*
Переслать вектор, размерности M, N процессам, используя различные виды связи между процессами. Элементы вектора задаются произвольно. Элементы вектора пересылаемого и принятого вектора, а также время выполнения должны быть выведены на экран.
M = 3, N = 3, Функция - MPI_Send
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
//var 1
#define M 3
int main(int argc, char* argv[])
{
int n = 1;
int vec[M];
int numprocs, myid;
int res_vec[M] = {0};
double end_t, send_t;
MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
MPI_Comm_rank(MPI_COMM_WORLD, &myid);
MPI_Status status;
for (size_t i = 0; i < M; i++)
vec[i] = myid;
printf("Process %d init vector:\n", myid);
for (size_t i = 0; i < M; i++)
printf("%d ", vec[i]);
printf("\n\n");
send_t = MPI_Wtime();
if (myid == 0)
{
for (int i = 1; i < numprocs; i++)
MPI_Send(vec, M, MPI_INT, i, 1, MPI_COMM_WORLD);
}
else
{
MPI_Recv(res_vec, M, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
end_t = MPI_Wtime();
printf("Process %d result vector:\n", myid);
for (size_t i = 0; i < M; i++)
printf("%d ", res_vec[i]);
printf("\nTime taken: %f\n\n", end_t - send_t);
}
MPI_Finalize();
}
