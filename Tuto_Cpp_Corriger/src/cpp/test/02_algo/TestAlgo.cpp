#include "TestAlgo.h"

#include "../../core/02_heritage/inherited/AlgoA.h"
#include "../../core/02_heritage/inherited/AlgoB.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur		*|
 \*-------------------------------------*/

TestAlgo::TestAlgo()
    {
    TEST_ADD(TestAlgo::testAlgoA);
    TEST_ADD(TestAlgo::testAlgoB);
    }

TestAlgo::~TestAlgo()
    {
    // rien
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void TestAlgo::testAlgoA(void)
    {
    Algo* ptrAlgo = new AlgoA();

    int x = 10;
    int z = ptrAlgo->z(x);
    int zExpected = 22; // (10+1)*2

    TEST_ASSERT(z == zExpected);

    delete ptrAlgo;
    }

void TestAlgo::testAlgoB(void)
    {
    Algo* ptrAlgo = new AlgoB();

    int x = 10;
    int z = ptrAlgo->z(x);
    int zExpected = 18; // (10-1)*2

    TEST_ASSERT(z == zExpected);

    delete ptrAlgo;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

