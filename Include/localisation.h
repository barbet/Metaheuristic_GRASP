//==============================================================================
// 
// Class Localisation: (chosen factories)
// - encoding of chosen factories
//
//==============================================================================

#ifndef LOCALISATION_H
#define LOCALISATION_H
#include <algorithm>


class Localisation
{
public:
  /**
   * Constructor
   * @param iNbFactories: number of factories in the model
   */
  Localisation(int iNbFactories = 0);
  
   /** Creation of the same localisation, the ith boolean being complemented */
  Localisation operator Complementation(Localisation Ref,int RowToComplete)


  /** Destructor */
  ~Localisation();
  
  /**
   * Resize the array of factories. (/!\ DELETE THE WHOLE DATA IN THE ARRAY /!\)
   * @param iNbFactories: new number of factories
   */
  void Resize(int iNbFactories);
  
  /** Construction of the localisation */
  void Construction();
  
  /** Gives the distance between a client and the closest factory of the localisation */
  double MinDistance(int Client);





  /**
   * Search the best localisation in the neighbourhood of current localisation
   * and actualize the current localisation.
   */
  void NeighbourhoodSearch();
  
private:
  int _NbFactories; // Number of factories
  bool* _aTab;      // Array of chosen factories
};

#endif
