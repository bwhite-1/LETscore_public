
//
//  Created by everyday on 13/10/2020.
//

#ifndef MyLetCalc_h
#define MyLetCalc_h 1

#include "G4Types.hh"
#include "globals.hh"
#include "G4Event.hh"
#include "MyHit.hh"
#include "MyStruct.hh"
#include "MyHist.hh"

class MyLetCalc
{

public:
    MyLetCalc(MyParticleData* particleDataList, G4int MyListLenght, MyHist* sProtonHistPointer);
    ~MyLetCalc();
    
    void Calculate(hitCollection* aHitCollection);
    
private:
    MyParticleData* fParticleDataList;
    MyHist* fsProtonHistPointer;
    G4int fListLength;
    G4bool hitIsPrimary;
    G4ThreeVector r1, r2, r;
    G4double xvSize;
    G4double yvSize;
    G4double zvSize;
    G4int currentvX;
    G4int currentvY;
    G4int currentvZ;
    G4double eKinMean, LETi, nLETt, dLETt, nLETd, dLETd, Edep;
    
};
#endif
