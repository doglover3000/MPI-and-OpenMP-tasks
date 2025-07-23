/* Реализовать и распараллелить с помощью технологии OpenMP различные операции над векторами размерности N.
n = 5, Тип элемента матрицы - Число, с плавающей запятой; Тип сортировки - Скалярное произведение 2х векторов */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <omp.h>
#define N 5
void print_vector(const double* vec, size_t size, const char* start_text) {
printf("%s", start_text);
for (size_t i = 0; i < size; i++) printf("%.2f ", vec[i]);
printf("\n\n");
}
int main() {
double a[N], b[N];
size_t i;
double sum = 0;
srand(time(NULL));
for (i = 0; i < N; i++) {
a[i] = (rand() % 10000 + 1)*0.01;
b[i] = (rand() % 10000 + 1)*0.01;
}
print_vector(a, N, "vector 1: ");
print_vector(b, N, "vector 2: ");
#pragma omp parallel for schedule(static, 2) shared(a, b) reduction(+:sum) private(i)
for (i = 0; i < N; i++) sum += a[i] * b[i];
printf("sum = %.4f\n", sum);
}
