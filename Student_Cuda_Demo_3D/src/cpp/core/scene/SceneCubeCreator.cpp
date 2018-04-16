#include <iostream>

#include "SceneCubeCreator.h"

#include "MandelbrotProvider.h"
#include "MandelbrotProvider1.h"
#include "MandelbrotProvider2.h"
#include "MandelbrotProvider3.h"
#include "RipplingProvider.h"
#include "RaytracingProvider.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructor		*|
 \*-------------------------------------*/

SceneCubeCreator::SceneCubeCreator()
    {
    createImages();
    createScene();
    }

SceneCubeCreator::~SceneCubeCreator()
    {
    delete ptrImage1;
    delete ptrImage2;
    delete ptrImage3;
    delete ptrImage4;
    delete ptrImage5;
    delete ptrImage6;

    delete ptrScene;
    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

SceneCube* SceneCubeCreator::getScene()
    {
    return ptrScene;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void SceneCubeCreator::createImages()
    {
    ptrImage1 = RipplingProvider().createImageGL();
    ptrImage2 = RaytracingProvider().createImageGL();
    ptrImage3 = MandelbrotProvider().createImageGL();
    ptrImage4 = MandelbrotProvider1().createImageGL();
    ptrImage5 = MandelbrotProvider2().createImageGL();
    ptrImage6 = MandelbrotProvider3().createImageGL();
    }

void SceneCubeCreator::createScene()
    {
    ptrScene = new SceneCube(ptrImage1, ptrImage2, ptrImage3, ptrImage4, ptrImage5, ptrImage6);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

