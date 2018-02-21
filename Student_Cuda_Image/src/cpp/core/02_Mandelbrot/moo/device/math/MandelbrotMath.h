#pragma once

#include <math.h>
#include "MathTools.h"

#include "Calibreur_GPU.h"
#include "ColorTools_GPU.h"
using namespace gpu;
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotMath
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ MandelbrotMath(uint n) :
		calibreur(Interval<float>(-1, 1), Interval<float>(0, 1))
	    {
	    this->n = n;
	    }

	__device__
	 virtual ~MandelbrotMath()
	    {
	    // Rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:
	__device__
	void colorXY(uchar4* ptrColor, float x, float y, float t)
	    {
	    float z = f(x, y, t);

	     if (z < 0)
	     {
	     ptrColor->z = 0;
	     ptrColor->x = 0;
	     ptrColor->y = 0;
	     }
	     else
	     {

	     float hue01 = z;
	     //calibreur.calibrer(&hue01);

	     ColorTools::HSB_TO_RVB(hue01, ptrColor); // update color
	     }

	    ptrColor->w = 255; // opaque
//	    ptrColor->z = 125;
//	    ptrColor->x = 125;
//	    ptrColor->y = 125;
	    }

    private:

	__device__
	float f(float x, float y, float t)
	    {

	    float N = t;

	    float a = 0.f;
	    float b = 0.f;

	    int k = 0;
	    while (1)
		{
		float aCopy = a;
		a = (a * a - b * b) + x;
		b = 2 * aCopy * b + y;
		k++;
		if (k > N || (a * a + b * b) > 4)
		    break;
		}

	    if (k > N)
		{
		return -1.0;
		}
	    return (1 / N) * k;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/
    private:
	// Input
	uint n;

	// Tools
	Calibreur<float> calibreur;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
