/*Произвести сортировку элементов в столбцах (или строках) матрицы размерности NxM, с использованием распределения вычислений между процессами средствами MPI
N = 3, M = 10, Тип элемента матрицы - Целый байтовый, Тип сортировки - По убыванию */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <mpi.h>
//var 1
#define ROWS 3
#define COLS 10
void swap(char* a, char* b) {
char tmp = *a;
*a = *b;
*b = tmp;
}
void sort(char* mass, size_t size) {
for (size_t i = 0; i < size; i++)
for (size_t j = 0; j < size - 1 - i; j++) {
if (*(mass + j) < *(mass + j + 1))
swap(mass + j, mass + j + 1);
}
}
int main(int argc, char* argv[])
{
char sendbuf[ROWS][COLS];
int allprocs, rank, procs, ost = 0;
char* sorted_buf;
int* sendcounts, * displs;
srand(time(NULL));
MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &allprocs);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
if (rank == 0) {
printf("Init matrix:\n");
for (size_t i = 0; i < ROWS; i++) {
for (size_t j = 0; j < COLS; j++) {
sendbuf[i][j] = 'A' + rand() % 24;
printf("%3d ", sendbuf[i][j]);
}
printf("\n");
}
printf("\n");
}
if (ROWS >= allprocs) {
ost = ROWS % allprocs;
procs = allprocs;
}
else
procs = ROWS;
if (rank < procs) {
sendcounts = (int*)calloc(allprocs, sizeof(int));
displs = (int*)malloc(allprocs * sizeof(int));
for (size_t i = 0; i < procs; i++) {
if (ROWS >= allprocs)
sendcounts[i] = ROWS / allprocs * COLS;
else
sendcounts[i] = COLS;
if (i > 0 && ost > 0) {
if (i <= ost)
displs[i] = i * sendcounts[i] + i * COLS;
else
displs[i] = i * sendcounts[i] + ost * COLS;
} else
displs[i] = i * sendcounts[i];
if (i < ost)
sendcounts[i] += COLS; ost--;
}
sorted_buf = (char*)malloc(sendcounts[rank] * sizeof(short int));
MPI_Scatterv(sendbuf, sendcounts, displs, MPI_BYTE, sorted_buf, sendcounts[rank], MPI_BYTE, 0, MPI_COMM_WORLD);
for (size_t i = 0; i < (*sendcounts); i += COLS)
sort(sorted_buf + i, COLS);
MPI_Gatherv(sorted_buf, sendcounts[rank], MPI_BYTE, sendbuf,
sendcounts, displs, MPI_BYTE, 0, MPI_COMM_WORLD);
free(sorted_buf);
free(sendcounts);
free(displs);
}
if (rank == 0) {
printf("Sorted matrix:\n");
for (size_t i = 0; i < ROWS; i++) {
for (size_t j = 0; j < COLS; j++)
printf("%3d ", sendbuf[i][j]);
printf("\n");
}
printf("\n");
}
MPI_Finalize();
}
