//==============================================================================
// 
// Class Testio: (Test Input/Output Header)
// - test instance reading
// - output writing
//
//==============================================================================

#ifndef TESTIO_H
#define TESTIO_H

#include "array2d.h" // Declaration of 2D-array
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

private:
  double* _aImplantationCost;     // Array of implantation costs of factories
  Array2d _ClientFactoryDistance; // Array of distances between clients and factories
};

#endif
