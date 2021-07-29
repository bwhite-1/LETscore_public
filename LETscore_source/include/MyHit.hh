//
//  MyDetectorConstruction.hh
//  definition of the MyDetectorConstruction class
//
//  Created by everyday on 13/10/2020.
//

#ifndef MyHit_h
#define MyHit_h 1


#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"
#include "G4Track.hh"

class MyHit : public G4VHit
{
public:
    //hit must be given ID
    MyHit(const G4int kHitIDnumber);
    ~MyHit();
    void Print();
    void Draw();
    
public:
    // set methods
    void setName(const G4String STR){mName = STR;};
    void setEdep(const G4double E){mEdep = E;};
    void setStepLength(const G4double DX){mStepLength = DX;};
    void setEKinPre(const G4double EKPRE){mEKinPre = EKPRE;};
    void setEKinPost(const G4double EKPOST){mEKinPost = EKPOST;};
    void setCreatorProcessName(G4String CPNAME) {mCPname = CPNAME;};
    void setParentID(G4int PID) {mPID = PID;};
    
    void setXPre( G4double XPRE){mXPre = XPRE;};
    void setXPost( G4double XPOST){mXPost = XPOST;};
    void setYPre( G4double YPRE){mYPre = YPRE;};
    void setYPost( G4double YPOST){mYPost = YPOST;};
    void setZPre( G4double ZPRE){mZPre = ZPRE;};
    void setZPost( G4double ZPOST){mZPost = ZPOST;};
    
    
    
    void setParticleDef( G4ParticleDefinition* DEF){mParticleDef = DEF;};
    void setTrackID(G4int ID) { mID = ID;};
    
    // get methods
    G4String getName()        const {return mName;};
    G4double getEdep()        const {return mEdep;};
    G4double getStepLength()  const {return mStepLength;};
    G4double getEKinPre()     const {return mEKinPre;};
    G4double getEKinPost()    const {return mEKinPost;};
    G4String getCreatorProcessName() const {return mCPname;};
    
    G4double getXPre() const {return mXPre;};
    G4double getXPost()const {return mXPost;};
    G4double getYPre() const {return mYPre;};
    G4double getYPost()const {return mYPost;};
    G4double getZPre() const {return mZPre;};
    G4double getZPost()const {return mZPost;};
    
    G4ParticleDefinition *getParticleDef() const {return mParticleDef;};
    G4int getTrackID()        const { return mID;};
    G4int getParentID() const { return mPID;};

    
private:
    G4int gHitID;
    G4String mName = "unknown";
    G4double mEdep = -1.0;
    G4double mStepLength = -1.0;
    G4double mEKinPre = -1.0;
    G4double mEKinPost = -1.0;
    G4String mCPname = "unknown";
    
    G4double mXPre = -1.0;
    G4double mXPost= -1.0;
    G4double mYPre = -1.0;
    G4double mYPost= -1.0;
    G4double mZPre = -1.0;
    G4double mZPost= -1.0;
    
    G4ParticleDefinition* mParticleDef;
    G4int mID = -1;
    G4int mPID = -1;
};

//define the hit collection type we used in the SD header
typedef G4THitsCollection<MyHit> hitCollection;

#endif
