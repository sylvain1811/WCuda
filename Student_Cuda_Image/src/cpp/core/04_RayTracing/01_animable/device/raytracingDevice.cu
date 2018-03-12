#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"

#include "IndiceTools_GPU.h"
#include "nbSphere.h"

#include "RaytracingMath.h"
using namespace gpu;

// Attention : 	Choix du nom est impotant!
//		VagueDevice.cu et non Vague.cu
// 		Dans ce dernier cas, probl�me de linkage, car le nom du .cu est le meme que le nom d'un .cpp (host)
//		On a donc ajouter Device (ou n'importequoi) pour que les noms soient diff�rents!

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

__constant__ Sphere TAB_SPHERE_CM[NB_SPHERE];

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void raytracing(uchar4* ptrDevPixels, uint w, uint h, float t, int nbSphere, Sphere* ptrDevTabSphere); // GM
__global__ void raytracing(uchar4* ptrDevPixels, uint w, uint h, float t); // CM
__host__ void uploadToGPU(Sphere* ptrTabSphere, size_t sizeOctet);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static __device__ void work(uchar4* ptrDevPixels, uint w, uint h, float t, int nbSphere, Sphere* ptrDevTabSphere);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

// SM
__device__ void copyGMtoSM(Sphere* tabSM, Sphere* tabGM, int n)
    {
    const int NB_THREAD_LOCAL = Indice2D::nbThreadLocal();
    const int TID_LOCAL = Indice2D::tidLocal();
    int s = TID_LOCAL;
    while (s < n)
	{
	tabSM[s] = tabGM[s];
	s += NB_THREAD_LOCAL;
	}
    }

// CM
__host__ void uploadToGPU(Sphere* ptrTabSphere, size_t sizeOctet)
    {
    //Device::memcpyToCM(TAB_SPHERE_CM, ptrTabSphere, sizeOctet);
    cudaMemcpyToSymbol(TAB_SPHERE_CM, ptrTabSphere, sizeOctet, 0, cudaMemcpyHostToDevice);
    }

__global__ void raytracing(uchar4* ptrDevPixels, uint w, uint h, float t) // CM
    {
    work(ptrDevPixels, w, h, t, NB_SPHERE, TAB_SPHERE_CM);
    }

__global__ void raytracing(uchar4* ptrDevPixels, uint w, uint h, float t, int nbSphere, Sphere* ptrDevTabSphere) // GM & SM
    {
    //GM
	{
	//work(ptrDevPixels, w, h, t, nbSphere, ptrDevTabSphere); // GM
	}
    // SM
	{
	__shared__ extern Sphere tabSM[];
	copyGMtoSM(tabSM, ptrDevTabSphere, nbSphere);
	__syncthreads();
	work(ptrDevPixels, w, h, t, nbSphere, tabSM); // SM
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static __device__ void work(uchar4* ptrDevPixels, uint w, uint h, float t, int nbSphere, Sphere* ptrDevTabSphere)
    {
    RaytracingMath raytracingMath = RaytracingMath(w, h, nbSphere, ptrDevTabSphere);

    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();
    const int WH = w * h;

    // Pattern entrelacement
    int i;
    int j;

    int s = TID;

    while (s < WH)
	{

	IndiceTools::toIJ(s, w, &i, &j);

	raytracingMath.colorIJ(&ptrDevPixels[s], i, j, t);

	s += NB_THREAD;
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

