#pragma once

#include <math.h>
#include "MathTools.h"
#include "Sphere.h"

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

	__device__ RaytracingMath(uint w, uint h, int nbSphere, Sphere* ptrDevTabSphere)
	    {
	    this->dim2 = w / 2.f;
	    this->nbSphere = nbSphere;
	    this->ptrDevTabSphere = ptrDevTabSphere;
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

	    float distanceMin = 9999999.f;
	    Sphere* sphereLaPlusProche = 0;
	    float keepedDz = 0.f;
	    float2 xysol = make_float2(j, i);
	    int savedIndex = -1;

	    for (int index = 0; index < nbSphere; index++)
		{
		float hCarre = ptrDevTabSphere[index].hCarre(xysol);
		savedIndex = index;

		if (ptrDevTabSphere[index].isEnDessous(hCarre))
		    {
		    float dz = ptrDevTabSphere[index].dz(hCarre);
		    float currentDistance = ptrDevTabSphere[index].distance(dz);

		    if (currentDistance < distanceMin)
			{
			sphereLaPlusProche = &ptrDevTabSphere[index];
			distanceMin = currentDistance;
			keepedDz = dz;
			}
		    }
		}

	    if (sphereLaPlusProche)
		{
		//float r, v, b;

		ColorTools::HSB_TO_RVB(sphereLaPlusProche->hue(t), 1, sphereLaPlusProche->brightness(keepedDz), ptrColorIJ);

		/*ptrColorIJ->x = 200;
		ptrColorIJ->y = 200;
		ptrColorIJ->z = 200;*/
		}
	    else
		{
		ptrColorIJ->x = 125;
		ptrColorIJ->y = 125;
		ptrColorIJ->z = 125;
		}

	    // opaque
	    ptrColorIJ->w = 255;

	    }

    private:

	/*--------------------------------------*\
	|*		Attribut			*|
	 \*-------------------------------------*/

    private:

	// Tools
	float dim2;

	// Inputs
	int nbSphere;
	Sphere* ptrDevTabSphere;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
