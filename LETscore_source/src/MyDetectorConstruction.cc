//
//  MyDetectorConstruction.cc
//  implementation fo the MyDetectorConstruction class
//
//  Created by everyday on 13/10/2020.
//

#include "MyDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4SDManager.hh"
#include "MySensitiveDetector.hh"

MyDetectorConstruction::MyDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{

    ConstructWorldVolume(0.03, 0.03, 0.180);
    ConstructPhantomVolume(0.025, 0.025, 0.085);
    
    fScoringVolume = shapeLog;
    return worldPhys;
}

// construct the SD
void MyDetectorConstruction::ConstructSDandField()
{
    // get SD manager
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    
    // create a new sensitive detector called SD_1
    MySensitiveDetector* sensitiveDet = new MySensitiveDetector("SD_1");
    
    // register SD with the manager
    sdManager -> AddNewDetector(sensitiveDet);
    
    // set logical volume to be a SD
    SetSensitiveDetector("Shape 1", sensitiveDet);
}

void MyDetectorConstruction::ConstructWorldVolume(G4double half_x, G4double half_y, G4double half_z)
{
    // get the Nist material manager
    G4NistManager* nist = G4NistManager::Instance();
    
    // create a box named World
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
    G4Box* worldBox = new G4Box("World", half_x*m, half_y*m, half_z*m);
    
    // now create logical volume from solid
    G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, world_mat, "World");
    
    // now create a physical volume - this a placed instance of the logical volume
    // note that the world volume is placed by giving it a null mother pointer
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(0,                 // no rotation
                                                     G4ThreeVector(0,0,0),   // at (0,0,0)
                                                     worldLog,          // its logical volume
                                                     "World",           // its name
                                                     0,                 // its mother volume
                                                     false,             // no boolean operation
                                                     0);                 // copy number
}

void MyDetectorConstruction::ConstructPhantomVolume(G4double half_x, G4double half_y, G4double half_z)
{
    // get the Nist material manager
    G4NistManager* nist = G4NistManager::Instance();
    
    // shape1
    G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_WATER");
    
    G4Box* shapeBox = new G4Box("Shape 1", half_x*m, half_y*m, half_z*m);
    G4LogicalVolume* shapeLog = new G4LogicalVolume(shapeBox, shape1_mat, "Shape 1");
    
    new G4PVPlacement(0,
                      G4ThreeVector(0,0,half_z*m),
                      shapeLog,
                      "Shape 1",
                      worldLog,
                      false,
                      0);
    
    fScoringVolume = shapeLog;
}
