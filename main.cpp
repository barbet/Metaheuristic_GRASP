#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
int main (int argc, char const *argv[]){
  printf("Nombre de processeurs : %d \n",omp_get_num_procs());
  printf("Nombre de thread actifs : %d \n",omp_get_num_threads());
  int n;
  #pragma omp parallel for schedule(dynamic,2)
  for(n=0;n<18;n++){
    printf("Element %d traité par le thread %d \n",n,omp_get_thread_num());
  }
  return EXIT_SUCCESS;
}
