#pragma once

#include "cudaTools.h"
#include "Provider_I_GPU.h"

using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotProvider: public Provider_I<uchar4>
    {
    public:
	virtual ~MandelbrotProvider()
	    {
	    //Rien
	    }

	/*--------------------------------------*\
	 |*		Override		*|
	 \*-------------------------------------*/

	Animable_I<uchar4>* createAnimable(void);

	Image_I* createImageGL(void);

    private:
	double x0 = -2.1;
	double y0 = -1.3;
	double x1 = 0.8;
	double y1 = 1.3;
    };

class MandelbrotProviderCustom1: public MandelbrotProvider
    {
    private:
	double x0 = -0.2;
	double y0 = -1.09;
	double x1 = 0.008;
	double y1 = -0.833;
    };

class MandelbrotProviderCustom2: public MandelbrotProvider
    {
    private:
	double x0 = -1.82;
	double y0 = -0.04;
	double x1 = -1.714;
	double y1 = 0.05;
    };

class MandelbrotProviderCustom3: public MandelbrotProvider
    {
    private:
	double x0 = -0.647;
	double y0 = 0.587;
	double x1 = -0.495;
	double y1 = 0.721;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
