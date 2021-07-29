//
//  MySensitiveDetector.cc
//  implementation fo the MySensitiveDetector class
//
//  Created by everyday on 13/10/2020.
//

#include "MySensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4HCtable.hh"
#include "G4Step.hh"
#include "G4UnitsTable.hh"
#include "MyAnalysis.hh"
#include "G4VProcess.hh"

MySensitiveDetector::MySensitiveDetector(G4String SDname)
 : G4VSensitiveDetector(SDname)
{
    //create a SD identified by a unique name
    collectionName.insert(SDname); // collectionName is a protected member of SD
}

MySensitiveDetector::~MySensitiveDetector(){}

// create a new hit collection at start of the event
void MySensitiveDetector::Initialize(G4HCofThisEvent* kHCEvent)
{
   // create a collection to store info about the hits
   gHitCollection = new hitCollection(SensitiveDetectorName, collectionName[0]);
 
   // To insert the collection, we need to get an unique ID for it
   if(mCollectionID<0) mCollectionID = GetCollectionID(0);// this is to get an ID for collectionName[0]
 
   // add the info into the collection
   kHCEvent->AddHitsCollection(mCollectionID, gHitCollection);
}

G4bool MySensitiveDetector::ProcessHits(G4Step* kStep, G4TouchableHistory*)
{
    // create a hit and populate it with information
    MyHit* hit = new MyHit(mCollectionID);
    hit->setName (kStep->GetTrack()->GetParticleDefinition()->GetParticleName());
    hit->setEdep (kStep->GetTotalEnergyDeposit());
    hit->setStepLength (kStep->GetStepLength());
    hit->setEKinPre(kStep->GetPreStepPoint()->GetKineticEnergy());
    hit->setEKinPost(kStep->GetPostStepPoint()->GetKineticEnergy());
    
    hit->setXPre(kStep->GetPreStepPoint()->GetPosition().getX());
    hit->setXPost(kStep->GetPostStepPoint()->GetPosition().getX());
    hit->setYPre(kStep->GetPreStepPoint()->GetPosition().getY());
    hit->setYPost(kStep->GetPostStepPoint()->GetPosition().getY());
    hit->setZPre(kStep->GetPreStepPoint()->GetPosition().getZ());
    hit->setZPost(kStep->GetPostStepPoint()->GetPosition().getZ());
    
    hit->setParticleDef(kStep->GetTrack()->GetDefinition());
    hit->setTrackID(kStep->GetTrack()->GetTrackID());
    
    if (hit->getTrackID() != 1) {
        hit->setCreatorProcessName(kStep->GetTrack()->GetCreatorProcess()->GetProcessName());
    }
    
    hit->setParentID(kStep->GetTrack()->GetParentID());
    // store this Hit in the collection, basically a push_back of the HC vector
    gHitCollection -> insert(hit);
    
    return true;
}

// Action taken at the end of the event, but before EventAction
void MySensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{

}
