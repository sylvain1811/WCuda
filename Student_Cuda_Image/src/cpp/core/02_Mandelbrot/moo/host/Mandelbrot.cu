#include "Mandelbrot.h"

#include <iostream>
#include <assert.h>

#include "Device.h"
using gpu::DomaineMath;
using namespace gpu;
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void mandelbrot(uchar4* ptrDevPixels, uint w, uint h, float t, uint n, DomaineMath domaineMath);

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

Mandelbrot::Mandelbrot(const Grid& grid, uint w, uint h, float dt, uint n, const DomaineMath& domaineMath) :
	Animable_I<uchar4>(grid, w, h, "Mandelbrot_CUDA", domaineMath), variateurAnimation(Interval<float>(20, 120), dt)
    {
    // Input
    this->n = n;

    // Tools
    this->t = 0;

    }

Mandelbrot::~Mandelbrot(void)
    {
    // Rien
    }

/**
 * Override
 */
void Mandelbrot::animationStep()
    {
    this->t = variateurAnimation.varierAndGet(); // in [30,100]
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void Mandelbrot::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    Device::lastCudaError("Mandelbrot rgba uchar4 (before kernel)"); // facultatif, for debug only, remove for release

    // TODO lancer le kernel avec <<<dg,db>>>
    // le kernel est importer ci-dessus (ligne 19)

    mandelbrot<<<dg,db>>>(ptrDevPixels, w,h,t, n, domaineMath);

    Device::lastCudaError("Mandelbrot rgba uchar4 (after kernel)"); // facultatif, for debug only, remove for release
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

