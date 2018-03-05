#include "Raytracing.h"

#include <iostream>
#include <assert.h>

#include "Device.h"
#include "nbSphere.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void raytracing(uchar4* ptrDevPixels,uint w, uint h,float t,int nbSphere, Sphere* ptrDevTabSphere);
extern __global__ void raytracing(uchar4* ptrDevPixels, uint w, uint h, float t);
extern __host__ void uploadToGPU(Sphere* ptrTabSphere, size_t sizeOctet);
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

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

Raytracing::Raytracing(const Grid& grid, uint w, uint h, float dt) :
	Animable_I<uchar4>(grid, w, h, "Raytracing_Cuda_RGBA_uchar4")
    {
    n = NB_SPHERE;

    assert(w == h);

    // Inputs
    this->dt = dt;

    // Tools
    this->t = 0.0f; // protected dans Animable

    sphereCreator = new SphereCreator(n, w, h);
    ptrTabSphere = sphereCreator->getTabSphere();

    sizeOctet = n * sizeof(Sphere);

    // Global memory
	{
	// Alloc
	Device::malloc(&ptrDevTabSphere, sizeOctet);

	// Copy
	Device::memcpyHToD(ptrDevTabSphere, ptrTabSphere, sizeOctet);
	}

    // Constant memory
	{
	uploadToGPU(ptrTabSphere, sizeOctet);
	}
    }

Raytracing::~Raytracing()
    {
    // Free
    Device::free(ptrDevTabSphere);
    delete sphereCreator;
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 * Call periodicly by the API
 *
 * Note : domaineMath pas use car pas zoomable
 */
void Raytracing::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    Device::lastCudaError("Raytracing rgba uchar4 (before kernel)"); // facultatif, for debug only, remove for release

    // lancer le kernel avec <<<dg,db>>>
    // le kernel est importer ci-dessus (ligne 19)

    //raytracing<<<dg,db>>>(ptrDevPixels, w,h,t, n, ptrDevTabSphere);
    raytracing<<<dg,db>>>(ptrDevPixels, w,h,t);

    Device::lastCudaError("Raytracing rgba uchar4 (after kernel)"); // facultatif, for debug only, remove for release
    }

/**
 * Override
 * Call periodicly by the API
 */
void Raytracing::animationStep()
    {
    t += dt;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

