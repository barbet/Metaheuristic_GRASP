//==============================================================================
// 
// Class Localisation: (chosen factories)
// - encoding of chosen factories
//
//==============================================================================

#ifndef LOCALISATION_H
#define LOCALISATION_H

#include "testio.h"
#include <assert.h>


class Localisation
{
public:
  /**
   * Constructor
   * @param iNbFactories: number of factories in the model
   */
  Localisation();
  
  /**
   * Constructor from an instance
   * @param iInstance       : Instance of the problem
   * @param iChosenFactories: Array of chosen factories. 
   *    If null, every factory is initialize with false.
   */
  Localisation(Testio &iInstance, bool* iChosenFactories = 0);

  /** Destructor */
  ~Localisation();
  
  /** Construction of the localisation */
  void Construction();
  
  /**
   * Create the same localisation except for the the factory iFactory
   * @param iFactory: factory to complement (add/remove)
   * return: the localisation created
   */
  Localisation CreateComplementedLocalisation(int iFactory);
  
  /**
   * Add a factory to the chosen ones if it not belong to its and remove it otherwise
   * @param iFactory: Number of factory to add/remove
   */
  inline void Complement(int iFactory);
  
  /**
   * Return the distance between a client and the closest chosen factory of the localisation
   * (Assume that each distance is positive.)
   * @param iClient: index of the client
   * @return: minimal distance to the factories if there are chosen factories
   *          -1 otherwise
   */
  double MinDistance(int iClient);
	
  /** Compute the cost of the localisation */
  double ComputeLocalisationCost();

  /**
   * Creates an intial factory with ony one factory for now (loop to be added)
   * @param iRCLLenght: Lenght of restricted candidate list
   */
  void Construction(int iRCLLength);

  /**
   * Search the best localisation in the neighbourhood of current localisation
   * and actualize the current localisation.
   */
  void NeighbourhoodSearch();
  
  /** Print the array of chosen factories */
  void PrintChosenFactories();
  
protected:
  Testio* _pInstance;             // Instance of the problem
  bool* _aChosenFactories;        // Array of chosen factories
  int _LastAddedFactory;          // Last factory added during the greedy construction
  double _ActualLocalisationCost; // Cost of the localisation
};


//==============================================================================
// Implementation of inline methods
//==============================================================================

inline void Localisation::Complement(int iFactory) {
  assert(0 <= iFactory && iFactory < _pInstance->NbFactories());
  _aChosenFactories[iFactory] = !_aChosenFactories[iFactory];
}

#endif
