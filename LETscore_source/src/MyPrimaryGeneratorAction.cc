//
//  MyPrimaryGeneratorAction.cpp
//  
//
//  Created by everyday on 13/10/2020.
//

#include "MyPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction(
                                                           const G4String& particleName,
                                                           G4double energy,
                                                           G4ThreeVector position,
                                                           G4ThreeVector momentumDirection)
    : G4VUserPrimaryGeneratorAction(),
      fGeneralParticleSource(0)
{
    fGeneralParticleSource = new G4GeneralParticleSource();
}

MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction()
{
    delete fGeneralParticleSource;
}

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    //this is called at the beginning of every event
    fGeneralParticleSource->GeneratePrimaryVertex(anEvent);
}
