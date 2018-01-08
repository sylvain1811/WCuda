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
    this->t = variateurAnimation.varierAndGet(); // in [30,100]
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void Mandelbrot::processEntrelacementOMP(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    MandelbrotMath mandelbrotMath(n);

    const int WH = w * h;

#pragma omp parallel
	{
	const int NB_THREAD = OmpTools::getNbThread();
	const int TID = OmpTools::getTid();

	int i;
	int j;

	int s = TID;
	while (s < WH)
	    {
	    IndiceTools::toIJ(s, w, &i, &j);

	    workPixel(&ptrTabPixels[s], i, j, domaineMath, &mandelbrotMath);

	    s += NB_THREAD;
	    }
	}
    }

void Mandelbrot::processForAutoOMP(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    MandelbrotMath mandelbrotMath(n);

#pragma omp parallel for
    for (int i = 0; i < h; i++)
	{
	for (int j = 0; j < w; j++)
	    {
	    int s = IndiceTools::toS(w, i, j);
	    workPixel(&ptrTabPixels[s], i, j, domaineMath, &mandelbrotMath);
	    }
	}
    }

/**
 * i in [0,h[
 * j in [0,w[
 *
 * code commun a:
 * 	- entrelacementOMP
 * 	- forAutoOMP
 */
void Mandelbrot::workPixel(uchar4* ptrColorIJ, int i, int j, const DomaineMath& domaineMath, MandelbrotMath* ptrMandelbrotMath)
    {
    // (i,j) domaine ecran dans N2
    // (x,y) domaine math dans R2

    double x;
    double y;
    domaineMath.toXY(i, j, &x, &y); // fill (x,y) from (i,j)

    ptrMandelbrotMath->colorXY(ptrColorIJ, x, y, t); // in [01]
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

