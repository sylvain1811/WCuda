#include "Device.h"

#include "MontecarloMultiGPU.h"
#include "Montecarlo.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

MontecarloMultiGPU::MontecarloMultiGPU(int n, const Grid& grid)
    {
    this->n = n;
    this->grid = grid;
    this->pi = 0.0;

    }

MontecarloMultiGPU::~MontecarloMultiGPU()
    {
    }

void MontecarloMultiGPU::run()
    {
    int n0 = 0;
    int deviceCount = Device::getDeviceCount();
    int nPerDevice = this->n / deviceCount;

#pragma omp parallel for reduction(+:n0)
    for (int devId = 0; devId < deviceCount; devId++)
	{
	Device::setDevice(devId);
	Montecarlo montecarlo(nPerDevice, this->grid);
	montecarlo.run();
	n0 += montecarlo.getN0();
	}

    this->pi = 2 * 2 * 2 * n0 / (double) (nPerDevice * deviceCount); // (xMax - xMin) * h * 2 * n0 / nTot
    }

float MontecarloMultiGPU::getPi()
    {
    return this->pi;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

