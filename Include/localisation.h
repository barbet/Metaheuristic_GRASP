//==============================================================================
// 
// Class Localisation: (chosen factories)
// - encoding of chosen factories
//
//==============================================================================

#ifndef LOCALISATION_H
#define LOCALISATION_H


class Localisation
{
public:
  /**
   * Constructor
   * @param iNbFactories: number of factories in the model
   */
  Localisation(int iNbFactories = 0);
  
  /** Destructor */
  ~Localisation();
  
  /** Construction of the localisation */
  void Construction();
  
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
