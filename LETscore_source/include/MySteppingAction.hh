

#ifndef MySteppingAction_h
#define MySteppingAction_h 1

#include "G4UserSteppingAction.hh"

class MyRunAction;

class MySteppingAction : public G4UserSteppingAction
{

public:
    MySteppingAction(MyRunAction* RunAct);
    virtual ~MySteppingAction();
    
    virtual void UserSteppingAction(const G4Step*);
    
private:
    MyRunAction* fRunAction;
    
};
#endif

