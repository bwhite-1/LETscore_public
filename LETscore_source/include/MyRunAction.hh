

#ifndef MyRunAction_h
#define MyRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "MyMatrix.hh"
#include "MyStruct.hh"
#include "MyHist.hh"


class G4Run;

class MyRunAction : public G4UserRunAction
{
  public:
    MyRunAction();
    virtual ~MyRunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
    
    void FillNtuple1(G4AnalysisManager* analysisManager);
    void FillNtuple3(G4AnalysisManager* analysisManager);
    
    MyMatrix pProtonMatrix = MyMatrix(50,50,170);
    MyMatrix sProtonMatrix = MyMatrix(50,50,170);
    MyMatrix electronMatrix = MyMatrix(50,50,170);
    MyMatrix alphaMatrix = MyMatrix(50,50,170);
    MyMatrix deuteronMatrix = MyMatrix(50,50,170);
    
    // this is an array of MyParticleData structs
    // to score another particle:
    // declare a matrix like above,
    // add it to the struct below,
    // and change MyListLength accordingly
    
    MyMatrix *pProtonPointer = &pProtonMatrix;
    MyMatrix *sProtonPointer = &sProtonMatrix;
    MyMatrix *electronPointer = &electronMatrix;
    MyMatrix *alphaPointer = &alphaMatrix;
    MyMatrix *deuteronPointer = &deuteronMatrix;
    
    MyParticleData MyParticleList[5] =
    {
    {"proton", true, pProtonPointer},
    {"proton", false, sProtonPointer}
    {"e-", false, electronPointer},
    {"alpha", false, alphaPointer},
    {"deuteron", false, deuteronPointer}
    };

    G4int MyListLength = 5;
    
    MyHist sProtonHist = MyHist(160, 170, 0, 160, 170);
    MyHist *sProtonHistPointer = &sProtonHist;
    
};

#endif

