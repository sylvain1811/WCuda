#pragma once

#include <opencv2/opencv.hpp>
#include <highgui.hpp>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Shape_I
    {
    public:
	virtual ~Shape_I()
	    {

	    }

	virtual void draw(cv::Mat* ptrImage)=0;

    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
