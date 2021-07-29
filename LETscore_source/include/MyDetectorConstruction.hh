//
//  MyDetectorConstruction.hh
//  definition of the MyDetectorConstruction class
//
//  Created by everyday on 13/10/2020.
//

#ifndef MyDetectorConstruction_h
#define MyDetectorConstruction_h 1


#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

// Detector construction class to define materials and geometry

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        MyDetectorConstruction();
        virtual ~MyDetectorConstruction();
        
        virtual G4VPhysicalVolume* Construct();
        virtual void ConstructSDandField();
    
        G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }
    
    protected:
        G4LogicalVolume* fScoringVolume;
};


#endif
