#pragma once

#include "cudaTools.h"
#include "Grid.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class SliceAd
    {
    public:

	SliceAd(int n, const Grid& grid);
	~SliceAd();
	void run();
	float getPi();

    private:

	// Inputs
	int n;
	Grid grid;

	// Outputs
	float pi;

	// Tools
	float* ptrResultGM;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
