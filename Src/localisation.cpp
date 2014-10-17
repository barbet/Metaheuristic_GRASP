#include "localisation.h"

#include <string.h>
#include <algorithm>

Localisation::Localisation():
  _pInstance(0),
  _aChosenFactories(0)
{
}


Localisation::Localisation(Testio &iInstance, bool* iChosenFactories):
  _pInstance(&iInstance),
  _aChosenFactories(0)
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
  double m = _pInstance->DistanceCF()(iClient,0);
  int j;
  for(j = 1; j < _pInstance->NbClients(); j++) {
    m = std::min( _pInstance->DistanceCF()(iClient,j) , m ); 
  }
  return m;
}


Localisation Localisation::CreateComplementedLocalisation(int iFactory)
{
  Localisation Complemented(*_pInstance, _aChosenFactories);
  Complemented.Complement(iFactory);
  return Complemented;
}


void Localisation::Construction()
{
  // TODO
}

void Localisation::NeighbourhoodSearch()
{
  // TODO
}

