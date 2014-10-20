#include "localisation.h"

#include <string.h>
#include <algorithm>
#include <cstdlib>
#include "array2d.h"

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
  double m = -1; // Minimum
  int j=0;
  while (j < _pInstance->NbFactories() && !_aChosenFactories[j]) {
    j++;
  }
  if (j < _pInstance->NbFactories()) {
    m = _pInstance->DistanceCF()(iClient,j);
    int i;
    for(i = j; i < _pInstance->NbFactories(); i++) {
      if (_aChosenFactories[i])
        m = std::min( _pInstance->DistanceCF()(iClient,i) , m ); 
    }
  }
  return m;
}


double Localisation::ComputeLocalisationCost()
{
  double Cost=0;
  int i;
  for (i = 0; i<_pInstance->NbClients(); i++) {
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
  bool stop = false;
  // Array of the cost of adding each factory
  double *Cost=new double[_pInstance->NbClients()];
  // Array containing the best candidates among the factories
  int* Candidates = new int[iRCLLength];

  while (!stop)
  {
    // Cost of the actual localisation of factories
    _ActualLocalisationCost = ComputeLocalisationCost();
    // Reset the array of the cost of adding each factory
    memset(Cost, 0, _pInstance->NbClients()*sizeof(double));

    //-- Compute cost of adding factory i
    int i;
    for (i=0; i<_pInstance->NbClients(); i++)
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
      for (i = 0; i < _pInstance->NbClients(); i++) {
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
	Candidates[j] = _LastAddedFactory;
      }
    }

    for(i=0; i<_pInstance->NbClients(); i++) // Compute the table of candidates (the iRCLLength better factories)
    {
      int j = 0;
      while (j<iRCLLength && Cost[i]>Cost[Candidates[j]] ) j++;
      if (j==iRCLLength) continue;
      int k;
      for (k = iRCLLength-1; k > j; k--) {
	    Candidates[k]=Candidates[k-1];
      }
      Candidates[j]=i;
    }
    int IdxFactoryToAdd = rand()%iRCLLength;
    if (_aChosenFactories[IdxFactoryToAdd])
      stop = true;
    else
      Complement( rand()%iRCLLength ); // draw a factory amongst the rcllength best
  }

  if (Cost)
    delete [] Cost; Cost = 0;
  if (Candidates)
    delete [] Candidates; Candidates = 0;
}

void Localisation::NeighbourhoodSearch()
{
  // TODO
}


