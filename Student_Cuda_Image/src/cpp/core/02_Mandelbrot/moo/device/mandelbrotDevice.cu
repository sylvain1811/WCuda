#include <cudaTools.h>
#include <DomaineMath_GPU.h>
#include <Indice2D.h>
#include <IndiceTools_GPU.h>

#include "math/MandelbrotMath.h"

using namespace gpu;

// Attention : 	Choix du nom est impotant!
//		VagueDevice.cu et non Vague.cu
// 		Dans ce dernier cas, probl�me de linkage, car le nom du .cu est le meme que le nom d'un .cpp (host)
//		On a donc ajouter Device (ou n'importequoi) pour que les noms soient diff�rents!

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void mandelbrot(uchar4* ptrDevPixels, uint w, uint h, float t, uint n, DomaineMath domaineMath);
__global__ void workPixel(uchar4* ptrColorIJ, int i, int j, DomaineMath domaineMath, MandelbrotMath* ptrMandelbrotMath, float t);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void mandelbrot(uchar4* ptrDevPixels, uint w, uint h, float t, uint n, DomaineMath domaineMath)
    {
    MandelbrotMath mandelbrotMath = MandelbrotMath(n);

    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();
    const int WH = w * h;

    // TODO pattern entrelacement
    int i;
    int j;

    int s = TID;

    while (s < WH)
	{

	IndiceTools::toIJ(s, w, &i, &j);

	//workPixel<<<>>>(&ptrDevPixels[s], i, j, domaineMath, &mandelbrotMath, t);

	double x;
	double y;
	domaineMath.toXY(i, j, &x, &y); // fill (x,y) from (i,j)

	(&mandelbrotMath)->colorXY(&ptrDevPixels[s], x, y, t); // in [01]

	s += NB_THREAD;
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__global__ void workPixel(uchar4* ptrColorIJ, int i, int j, const DomaineMath& domaineMath, MandelbrotMath* ptrMandelbrotMath, float t)
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

