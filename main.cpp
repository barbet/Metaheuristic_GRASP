#include <stdio.h>   // Standard Input/Output Header
#include <stdlib.h>  // C Standard General Utilities Library
//#include <omp.h>     // Open Multi-Processing Library
#include <algorithm>
#include <iostream>
#include <time.h>    //time
#include "testio.h"  // Test Input/Output Header
#include "localisation.h"


/** Mets tes tests dedans Tristan :) */
void Test_Tristan()
{
  Testio myTestio("TestCases/Input/cap71.txt");
  Localisation myLoc(myTestio);
  myLoc.Construction(5);
  myLoc.PrintChosenFactories();
}


/** Mets tes tests dedans Etienne :) */
void Test_Etienne()
{
  Testio myTestio("TestCases/Input/cap71.txt");
  /*printf("Nombre de processeurs : %d \n",omp_get_num_procs());
  printf("Nombre de thread actifs : %d \n",omp_get_num_threads());
  int n;
  #pragma omp parallel for schedule(dynamic,2)
  for(n=0;n<18;n++){
    printf("Element %d traité par le thread %d \n",n,omp_get_thread_num());
  }*/
}


int main (int argc, char const *argv[]){
  /* initialize random seed: */
  srand (time(NULL));
  
  Test_Tristan();
  //Test_Etienne();
  return EXIT_SUCCESS;
}
