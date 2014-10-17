#include "testio.h"

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

