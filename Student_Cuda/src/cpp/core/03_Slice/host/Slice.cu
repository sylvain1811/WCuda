#include "Slice.h"
#include "Device.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

extern __global__ void slice(int n, float* ptrTabGM);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

Slice::Slice(int n, const Grid& grid)
    {
    this->n = n;
    this->grid = grid;
    this->sizeTab = n * sizeof(float);
    this->ptrTab = new float[n];
    this->pi = 0.0;

    // MM
    Device::malloc(&ptrTabGM, sizeTab);
    }

Slice::~Slice()
    {
    Device::free(ptrTabGM);
    delete[] ptrTab;
    }

float Slice::getPi()
    {
    return this->pi;
    }

void Slice::run()
    {
    slice<<<grid.dg, grid.db>>>(n, ptrTabGM);

    Device::memcpyDToH(ptrTab, ptrTabGM, sizeTab);

    int i = 0;
    float sum = 0.0;

#pragma omp parallel for reduction(+:sum)
    for (i = 0; i < n; i++)
	{
	sum += ptrTab[i];
	}

    pi = sum / (float) n;
    }
/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

