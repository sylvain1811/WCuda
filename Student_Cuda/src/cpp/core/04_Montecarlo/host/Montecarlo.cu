#include "Device.h"
#include "Montecarlo.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

extern __global__ void montecarlo(curandState* tabDevGeneratorGM, int n, float* ptrResultGM);
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
    Device::malloc(&ptrResultGM, sizeof(pi));
    Device::memclear(ptrResultGM, sizeof(pi));
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
montecarlo<<<grid.dg, grid.db, 1024*sizeof(float)>>>(tabDevGeneratorGM, nPerThread, ptrResultGM);

Device::memcpyDToH(&pi, ptrResultGM, sizeof(float));
pi = 2 * 4 * pi / (float) n;
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

