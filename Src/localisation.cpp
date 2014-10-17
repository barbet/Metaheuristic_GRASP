#include "localisation.h"

#include <string.h> // To use memset

Localisation::Localisation(int iNbFactories):
  _NbFactories(iNbFactories),
  _aTab(0)
{
  if (_NbFactories)
  {
    _aTab = new bool[_NbFactories];
    memset(_aTab, 0, _NbFactories*sizeof(bool));
  }
}
  
Localisation::~Localisation()
{
  if (_aTab)
    delete [] _aTab; _aTab=0;
}

void Localisation::Resize(int iNbFactories)
{
  if (_aTab)
    delete [] _aTab; _aTab=0;
  _NbFactories = iNbFactories;
  if (_NbFactories>0)
  {
    _aTab = new double[_NbFactories];
    memset(_aTab, 0, _NbFactories*sizeof(double));
  }
}

void Localisation::Construction()
{
  // TODO
}

void Localisation::NeighbourhoodSearch()
{
  // TODO
}

