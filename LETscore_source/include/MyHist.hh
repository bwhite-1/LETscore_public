
//
//  Created by everyday on 13/10/2020.
//

#ifndef MyHist_h
#define MyHist_h 1

#include "G4Types.hh"
#include "globals.hh"
#include <vector>

class MyHist
{

    
public:
    MyHist(G4int nbins, G4int numberofZ, G4int min, G4int max, G4int maxZ);
    ~MyHist();
    
    // all elements initialized to zero
    void Initialize();
    
    void Add(G4double val, G4double z);
    
    G4int GetBinValue(G4int bin, G4int z);

    G4int GetNBins();
    G4int GetNumberofZ();
    G4int GetMin();
    G4int GetMax();
    size_t Index(G4int bin, G4int z);
    
private:
    G4int nbins;
    G4int nZ;
    G4int minimum;
    G4int maximum;
    G4int maximumZ;
    std::vector<G4double> hist;

};
#endif
