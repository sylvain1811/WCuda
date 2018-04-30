#include "Device.h"
#include "Montecarlo.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

extern __global__ void montecarlo(curandState* tabDevGeneratorGM, int n, int* ptrResultGM);
extern __global__ void createGenerator(curandState* tabDevGeneratorGM, int deviceId);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

Montecarlo::Montecarlo(int n, const Grid& grid)
    {
    this->n = n;
    this->grid = grid;
    this->pi = 0.0;
    this->sizeTabGenerator = grid.threadCounts() * sizeof(curandState);

    // MM
    Device::malloc(&ptrResultGM, sizeof(n0));
    Device::memclear(ptrResultGM, sizeof(n0));
    Device::malloc(&tabDevGeneratorGM, sizeTabGenerator);

    // Init generator
    int deviceId = Device::getDeviceId();
createGenerator<<<grid.dg, grid.db>>>(tabDevGeneratorGM, deviceId);

}

Montecarlo::~Montecarlo()
{
Device::free(tabDevGeneratorGM);
Device::free(ptrResultGM);
}

void Montecarlo::run()
{
int nPerThread = n / grid.threadCounts();
montecarlo<<<grid.dg, grid.db, 1024*sizeof(int)>>>(tabDevGeneratorGM, nPerThread, ptrResultGM);

Device::memcpyDToH(&n0, ptrResultGM, sizeof(int));
pi = 2 * 2 * 2 * n0 / (float) (nPerThread * grid.threadCounts());
}

int Montecarlo::getN0()
{
return this->n0;
}

float Montecarlo::getPi()
{
return this->pi;
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

