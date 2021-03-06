#include "SliceAd.h"
#include "Device.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

extern __global__ void sliceAd(int n, float* ptrTabGM);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

SliceAd::SliceAd(int n, const Grid& grid)
    {
    this->n = n;
    this->grid = grid;
    this->pi = 0.0;

    // MM
    Device::malloc(&ptrResultGM, sizeof(pi));
    Device::memclear(ptrResultGM, sizeof(pi));
    }

SliceAd::~SliceAd()
    {
    Device::free(ptrResultGM);
    }

float SliceAd::getPi()
    {
    return this->pi;
    }

void SliceAd::run()
    {
    sliceAd<<<grid.dg, grid.db, 1024*sizeof(float)>>>(n, ptrResultGM);
    Device::memcpyDToH(&pi, ptrResultGM, sizeof(float));
    pi = pi / (float)n;
    }
/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

