//
//  MyActionInitialization.cc
//  
//
//  Created by everyday on 13/10/2020.
//

#include "MyActionInitialization.hh"
#include "MyPrimaryGeneratorAction.hh"
#include "MyEventAction.hh"
#include "MyRunAction.hh"
#include "MySteppingAction.hh"

MyActionInitialization::MyActionInitialization()
 : G4VUserActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::Build() const
{
    MyRunAction* runAction = new MyRunAction();
    
    SetUserAction(runAction);
    SetUserAction(new MyPrimaryGeneratorAction);
    SetUserAction(new MyEventAction(runAction));
    SetUserAction(new MySteppingAction(runAction));

}
