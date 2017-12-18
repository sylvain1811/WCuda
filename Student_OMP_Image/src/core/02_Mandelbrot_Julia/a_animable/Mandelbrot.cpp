#include "Mandelbrot.h"
#include "MandelbrotMath.h"

#include <iostream>
#include <omp.h>
#include "OmpTools.h"

#include "IndiceTools_CPU.h"
using cpu::IndiceTools;

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

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

Mandelbrot::Mandelbrot(uint w, uint h, float dt, uint n, const DomaineMath& domaineMath) :
	Animable_I<uchar4>(w, h, "Mandelbrot_OMP", domaineMath), variateurAnimation(Interval<float>(20, 120), dt)
    {
    // Input
    this->n = n;

    // Tools
    this->t = 0;
    this->parallelPatern = ParallelPatern::OMP_MIXTE;

    // OMP
    cout << "\n[Mandelbrot] : OMP : nbThread = " << this->nbThread << endl;
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
    this->t = variateurAnimation.varierAndGet(); // in [20,120]
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void Mandelbrot::processForAutoOMP(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath)
    {

    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

