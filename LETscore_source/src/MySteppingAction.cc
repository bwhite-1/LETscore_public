//
//  MyEventAction.cpp
//  
//
//  Created by everyday on 13/10/2020.
//

#include "MySteppingAction.hh"
#include "G4Step.hh"
#include "MyRunAction.hh"
#include "G4Track.hh"
#include "MyAnalysis.hh"
#include "G4VProcess.hh"
#include "math.h"

/*
 Stepping action:
 Every step, check if elastic secondary proton crosses the measurement plane at 80 mm
 If it does, record its nonrelativistic energy and lambda (distance from beam axis)
 Store residual range (calculated from energy) and lambda in Ntuple
 */


MySteppingAction::MySteppingAction(MyRunAction* RunAct)
:fRunAction(RunAct)
{}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step* step)
{
    // check particle is a secondary elastic proton
    if (step->GetTrack()->GetTrackID() != 1 &&
        step->GetTrack()->GetDefinition()->GetParticleName() == "proton" &&
        step->GetTrack()->GetCreatorProcess()->GetProcessName() == "hadElastic" ){
            
        auto preStepPoint = step->GetPreStepPoint();
        auto postStepPoint= step->GetPostStepPoint();
        
        // measurement plane depth in mm
        G4double plane = 80;
        
        if (preStepPoint->GetPosition().z() < plane*CLHEP::mm && postStepPoint->GetPosition().z() > plane*CLHEP::mm){
            
            // decompose pre and post position vector into components so lambda may be calculated
            G4double preX = preStepPoint->GetPosition().x();
            G4double postX = postStepPoint->GetPosition().x();
            G4double preY = preStepPoint->GetPosition().y();
            G4double postY = postStepPoint->GetPosition().y();
            G4double preZ = preStepPoint->GetPosition().z();
            G4double postZ = postStepPoint->GetPosition().z();
            
            G4double deltaX = postX - preX;
            G4double deltaY = postY - preY;
            G4double deltaZ = postZ - preZ;
            
            G4double lamda = (plane - preZ) / (deltaZ) * (sqrt(deltaX*deltaX + deltaY*deltaY)) + sqrt(preX*preX + preY*preY);
            G4double eK = 0.5 * (preStepPoint->GetKineticEnergy() + postStepPoint->GetKineticEnergy());
            
            // using Bortfeld relation
            G4double range = 0.022 * pow(eK,1.77);
            
            G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
            
            analysisManager->FillNtupleDColumn(1,0,lamda);
            analysisManager->FillNtupleDColumn(1,1,range);
            analysisManager->AddNtupleRow(1);

            
        }
    }
     
}
