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
	    this->nbSphere = nbSphere;
	    this->ptrDevTabSphere = ptrDevTabSphere;
	    }

	// constructeur copie: pas besoin car pas attribut ptr

	__device__ virtual ~RaytracingMath(void)
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
	    float distanceMin = 9999999.f;
	    Sphere* sphereLaPlusProche = 0;
	    float keepedDz = 0.f;
	    float2 xysol = make_float2(i, j);

	    for (int index = 0; index < nbSphere; index++)
		{
		float hCarre = ptrDevTabSphere[index].hCarre(xysol);

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
		ColorTools::HSB_TO_RVB(sphereLaPlusProche->hue(t), 1, sphereLaPlusProche->brightness(keepedDz), ptrColorIJ);
		}
	    else
		{
		ptrColorIJ->x = 0;
		ptrColorIJ->y = 0;
		ptrColorIJ->z = 0;
		}

	    // opaque
	    ptrColorIJ->w = 255;
	    }

    private:

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	int nbSphere;
	Sphere* ptrDevTabSphere;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
