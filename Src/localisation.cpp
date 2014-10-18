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
  int nbClients = _pInstance->NbClients();
  double m = -1; // Minimum
  int j=0;
  while (j < nbClients && !_aChosenFactories[j]) {
    j++;
  }
  if (j < nbClients) {
    m = _pInstance->DistanceCF()(iClient,j);
    int i;
    for(i = j; i < nbClients; i++) {
      if (_aChosenFactories[i])
        m = std::min( _pInstance->DistanceCF()(iClient,i) , m ); 
    }
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

