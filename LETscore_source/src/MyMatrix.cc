/* https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
 
 (indices were backwards??)
 see above for explanation of how the matrix is defined
*/

#include "MyMatrix.hh"
#include "globals.hh"
#include "G4Types.hh"

MyMatrix::MyMatrix(G4int nX, G4int nY, G4int nZ)
{
    nVoxelX = nX;
    nVoxelY = nY;
    nVoxelZ = nZ;
    
    // create the matrix
    matrix.resize(5*nVoxelX*nVoxelY*nVoxelZ);
    
    if (matrix)
    {
        G4cout << "Successfully created 5"
        << " x " << nVoxelX
        << " x " << nVoxelY
        << " x " << nVoxelZ
        << " matrix" << G4endl;
    }
    else
    {
        G4cout << "Could not create the matrix" << G4endl;
    }
}


MyMatrix::~MyMatrix()
{
}


size_t MyMatrix::Index(G4int x, G4int y, G4int z, G4int t) const
{
    // function to map from
    //      4d_array[x][y][z][t]
    // to
    //      1d_array[]
    
    return x + (y*nVoxelX) + (z*nVoxelX*nVoxelY) + (t*nVoxelX*nVoxelY*nVoxelZ);
    
}
 

void MyMatrix::Initialize()
{
    //set all elements to zero
    
    for (int i=0; i<nVoxelX*nVoxelY*nVoxelZ*5; i++)
    {
        matrix[i] = 0.;
    }
}


void MyMatrix::Fill(G4int x,
                    G4int y,
                    G4int z,
                    G4double nLETt,
                    G4double dLETt,
                    G4double nLETd,
                    G4double dLETd,
                    G4double Edep)
{
    matrix[ Index(x,y,z,0) ] += nLETt;
    matrix[ Index(x,y,z,1) ] += dLETt;
    matrix[ Index(x,y,z,2) ] += nLETd;
    matrix[ Index(x,y,z,3) ] += dLETd;
    matrix[ Index(x,y,z,4) ] += Edep;
}


G4double MyMatrix::getnLETt(G4int x, G4int y, G4int z)
{ return matrix[Index(x,y,z,0)];}

G4double MyMatrix::getdLETt(G4int x, G4int y, G4int z)
{ return matrix[Index(x,y,z,1)];}

G4double MyMatrix::getnLETd(G4int x, G4int y, G4int z)
{ return matrix[Index(x,y,z,2)];}

G4double MyMatrix::getdLETd(G4int x, G4int y, G4int z)
{ return matrix[Index(x,y,z,3)];}

G4double MyMatrix::getEdep(G4int x, G4int y, G4int z)
{ return matrix[Index(x,y,z,4)];}


G4int MyMatrix::getNVoxelX()
{ return nVoxelX;}

G4int MyMatrix::getNVoxelY()
{ return nVoxelY;}

G4int MyMatrix::getNVoxelZ()
{ return nVoxelZ;}
