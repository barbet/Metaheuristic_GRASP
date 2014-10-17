//==============================================================================
// 
// Class Testio: (Test Input/Output Header)
// - test instance reading
// - output writing
//
//==============================================================================

#ifndef TESTIO_H
#define TESTIO_H

#include "array2d.h"
#include <string>


class Testio
{
public:
  /** Default constructor */
  Testio();
  
  /**
   * Constructor from a file
   * @param iFile: file containing the instance of the proble
   */
  Testio(std::string iFile);
  
  /** Destructor */
  ~Testio();
  
  /** Return the number of clients */
  inline int NbClients();

  /** Return the number of factories */
  inline int NbFactories();
  
  /** Return the array of implantation costs of factories */
  inline double* ImplantationCost();
  
  /** Return the double array of distance between clients and factories */
  inline Array2d DistanceCF();
  
protected:
  int _NbClients;                 // Number of clients
  int _NbFactories;               // Number of factories
  double* _aImplantationCost;     // Array of implantation costs of factories
  Array2d _ClientFactoryDistance; // Array of distances between clients and factories
};


//==============================================================================
// Implementation of inline methods
//==============================================================================

inline int Testio::NbClients() {
  return _NbClients;
}

inline int Testio::NbFactories() {
  return _NbFactories;
}

inline double* Testio::ImplantationCost() {
  return _aImplantationCost;
}

inline Array2d Testio::DistanceCF() {
  return _ClientFactoryDistance;
}


#endif
