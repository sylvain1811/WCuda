#pragma once

#include <math.h>
#include "MathTools.h"
#include <iostream>
#include <stdlib.h>
#include "Calibreur_CPU.h"
#include "ColorTools_CPU.h"
using namespace cpu;

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
	MandelbrotMath(uint n) :
		calibreur(Interval<float>(-1, 1), Interval<float>(0, 1))
	    {
	    this->n = n;
	    }

	virtual ~MandelbrotMath()
	    {
	    // Rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:
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
	    }

    private:

	float f(float x, float y, float t)
	    {

	    float N = t;

	    float a = 0;
	    float b = 0;

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
