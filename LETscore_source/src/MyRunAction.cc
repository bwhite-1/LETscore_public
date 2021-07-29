//
//  MyRunAction.cc
//  
//
//  Created by everyday on 13/10/2020.
//

#include "MyRunAction.hh"
#include "MyAnalysis.hh"
#include "MyMatrix.hh"
#include "MyStruct.hh"


#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <string>

/*
 RunAction defines how data is stored at end of run
 Ntuple 1 is filled from the 3D matrix (MyMatrix)
 Ntuple 2 was filled on a step-by-step basis in SteppingAction
 Ntuple 3 is filled from the histogram (MyHist)
 */

MyRunAction::MyRunAction()
 : G4UserRunAction()
{
    // create analysis manager
    // choice of analysis tool is done in MyAnalysis.hh
    
    auto analysisManager = G4AnalysisManager::Instance();
    G4cout << "Using " << analysisManager->GetType() << G4endl;
    
    analysisManager->SetVerboseLevel(1);

}

MyRunAction::~MyRunAction()
{
    delete G4AnalysisManager::Instance();
}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
    
    //initialise matrices
    for (int i=0; i<MyListLength-1; i++)
    {
        MyParticleList[i].matrix->Initialize();
    }
    
    // intialise hist
    sProtonHist.Initialize();
    
    //get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();
    
    // open an output file
    G4String fileName = "LETscore";
    analysisManager->OpenFile(fileName);
    
    
    // create ntuples - one for the LET data and one for the secondary production data
    analysisManager->CreateNtuple("MyNtuple","LET"); //0
    analysisManager->CreateNtuple("MyNtuple2","Secondary"); //1
    analysisManager->CreateNtuple("MyNtuple3","SecondarySpectrum"); //2
    
    analysisManager->CreateNtupleIColumn(0,"x"); // 0
    analysisManager->CreateNtupleIColumn(0,"y"); // 1
    analysisManager->CreateNtupleIColumn(0,"z"); // 2
    // now create columns for each particle in list
    // each particle takes 3 columns
    // ((expand window to see diagram))
    //  ____________________________________________________________________________
    // ||    Pos    |     Particle X     |     Particle Y     |         ...        ||
    // || x | y | z | nLET | dLET | Edep | nLET | dLET | Edep | nLET | dLET | Edep ||
    // ||---|---|---|------|------|------|------|------|------|------|------|------||
    // || 0 | 0 | 0 |  ..  |  ..  |  ..  |  ..  |  ..  |  ..  |  ..  |  ..  |  ..  ||
    // || 1 | 0 | 0 |  ..  |  ..  |  ..  |  ..  |  ..  |  ..  |  ..  |  ..  |  ..  ||
    
    for (int i=0; i<MyListLength; i++)
    {
        analysisManager->CreateNtupleDColumn(0,std::to_string(i+1)+MyParticleList[i].name+"_nLETd");
        analysisManager->CreateNtupleDColumn(0,std::to_string(i+1)+MyParticleList[i].name+"_dLETd");
        analysisManager->CreateNtupleDColumn(0,std::to_string(i+1)+MyParticleList[i].name+"_Edep");
    }
    
    analysisManager->CreateNtupleDColumn(1,"lamda");
    analysisManager->CreateNtupleDColumn(1,"Secondary Energy");
    

    analysisManager->CreateNtupleIColumn(2,"Depth");
    analysisManager->CreateNtupleIColumn(2,"Secondary Energy");
    analysisManager->CreateNtupleIColumn(2,"Frequency");
    
    analysisManager->FinishNtuple(0);
    analysisManager->FinishNtuple(1);
    analysisManager->FinishNtuple(2);
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    auto analysisManager = G4AnalysisManager::Instance();
    
    FillNtuple1(analysisManager);
    FillNtuple3(analysisManager);

    //write and close output file
    analysisManager->Write();
    analysisManager->CloseFile();
    
}

void MyRunAction::FillNtuple1(G4AnalysisManager* analysisManager)
{
    G4int nVoxelX = MyParticleList[0].matrix->getNVoxelX();
    G4int nVoxelY = MyParticleList[0].matrix->getNVoxelY();
    G4int nVoxelZ = MyParticleList[0].matrix->getNVoxelZ();

    G4int row = 0;
    
    // loop over voxels
    for (int k=0; k<nVoxelZ; k++)
    {
        for (int j=0; j<nVoxelY; j++)
        {
            for (int i=0; i<nVoxelX; i++){
                
                //fill the first columns with voxel number
                analysisManager->FillNtupleIColumn(0, 0, i);
                analysisManager->FillNtupleIColumn(0, 1, j);
                analysisManager->FillNtupleIColumn(0, 2, k);
                
                // if there is not LET/Edep in a voxel, don't bother adding it to the Ntuple
                
                G4double emptyVox = 0;
                
                for (int ii = 0; ii<MyListLength; ii++){
                    emptyVox += MyParticleList[ii].matrix->getnLETd(i,j,k);
                    emptyVox += MyParticleList[ii].matrix->getEdep(i,j,k);
                }
                
                if (emptyVox != 0)
                {
                    // loop over particle type in list
                    for (int n=0; n<MyListLength; n++)
                    {
                        G4double nLETd = MyParticleList[n].matrix->getnLETd(i,j,k);
                        
                        G4double dLETd = MyParticleList[n].matrix->getdLETd(i,j,k);
                        
                        G4double Edep = MyParticleList[n].matrix->getEdep(i,j,k);
                        
                        analysisManager->FillNtupleDColumn(0, 3+3*n,   nLETd);
                        analysisManager->FillNtupleDColumn(0, 3+3*n+1, dLETd);
                        analysisManager->FillNtupleDColumn(0, 3+3*n+2, Edep);
                    }
                    analysisManager->AddNtupleRow(0);
                    row++;
                }
            }
        }
    }
    
}

void MyRunAction::FillNtuple3(G4AnalysisManager* analysisManager)
{
    G4int min = sProtonHistPointer->GetMin();
    G4int max = sProtonHistPointer->GetMax();
    
    for (G4int j=0; j<sProtonHistPointer->GetNumberofZ(); j++)
    {
        for (int i=0; i<sProtonHistPointer->GetNBins(); i++)
        {
            
            analysisManager->FillNtupleIColumn(2,0, j);
            
            analysisManager->FillNtupleIColumn(2, 1, i*(max - min)/sProtonHistPointer->GetNBins());
            
            analysisManager->FillNtupleIColumn(2, 2, sProtonHistPointer->GetBinValue(i,j));
            
            analysisManager->AddNtupleRow(2);
        }
    }
}
