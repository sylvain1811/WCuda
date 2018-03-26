#pragma once

#include "cudaTools.h"
#include "Grid.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Slice
    {
    public:

	Slice(int n, const Grid& grid);
	~Slice();
	void run();
	float getPi();

    private:

	// Inputs
	int n;
	Grid grid;

	// Outputs
	float pi;

	// Tools
	float* ptrTab;
	float* ptrTabGM;
	size_t sizeTab;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
