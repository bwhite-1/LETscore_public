
//
//  Created by everyday on 13/10/2020.
//

#ifndef MyMatrix_h
#define MyMatrix_h 1

#include "G4Types.hh"
#include "globals.hh"
#include <vector>

class MyMatrix
{

    
public:
    MyMatrix(G4int nX, G4int nY, G4int nZ);
    ~MyMatrix();
    
    // all elements initialized to zero
    void Initialize();
    
    void Fill(G4int x,
              G4int y,
              G4int z,
              G4double nLETt,
              G4double dLETt,
              G4double nLETd,
              G4double dLETd,
              G4double Edep);
    
    G4double getnLETt(G4int x, G4int y, G4int z);
    G4double getdLETt(G4int x, G4int y, G4int z);
    G4double getnLETd(G4int x, G4int y, G4int z);
    G4double getdLETd(G4int x, G4int y, G4int z);
    G4double getEdep(G4int x, G4int y, G4int z);
    
    size_t Index(G4int x, G4int y, G4int z, G4int t) const;
    
    G4int getNVoxelX();
    G4int getNVoxelY();
    G4int getNVoxelZ();
    
    
    
private:
    G4int nVoxelX;
    G4int nVoxelY;
    G4int nVoxelZ;
    std::vector<G4double> matrix;

};
#endif
