#include "MyLetCalc.hh"
#include "MyMatrix.hh"
#include "MyEventAction.hh"
#include "MyStruct.hh"
 
#include "globals.hh"
#include "G4Types.hh"
#include "G4EmCalculator.hh"
#include "G4NistManager.hh"
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "Randomize.hh"

MyLetCalc::MyLetCalc(MyParticleData* particleDataList, G4int MyListLength, MyHist* sProtonHistPointer)
 : fParticleDataList(particleDataList),
   fListLength(MyListLength),
   fsProtonHistPointer(sProtonHistPointer)
{}

MyLetCalc::~MyLetCalc()
{}

void MyLetCalc::Calculate(hitCollection* aHitCollection)
{
    G4EmCalculator emCal;
    G4NistManager* nist = G4NistManager::Instance();
    
    // first calculate the total path length
    G4double totalPathLength = 0;
    G4double pathLength = 0;
    
    G4bool isCounted = false;
    
    for (size_t i=0; i<aHitCollection->entries(); i++)
    {
        auto hit = (*aHitCollection)[i];
        
        if (hit->getTrackID()!=1 &&
            hit->getCreatorProcessName() == "hadElastic" &&
            hit->getParticleDef()->GetParticleName() == "proton")
        {
            totalPathLength += hit->getStepLength();
            /*
            if (hit->getEKinPost() == 0){
                break;
            }*/
             
        }
    }
    
    //loop over hit collection
    for (size_t i=0; i<aHitCollection->entries(); i++)
    {
        auto hit = (*aHitCollection)[i];
        
        //check if particle is primary
        if (hit->getTrackID() == 1){
            hitIsPrimary = true;
        }
        else {
            hitIsPrimary = false;
        }
        
        
        //check which matrix to use
        int particleIdx = -1;

        for (int j=0; j<fListLength; j++)
        {
            if (hit->getParticleDef()->GetParticleName() == fParticleDataList[j].name
                && hitIsPrimary == fParticleDataList[j].isPrimary){
                particleIdx = j;
            }
        }
        
        if (particleIdx != -1 && hit->getCreatorProcessName() == "hadElastic")
        {
            //calculate which voxel particle is in
            //pick a random point along the step
            // c.f. condensed history
            
            // r = r1 + (G4UniformRand() * (r2-r1));
            // break into components
            
            G4double x1 = hit->getXPre();
            G4double x2 = hit->getXPost();
            G4double y1 = hit->getYPre();
            G4double y2 = hit->getYPost();
            G4double z1 = hit->getZPre();
            G4double z2 = hit->getZPost();
            
            G4double rand = G4UniformRand();
            
            G4double x = x1 + rand * (x2-x1);
            G4double y = y1 + rand * (y2-y1);
            G4double z = z1 + rand * (z2-z1);
            
            // recall that the detector size is given in hx hy hz!!!
            xvSize = 50 / fParticleDataList[particleIdx].matrix->getNVoxelX();
            yvSize = 50 / fParticleDataList[particleIdx].matrix->getNVoxelY();
            zvSize = 170 / fParticleDataList[particleIdx].matrix->getNVoxelZ();
    
            currentvX = floor(x/xvSize)+25;
            currentvY = floor(y/yvSize)+25;
            currentvZ = floor(z/zvSize);
            
            eKinMean = 0.5 * ( hit->getEKinPre() + hit->getEKinPost() );
            
            LETi = emCal.ComputeElectronicDEDX(eKinMean,
                                               hit->getParticleDef(),
                                               nist->FindOrBuildMaterial("G4_WATER"));
            
            nLETt = hit->getStepLength() * LETi;
            dLETt = hit->getStepLength();
            
            nLETd = hit->getEdep() * LETi;
            dLETd = hit->getEdep();
            
            Edep = hit->getEdep();
            
            //fill matrix
            // -> c.f. Granville and Sawakuchi method 2
            fParticleDataList[particleIdx].matrix->Fill(currentvX,
                                                       currentvY,
                                                       currentvZ,
                                                       nLETt,
                                                       dLETt,
                                                       nLETd,
                                                       dLETd,
                                                       Edep);
            
        }
        
        // now score local energy spectrum
        // for secondary protons
        // and score into histogram
        // -> c.f. Granville and Sawakuchi method 3
        if (hit->getTrackID()!=1 &&
            hit->getCreatorProcessName() == "hadElastic" &&
            hit->getParticleDef()->GetParticleName() == "proton")
        {
            
            G4double xPre = hit->getXPre();
            G4double xPost = hit->getXPost();
            G4double yPre = hit->getYPre();
            G4double yPost = hit->getYPost();
            G4double zPre = hit->getZPre();
            G4double zPost = hit->getZPost();
            
            pathLength += hit->getStepLength();
            
            if (zPost > zPre)
            {
                if (ceil(zPre) == ceil(zPost) && !isCounted){
                    G4double eK = 0.5* (hit->getEKinPre() + hit->getEKinPost());
                    fsProtonHistPointer->Add( eK, floor(zPre) );
                    break;
                } else {
                    for (G4double j = ceil(zPre); j < ceil(zPost); j++)
                    {
                        G4double eK = 0.5 * (hit->getEKinPre() + hit->getEKinPost());
                        
                        fsProtonHistPointer->Add( eK, j );
                        
                        isCounted = true;
                    }
                }
            }
        }
    }
}
