#pragma once

#include "cudaTools.h"
#include "Grid.h"
#include <curand_kernel.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Montecarlo
    {
    public:

	Montecarlo(int n, const Grid& grid);
	~Montecarlo();
	float getPi();
	void run();

    private:

	// Inputs
	int n;
	Grid grid;

	// Outputs
	float pi;

	// Tools
	float* ptrResultGM;
	curandState* tabDevGeneratorGM;
	size_t sizeTabGenerator;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
