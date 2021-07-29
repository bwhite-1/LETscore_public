//
//  first_project.cpp
//  
//
//  Created by everyday on 13/10/2020.
//
#include "MyDetectorConstruction.hh"
#include "MyActionInitialization.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4ScoringManager.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "QGSP_BIC.hh"





int main(int argc,char** argv)
{
    // Detect interactive mode (if no arguments) and define UI session
    //
    G4UIExecutive* ui = 0;
    if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
    }

    // Construct the default run manager
    //
    #ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
    G4cout<<"multithreaded"<<G4endl;
    #else
    G4RunManager* runManager = new G4RunManager;
    G4cout<<"single threaded"<<G4endl;
    #endif

    // Construct the scoring manager for primitive scoring
    G4ScoringManager* scoringManager = G4ScoringManager::GetScoringManager();

    //Set mandatory intialization classes
    //
    // Detector construction
    runManager->SetUserInitialization(new MyDetectorConstruction);

    // Physics List
    G4VModularPhysicsList* physicsList = new QGSP_BIC;
    physicsList->SetCutValue(0.1, "e-");

    physicsList->SetVerboseLevel(1);
    runManager->SetUserInitialization(physicsList);

    // user action initialization
    runManager->SetUserInitialization(new MyActionInitialization);



    // initialize G4 kernel
    //runManager->Initialize();

    // get the pointer to the UI manager and set verbosities
    G4UImanager* UI = G4UImanager::GetUIpointer();
    UI->ApplyCommand("/run/verbose 0");
    UI->ApplyCommand("/event/verbose 0");
    UI->ApplyCommand("/tracking/verbose 0");

    // start a run
    int numberOfEvent = 3;
    runManager->BeamOn(numberOfEvent);



    // Initialize visualization
    G4VisManager* visManager = new G4VisExecutive;
    // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
    // G4VisManager* visManager = new G4VisExecutive("Quiet");
    visManager->Initialize();

    // Get the pointer to the User Interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if ( ! ui ) {
      // batch mode
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UImanager->ApplyCommand(command+fileName);
    }
    else {
      // interactive mode
      UImanager->ApplyCommand("/control/execute init_vis.mac");
      ui->SessionStart();
      delete ui;
    }

    

    // Job termination
    delete visManager;
    delete runManager;

    return 0;
}
