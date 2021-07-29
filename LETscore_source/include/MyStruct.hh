
//
//  Created by everyday on 13/10/2020.
//

#ifndef MyStruct_h
#define MyStruct_h 1

#include "G4Types.hh"
#include "globals.hh"
#include "MyMatrix.hh"

struct MyParticleData {
    G4String name;
    G4bool isPrimary;
    MyMatrix* matrix;
};


#endif
