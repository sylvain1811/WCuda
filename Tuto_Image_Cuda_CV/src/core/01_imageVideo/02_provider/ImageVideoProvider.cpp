#include "ImageVideo.h"
#include "ImageVideoProvider.h"

#include "MathTools.h"
#include "Grid.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static string nameVideo();

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Override
 */
Animable_I<uchar4>* ImageVideoProvider::createAnimable()
    {
    // video
    string videoName = nameVideo();

    // Dimension : neil pryde
    // int dw = 640;
    // int dh = 360;

    // Dimension : autoroute
    int w = 1920;
    int h = 1080;

    // Grid Cuda
     int mp=Device::getMPCount();
     int coreMP=Device::getCoreCountMP();

     dim3 dg = dim3(mp, 2, 1);  	// disons a optimiser, depend du gpu
     dim3 db = dim3(coreMP, 2, 1);   	// disons a optimiser, depend du gpu
     Grid grid(dg, db);

    return new ImageVideo(grid,w, h, videoName);
    }

/**
 * Override
 */
Image_I* ImageVideoProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(1, 0, 0); // red
    return new ImageAnimable_RGBA_uchar4(createAnimable(), colorTexte);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

string nameVideo()
    {
    // Important de tester en haute definition (autoroute.mp4) pour vallider la dll ffmpeg
    // petite video ne l'utilise pas!

#ifdef _WIN32
    // Work
	{
	//return "C:\\Users\\cedric.bilat\\Desktop\\neilPryde.avi";// ok
	//return"C:\\Users\\cedric.bilat\\Desktop\\autoroute.mp4";//ok
	}

    // Home
	{
	//  return "C:\\Users\\bilat\\Desktop\\neilPryde.avi"; // ok
	return "C:\\Users\\bilat\\Desktop\\autoroute.mp4";// ok
	}
//#elif  __arm__
#else
	{
	 // return "/opt/cbi/data/video/neilPryde.avi"; // ok
	return "/opt/cbi/data/video/autoroute.mp4"; // ok
	}
#endif
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
