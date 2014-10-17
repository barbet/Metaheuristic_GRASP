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

double Localisation::MinDistance(int Client)
{
	double m;
	// Initialize the minimum to a majorant of the client's line
	for( int j = 0; j< Testio.getNbClients(); j++)
	{
		m= m + _aTab(j);
	}
	//find the distance minimum among activated facilities
	for( int j = 0; j< Testio.getNbClients(); j++)
	{
		if (_aTab(j)) {
			m= min(m,testio.getClientFactoryDistance(Client,j));
		}
	}
	return m;
}


Localisation Localisation::operator Complementation(Localisation Ref,int RowToComplete)
{
	//create a localisation identique to the reference
	Localisation Complemented(Ref.get_NbFactories());
	for (int j=0;j<NbFactoriesComplemented;j++){
		Complemented.set(j)=Reference.get(j);
	}
	//complement the RowToComplete th row
	Complemented.set(RowToComplete)=1-Ref.get(RowToComplete);
}


void Localisation::Construction()
{
  // TODO
}

void Localisation::NeighbourhoodSearch()
{
  // TODO
}

