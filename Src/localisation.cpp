#include "localisation.h"

#include <string.h>
#include <algorithm>
#include <Cstdlib>

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


double Localisation::ComputeLocalisationCost()
{
	double Cost=0;
	int i;
	for (i = 0;i<_pInstance->NbClients();i++)
	{
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


void Localisation::Construction(Testio &iInstance, int RCLLength)
{
  Localisation MyLoc(iInstance);
  int i;
  int j;
  int k;
  double *Cost=new double[_pInstance->NbClients()]; 
  array2d Candidates(RCLLength,2); //contains the better factories and the corresponding cost
  for (i=0; i<_pInstance->NbClients();i++)
  {
	Cost(i)=(MyLoc.Complement(i)).ComputeLocalisationCost(); //cost of the solution with the ith factories open
	MyLoc.Complement(i); // reset MyLoc
  }
 for(i=0; i<_pInstance->NbClients();i++) // Compute the table of candidates (the rcllegth better factories and their cost)
 {
	 j=0;
	 while (j<RCLLength && Cost(i)<Candidates(2,j) ) j++;
	 if j=RCLLength continue;
	 for (k=j+1;k<RCLLength;k++)
	 {
		 Candidates(1,k)=Candidates(1,k-1);
		 Candidates(2,k)=Candidates(2,k-1);
	 }
	 Candidates(1,j)=i;
	 Candidates(2,j)=Cost(i);
}
j=rand()%RCLLength; // draw a factory amongst the rcllength best
MyLoc.Complement(j);

}

void Localisation::NeighbourhoodSearch()
{
  // TODO
}


