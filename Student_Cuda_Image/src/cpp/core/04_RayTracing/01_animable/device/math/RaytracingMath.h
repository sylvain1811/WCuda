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
	RaytracingMath(uint w, uint h)
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
	    uchar levelGris;

	    f(j, i, t, &levelGris);

	    ptrColorIJ->x = levelGris;
	    ptrColorIJ->y = levelGris;
	    ptrColorIJ->z = levelGris;

	    ptrColorIJ->w = 255; //opaque
	    }

    private:

	__device__
	void f(int i, int j, float t, uchar* ptrlevelGris)
	    {
	    float result;
	    dij(i, j, &result); // warning : dij return void. Ne peut pas etre "imbriquer dans une fonction"

	    result = result / 10.f;
	    // TODO cf fonction math pdf

	    float numerateur = cosf(result - t / 7.f);
	    float denominateur = result + 1.f;

	    *ptrlevelGris = 128.f + 127.f * (numerateur / denominateur);
	    }

	__device__
	void dij(int i, int j, float* ptrResult)
	    {
	    //TODO cf fonction math pdf
	    float fi = i - dim2;
	    float fj = j - dim2;
	    *ptrResult = sqrtf(fi * fi + fj * fj);
	    }

	/*--------------------------------------*\
	|*		Attribut			*|
	 \*-------------------------------------*/

    private:

	// Tools
	float dim2;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
