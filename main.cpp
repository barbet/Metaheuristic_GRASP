#include <stdio.h>   // Standard Input/Output Header
#include <stdlib.h>  // C Standard General Utilities Library
//#include <omp.h>     // Open Multi-Processing Library
#include <algorithm>
#include <iostream>
#include <time.h>    //time
#include "testio.h"  // Test Input/Output Header
#include "localisation.h"
#include "kcombinationiterator.h"

/** Mets tes tests dedans Tristan :) */
void Test_Tristan()
{
  Testio myTestio("TestCases/Input/cap71.txt");
  Localisation myLoc(myTestio);
  for (int i = 0; i < myTestio.NbFactories(); i++) {
    std::cout << myTestio.ImplantationCost(i) << std::endl;
  }
  myLoc.Construction(1);
  myLoc.PrintChosenFactories();
  myLoc.NeighbourhoodSearch(1);
  myLoc.PrintChosenFactories();
  myLoc.LocalSearchAlgorithm(2);
  myLoc.PrintChosenFactories();
}


/** Mets tes tests dedans Etienne :) */
void Test_Etienne()
{
  Testio myTestio("TestCases/Input/cap71.txt");
  KcombinationIterator I(3,5);
  /*
    while (!I.IsEnded())
    {
      std::cout << I(0) << I(1) << I(2) << std::endl;
      I.Print();
      ++I;
    }
    printf("Nombre de processeurs : %d \n",omp_get_num_procs());
    printf("Nombre de thread actifs : %d \n",omp_get_num_threads());
    int n;
    pragma omp parallel for schedule(dynamic,2)
    for(n=0;n<18;n++){
      printf("Element %d traité par le thread %d \n",n,omp_get_thread_num());
    }
  */
}


int main (int argc, char const *argv[]){
  /* initialize random seed: */
  srand (time(NULL));
  
  Test_Tristan();
  Test_Etienne();
  return EXIT_SUCCESS;
}
