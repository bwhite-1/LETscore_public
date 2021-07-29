//
//  MyPrimaryGeneratorAction.hh
//  
//
//  Created by everyday on 13/10/2020.
//

#ifndef MyPrimaryGeneratorAction_h
#define MyPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "G4GeneralParticleSource.hh"
#include "globals.hh"

class G4GeneralParticleSource;
class G4Event;

class MyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
    public:
        MyPrimaryGeneratorAction(
            const G4String& particleName = "proton",
            G4double energy = 150.*CLHEP::MeV,
            G4ThreeVector position = G4ThreeVector(0,0,0*CLHEP::m),
            G4ThreeVector momentumDirection = G4ThreeVector(0,0,1));
        ~MyPrimaryGeneratorAction();
    
        //methods
        virtual void GeneratePrimaries(G4Event*);
        const G4GeneralParticleSource* GetGeneralParticleSource() const { return fGeneralParticleSource; }
    private:
        G4GeneralParticleSource* fGeneralParticleSource;
    
    
};

#endif
