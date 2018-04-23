#include "Indice2D.h"
#include "reductionADD.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void sliceAd(int n, float* ptrResultGM);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void sliceAd(int n, float* ptrResultGM)
    {

    extern __shared__ float tabSM[];

    // Reduction intra thread
    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();
    const int TID_LOCAL = Indice2D::tidLocal();

    int s = TID;
    float sum = 0.0;
    float xi;

    while (s < n)
	{
	xi = s / (float) n;
	sum += 4 / (1 + xi * xi);
	s += NB_THREAD;
	}

    tabSM[TID_LOCAL] = sum;

    __syncthreads();

    // Reduction intra block et interblock
    reductionADD(tabSM, ptrResultGM);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
