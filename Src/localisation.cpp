#include "localisation.h"

#include <string.h>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <assert.h>
#include "array2d.h"
#include "kcombinationiterator.h"

#ifndef INFINITY
#define INFINITY 1e+50
#endif

Localisation::Localisation():
  _pInstance(0),
  _aChosenFactories(0),
  _LastAddedFactory(-1),
  _ActualLocalisationCost(-1)
{
}


Localisation::Localisation(Testio &iInstance, bool* iChosenFactories):
  _pInstance(&iInstance),
  _aChosenFactories(0),
  _LastAddedFactory(-1),
  _ActualLocalisationCost(-1)
{
  int nbFactories = _pInstance->NbFactories();
  if (nbFactories) {
    _aChosenFactories = new bool[nbFactories];
    if (iChosenFactories)
      memcpy(_aChosenFactories, iChosenFactories, nbFactories*sizeof(bool));
    else
      memset(_aChosenFactories, 0, nbFactories*sizeof(bool));
  }
}


Localisation::~Localisation()
{
  if (_aChosenFactories)
    delete [] _aChosenFactories; _aChosenFactories=0;
  _pInstance = 0;
}


double Localisation::MinDistance(int iClient)
{
  double m = INFINITY; // Minimum
  int j=0;
  while (j < _pInstance->NbFactories() && !_aChosenFactories[j]) {
    j++;
  }
  if (j < _pInstance->NbFactories()) {
    m = _pInstance->DistanceCF(iClient,j);
    int i;
    for(i = j; i < _pInstance->NbFactories(); i++) {
      if (_aChosenFactories[i]){
	double dist = _pInstance->DistanceCF(iClient,i);
        m = std::min( dist , m ); 
      }
    }
  }
  return m;
}


double Localisation::ComputeLocalisationCost()
{
  double Cost=0;
  int i;
  for (i = 0; i < _pInstance->NbFactories(); i++) {
    if (_aChosenFactories[i])
      Cost = Cost + _pInstance->ImplantationCost(i);
  }
  for (i = 0; i < _pInstance->NbClients(); i++) {
    Cost=Cost+MinDistance(i);
  }
  return Cost;
}


Localisation Localisation::CreateComplementedLocalisation(int iFactory)
{
  Localisation Complemented(*_pInstance, _aChosenFactories);
  Complemented.Complement(iFactory);
  return Complemented;
}


void Localisation::Construction(int iRCLLength)
{
  assert(iRCLLength>0);
  bool stop = false;
  // Array of the cost of adding each factory
  double *Cost=new double[_pInstance->NbFactories()];
  // Array containing the best candidates among the factories
  int* Candidates = new int[iRCLLength];

  while (!stop)
  {
    // Cost of the actual localisation of factories
    _ActualLocalisationCost = ComputeLocalisationCost();
    // Reset the array of the cost of adding each factory
    memset(Cost, 0, _pInstance->NbFactories()*sizeof(double));

    //-- Compute cost of adding factory i
    int i;
    for (i=0; i<_pInstance->NbFactories(); i++)
    {
      if (!_aChosenFactories[i])
      {
	Complement(i); // Add factory number i
	Cost[i] = ComputeLocalisationCost(); //cost of the solution with the ith factories open
	Complement(i); // Remove factory i
      }
      else
      {
	Cost[i] = _ActualLocalisationCost;
      }
    }

    //-- Search of the best candidates that improve the localisation (iRCLLength candidates)
    if (_LastAddedFactory==-1) { // Initialisation of first loop with the highest cost
      int IdxMaxCost = 0;
      for (i = 0; i < _pInstance->NbFactories(); i++) {
	if (Cost[IdxMaxCost] < Cost[i])
	  IdxMaxCost = i;
      }
      int j;
      for (j = 0; j < iRCLLength; j++) {
	Candidates[j] = IdxMaxCost;
      }
    }
    else { // Initialisation of other loops with the last change
      int j;
      for (j = 0; j < iRCLLength; j++) {
	Candidates[j] = _LastAddedFactory; // To add only factories which improve the cost
      }
    }

    for(i=0; i<_pInstance->NbFactories(); i++) // Compute the table of candidates (the iRCLLength better factories)
    {
      int j = 0;
      while (j<iRCLLength && Cost[i]>Cost[Candidates[j]] )
	j++;
      if (j==iRCLLength) continue;
      int k;
      for (k = iRCLLength-1; k > j; k--) {
        Candidates[k]=Candidates[k-1];
      }
      Candidates[j]=i;
    }
    int IdxFactoryToAdd = rand()%iRCLLength;
    if (_aChosenFactories[Candidates[IdxFactoryToAdd]])
      stop = true;
    else
    {
      Complement( Candidates[IdxFactoryToAdd] ); // draw a factory amongst the rcllength best
      _LastAddedFactory = Candidates[IdxFactoryToAdd];
    }
  }

  if (Cost)
    delete [] Cost; Cost = 0;
  if (Candidates)
    delete [] Candidates; Candidates = 0;
}


bool Localisation::NeighbourhoodSearch(int iNSize)
{
  if (iNSize <= 0 || iNSize > std::min(3, _pInstance->NbFactories()) ) {
    std::cout << "It is a stupid use of this method !" << std::endl;
    return false;
  }

  bool FindABetterSolution = false;

  // Cost of the actual localisation of factories
  _ActualLocalisationCost = ComputeLocalisationCost();
  // Best neighbour of current location
  int* BestNeighbour = new int[iNSize];
  int i;
  for (i = 0; i < iNSize; i++)
    BestNeighbour[i] = -1;

  // Iterator on solution of the neighbourhood
  KcombinationIterator NeighbourhoodIt(iNSize, _pInstance->NbFactories());
  while (!NeighbourhoodIt.IsEnded())
  {
    int j;
    for (j = 0; j < iNSize; j++) // Complement some factories to get a solution in the neighbourhood
      Complement(NeighbourhoodIt(j));
    double NewLocalisationCost = ComputeLocalisationCost(); // Compute the cost of the solution
    if (NewLocalisationCost < _ActualLocalisationCost)
    { // Stock the solution if it is better
      for (j = 0; j < iNSize; j++)
	BestNeighbour[j] = NeighbourhoodIt(j);
      _ActualLocalisationCost = NewLocalisationCost;
    }
    for (j = 0; j < iNSize; j++) // Reset the localisation to initial value
      Complement(NeighbourhoodIt(j));

    ++NeighbourhoodIt;
  }

  // Change the localisation to the best localisation in the neighbourhood
  if (BestNeighbour[0] != -1)
  {
    int j;
    for (j = 0; j < iNSize; j++)
      Complement(BestNeighbour[j]);
    FindABetterSolution = true;
  }

  if (BestNeighbour)
    delete [] BestNeighbour; BestNeighbour = 0;

  return FindABetterSolution;
}


void Localisation::LocalSearchAlgorithm(int iMaxSize)
{
  int NeighbourhoodSize = 1;
  while (true)
  {
    if (NeighbourhoodSearch(NeighbourhoodSize))
    {
      NeighbourhoodSize = 1;
      continue;
    }
    else if (NeighbourhoodSize < iMaxSize)
    {
      NeighbourhoodSize++;
      continue;
    }
    else
    {
      break;
    }
  }
}


void Localisation::PrintChosenFactories()
{
  int i;
  std::cout << "Chosen factories : (cost " << ComputeLocalisationCost() << ")" << std::endl;
  for (i = 0; i <_pInstance->NbFactories(); i++) {
    std::cout << _aChosenFactories[i] << " ";
  }
  std::cout << std::endl;
}

