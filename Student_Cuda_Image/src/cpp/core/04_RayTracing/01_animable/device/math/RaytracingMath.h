#pragma once

#include <math.h>
#include "MathTools.h"

#include "cudaTools.h"
#include "Calibreur_GPU.h"
#include "ColorTools_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RaytracingMath
    {
	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	__device__
	RaytracingMath(uint w, uint h, int nbSphere, Sphere* ptrDevTabSphere)
	    {
	    this->dim2 = w / 2.f;

	    }

	// constructeur copie: pas besoin car pas attribut ptr

	__device__
	virtual ~RaytracingMath(void)
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorIJ(uchar4* ptrColorIJ, int i, int j, float t)
	    {
	    // TODO
	    }

    private:


	/*--------------------------------------*\
	|*		Attribut			*|
	 \*-------------------------------------*/

    private:

	// Tools
	float dim2;

	// Inputs
	int nbSphere
	Sphere* ptrDevTabSphere

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
