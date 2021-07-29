//
//  MyPrimaryGeneratorAction.hh
//  
//
//  Created by everyday on 13/10/2020.
//

#ifndef MyActionInitialization_h
#define MyActionInitialization_h 1

#include "G4VUserActionInitialization.hh"


class MyActionInitialization : public G4VUserActionInitialization
{
public:
    MyActionInitialization();
    virtual ~MyActionInitialization();
    
    virtual void Build() const;
};

#endif
