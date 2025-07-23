/* Вычисление константы ПИ c точностью 0,001 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
double calculate_pi(void) {
static const unsigned total = 100000;
unsigned result = 0;
#pragma omp parallel reduction(+:result)
{
int count = total / omp_get_num_threads();
int i;
for (i = 0; i < count; ++i) {
double x = (double)rand() / RAND_MAX;
double y = (double)rand() / RAND_MAX;
if (x * x + y * y < 1.0)
result++;
}
}
return 4.0 * result / total;
}
int main(int argc, char const* argv[])
{
omp_set_num_threads(16);
double pi_approx = calculate_pi();
printf("Pi approximation: %.4f\n", pi_approx);
return 0;
}
