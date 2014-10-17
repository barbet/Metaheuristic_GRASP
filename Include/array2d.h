//==============================================================================
// 
// Class Array2d: (2-Dimensional Array)
// - creation of 2D-array
//
//==============================================================================

#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <assert.h> // defines the C preprocessor macro assert()

class Array2d
{
public:
  /** Default constructor */
  Array2d();
  
  /**
   * Constructor by specifying numbers of rows and columns
   * @param iNbRow   : number of array's rows
   * @param iNbColumn: number of array's column
   */
  Array2d(int iNbRow, int iNbColumn);
  
  /** Destructor */
  ~Array2d();
  
  /** Return the number of rows of the array */
  inline int GetNbRow();

  /** Return the number of columns of the array */
  inline int GetNbColumn();

  /**
   * Reading and writing access to coefficients
   * @param i : row's index
   * @param j : column's index
   */
  inline double& operator()(int i, int j);
  inline const double& operator()(int i, int j)const;
  
private:
  int _NbRow;     // Number of rows
  int _NbColumn;  // Number of columns
  double* _aTab;  // Array of double
};


//==============================================================================
// Implementation of inline methods
//==============================================================================

inline int Array2d::GetNbRow() {
  return _NbRow;
}

inline int Array2d::GetNbColumn() {
  return _NbColumn;
}

inline double& Array2d::operator()(int i, int j)
{
  assert(0<=i && i<_NbRow && 0<=j && j<_NbColumn);
  return _aTab[_NbColumn*i+j];
}

inline const double& Array2d::operator()(int i, int j)const
{
  assert(0<=i && i<_NbRow && 0<=j && j<_NbColumn);
  return _aTab[_NbColumn*i+j];
}


#endif


