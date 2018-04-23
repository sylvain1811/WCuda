#include "../03_Test_Slice/TestSlice.h"
#include "MathTools.h"
#include "../../../core/03_Slice/host/Slice.h"

#include "Device.h"

#define M_PI 3.14159265358979323846

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern bool useSlice();

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructor		*|
 \*-------------------------------------*/

TestSlice::TestSlice(int deviceId)
    {
    this->deviceId = deviceId;

    TEST_ADD(TestSlice::testPi);
    }

/*--------------------------------------*\
 |*		Methodes		*|
 \*-------------------------------------*/

void TestSlice::testPi(void)
    {
    const int n = 100000;

    // Grid cuda
    int mp = Device::getMPCount();
    int coreMP = Device::getCoreCountMP();

    // Entrelacement
    dim3 dg = dim3(mp, 2, 1);
    dim3 db = dim3(coreMP, 3, 1);
    Grid grid(dg, db);

    Slice slice(n, grid);
    slice.run();

    const float epsilon = 0.1;

    TEST_ASSERT(MathTools::isEquals((float)slice.getPi(), (float)M_PI, epsilon));
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

