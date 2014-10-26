#include <stdio.h>   // Standard Input/Output Header
#include <stdlib.h>  // C Standard General Utilities Library
//#include <omp.h>     // Open Multi-Processing Library
#include <algorithm>
#include <iostream>
#include <time.h>    //time
#include "testio.h"  // Test Input/Output Header
#include "localisation.h"
#include "kcombinationiterator.h"

void Genetic(Localisation* TableauLoc ,int TableauLocSize, double MutationRate,int NbFactories);

/** Mets tes tests dedans Tristan :) */
void Test_Tristan()
{
  Testio myTestio("TestCases/Input/cap71.txt");
  Localisation myLoc(myTestio);
  for (int i = 0; i < myTestio.NbFactories(); i++){
    std::cout << myTestio.ImplantationCost(i) << std::endl;
  }

  int TableauLocSize = 5;
 
  Localisation* TableauLoc = new Localisation[TableauLocSize];
  

  myLoc.Construction(3);
  TableauLoc[0]=myLoc;
  myLoc.PrintChosenFactories();
  myLoc.NeighbourhoodSearch(1);
  TableauLoc[1]=myLoc;
  myLoc.PrintChosenFactories();
  myLoc.LocalSearchAlgorithm(2);
  TableauLoc[2]=myLoc;
  myLoc.PrintChosenFactories();
  TableauLoc[3]=TableauLoc[2];
  Genetic(TableauLoc,4,0.999,myTestio.NbFactories());

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




void Genetic(Localisation* TableauLoc ,int TableauLocSize, double MutationRate,int NbFactories)  // tableauLocSize has to be even
{
  double * aCost = new double[TableauLocSize];   //array of localisation costs
  bool * aSelected = new bool[TableauLocSize];  // array keeping in memory who has been used in reproduction
  int i;
  for (i=0; i<TableauLocSize; i++)  // initialisation
  {
    aCost[i]=(TableauLoc[i]).ComputeLocalisationCost();
    aSelected[i]=0;
  }
  int Compteur=0;
  while(Compteur<10) 
  {
    Compteur++;
    for (i=0; i<int(TableauLocSize/2); i++)
    {
      // selection of individuals
      int Individual1=rand()%TableauLocSize;
      while (aSelected[Individual1] && Individual1<TableauLocSize) Individual1++;  // individual1 is chosen amongst localisation that have not been selected yet
      if (Individual1==TableauLocSize) Individual1=0;  // loop if we arrive at the end
      while (aSelected[Individual1] && Individual1<TableauLocSize) Individual1++;
      int Individual2=rand()%TableauLocSize;
      while (aSelected[Individual2] && Individual1<TableauLocSize) Individual2++;  // individual2 is chosen amongst localisation that have not been selected yet
      if (Individual2==TableauLocSize) Individual1=0;  // loop if we arrive at the end
      while (aSelected[Individual2] && Individual1<TableauLocSize) Individual2++;
      
      // Indivudual1 is the best of the two
      if (aCost[Individual1]>aCost[Individual2])
      {
        int TmpIndividual=Individual1;
        Individual2=Individual1;
        Individual1=TmpIndividual;
      }

      //reproduction=> swap sequence between crossingpoint1 and crossingpoint2for individual2
      int CrossingPoint1=rand()%(NbFactories-1);
      int CrossingPoint2=CrossingPoint1+rand()%(NbFactories-CrossingPoint1-1);
      int j=0;
      for (j=CrossingPoint1; j<CrossingPoint2;j++)  //need to be checked
      {
        (TableauLoc[Individual2])(j)=(TableauLoc[Individual1])(j);
      }
      //Mutation
      int Rdm=rand();
      if (Rdm<MutationRate) (TableauLoc[Individual1]).Complement(j); // mutate the worst localisation with MutationRate
    
    }

  }
}





int main (int argc, char const *argv[]){
  /* initialize random seed: */
  srand (time(NULL));
  
  Test_Tristan();
  Test_Etienne();
  return EXIT_SUCCESS;
}
