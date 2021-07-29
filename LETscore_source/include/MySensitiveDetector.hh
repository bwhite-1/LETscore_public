//
//  MyDetectorConstruction.hh
//  definition of the MyDetectorConstruction class
//
//  Created by everyday on 13/10/2020.
//

#ifndef MySensitiveDetector_h
#define MySensitiveDetector_h 1


#include "G4VSensitiveDetector.hh"
#include "MyHit.hh"

class MySensitiveDetector : public G4VSensitiveDetector
{
public:
    // constructor takes the unique name SD_1
    MySensitiveDetector(G4String SDname);
    ~MySensitiveDetector();
public:
    // runs every time the SD is active
    G4bool ProcessHits(G4Step* kStep, G4TouchableHistory*);
    
    // optional methods
    void Initialize(G4HCofThisEvent* kHCEvent);
    void EndOfEvent(G4HCofThisEvent* kHCEvent);
    
private:
    // pointer to a collection of hits
    hitCollection* gHitCollection;
    G4int mCollectionID;
    
};

#endif
