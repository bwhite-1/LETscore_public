//
//  MyEventAction.cpp
//  
//
//  Created by everyday on 13/10/2020.
//

#include "MyEventAction.hh"
#include "MySensitiveDetector.hh"
#include "MyHit.hh"
#include "MyAnalysis.hh"
#include "MyRunAction.hh"
#include "MyMatrix.hh"
#include "MyLetCalc.hh"


#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"
#include "G4NistManager.hh"

/*
 EventAction defines what happens before and after an event
 (simulation of the entire trajectory of a particle and all its children)
 Uses the hit collection to calculate the LET at all points in 3d space
 */

MyEventAction::MyEventAction(MyRunAction* runAction)
 : G4UserEventAction(),
   fRunAction(runAction),
   fhcID(-1)
{}

MyEventAction::~MyEventAction()
{}

hitCollection* MyEventAction::GetHitsCollection(G4int hcID, const G4Event* event) const
{
    auto hitsCollection = static_cast<hitCollection*>(event->GetHCofThisEvent()->GetHC(hcID));
    
    if (!hitsCollection) {
        G4ExceptionDescription msg;
        msg << "Cannot access hitsCollection ID " << hcID;
        G4Exception("MyEventAction::GetHitsCollection()", "MyCode0003", FatalException, msg);
    }
    return hitsCollection;
}

void MyEventAction::BeginOfEventAction(const G4Event*)
{}

void MyEventAction::EndOfEventAction(const G4Event* event)
{
    // get collection id, same as sdetector name
    if ( fhcID == -1 )
    {
        fhcID = G4SDManager::GetSDMpointer()->GetCollectionID("SD_1");
    }
    //get hit collection IDs
    auto aHitCollection = GetHitsCollection(fhcID, event);

    // cout event number every 10000 events to keep track of simulation progress
    if (event->GetEventID() % 10000 ==0)
    {
        G4cout<<event->GetEventID()<<G4endl;
    }
    
    MyLetCalc LetCalc(fRunAction->MyParticleList, fRunAction->MyListLength, fRunAction->sProtonHistPointer);
    LetCalc.Calculate(aHitCollection);
    
    FillHistogram(aHitCollection);
}

void MyEventAction::FillHistogram(G4HitsCollection aHitCollection)
{
    G4int last_vox = -1;
    for (size_t i=0; i<aHitCollection->entries(); i++)
    {
        auto hit = (*aHitCollection)[i];
    
         if (hit->getTrackID()!=1)
         {
             if (hit->getParticleDef()->GetParticleName() == "proton" &&
                 hit->getCreatorProcessName() == "hadElastic" &&
                 hit->getParentID() == 1)
             {
                 G4double zPre = hit->getZPre();
                 G4double zPost = hit->getZPost();
                 
                 if (ceil(zPre) == ceil(zPost))
                 {
                     if (last_vox != ceil(zPre))
                     {
                     
                         G4double eK = 0.5 * (hit->getEKinPre() + hit->getEKinPost());
                         G4double range = 0.022 * pow(eK, 1.77);
                         fRunAction->sProtonHistPointer->Add( range, ceil(zPre) );
                         
                         last_vox = ceil(zPre);
                     }

                 } else {

                     for (G4int j = ceil(zPre); j < ceil(zPost); j++)
                     {
                         G4double eK = 0.5 * (hit->getEKinPre() + hit->getEKinPost());
                         
                         G4double range = 0.022 * pow(eK, 1.77);
                         
                         fRunAction->sProtonHistPointer->Add( range, j );
                     }
                 }
                 
             }
         }
    }
}
