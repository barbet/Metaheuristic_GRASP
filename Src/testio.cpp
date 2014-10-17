#include "testio.h"

#include <fstream>
#include <iostream>

Testio::Testio():
  _aImplantationCost(0),
  _ClientFactoryDistance()
{
}
  
Testio::~Testio()
{
  if (_aImplantationCost)
    delete [] _aImplantationCost; _aImplantationCost=0;
}


Testio::Testio(std::string iFile):
  _aImplantationCost(0),
  _ClientFactoryDistance()
{
/* TODO
  std::ifstream fichier(iFile.c_str(), std::ios::in);
  if(fichier)
  {
    fichier >> _NbColumn >> _NbRow;
    int SizeOfTab = _NbRow*_NbColumn;
    if (SizeOfTab)
    {
      _aTab=new T[SizeOfTab];
      memset(_aTab, 0, SizeOfTab*sizeof(T));
      for(int i=0; i<SizeOfTab; i++)
      {
        T coef;
        fichier >> coef;
        _aTab[i]=coef;
      }
    }
    fichier.close();  // on ferme le fichier
  }
  else
    std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
*/
}
