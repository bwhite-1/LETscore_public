/* https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
 
 (indices were backwards??)
 see above for explanation of how the matrix is defined
*/

#include "MyHist.hh"
#include "globals.hh"
#include "G4Types.hh"

MyHist::MyHist(G4int bins, G4int numberofZ, G4int min, G4int max, G4int maxZ)
{
    nbins = bins;
    minimum = min;
    maximum = max;
    nZ = numberofZ;
    maximumZ = maxZ;
    
    // create the matrix
    hist.resize(nbins*nZ);

}


MyHist::~MyHist()
{
    //delete[] matrix;
    //matrix = nullptr;
}
 
void MyHist::Initialize()
{
    for (int i=0; i<nbins*nZ; i++)
    {
        hist[i] = 0.;
    }
}

size_t MyHist::Index(G4int bin, G4int z)
{
    return bin + (z * nbins);
}

void MyHist::Add(G4double val, G4double z)
{
    
    G4int bin = floor( val*nbins/(maximum-minimum) );
    G4int depth = floor( z );
    hist[ Index(bin, depth) ] += 1;
    //G4cout<< "value = " << val << ", bin = " << bin << G4endl;
}

G4int MyHist::GetBinValue(G4int bin, G4int z)
{
    return hist[Index(bin,z)];
}

G4int MyHist::GetNBins()
{
    return nbins;
}

G4int MyHist::GetNumberofZ()
{
    return nZ;
}

G4int MyHist::GetMin()
{
    return minimum;
}

G4int MyHist::GetMax()
{
    return maximum;
}

