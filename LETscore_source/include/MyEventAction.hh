//
//  MyPrimaryGeneratorAction.hh
//  
//
//  Created by everyday on 13/10/2020.
//

#ifndef MyEventAction_h
#define MyEvent_h 1

#include "G4UserEventAction.hh"
#include "MyHit.hh"
#include "MyMatrix.hh"
#include "MyRunAction.hh"


class MyRunAction;

class MyEventAction : public G4UserEventAction
{
public:
    MyEventAction(MyRunAction* runAction);
    virtual ~MyEventAction();
    
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void   EndOfEventAction(const G4Event* event);
    
private:
    hitCollection* GetHitsCollection(G4int hcID,
                                     const G4Event* event) const;
    
    MyRunAction* fRunAction;
    G4int fhcID;

    
};

#endif
