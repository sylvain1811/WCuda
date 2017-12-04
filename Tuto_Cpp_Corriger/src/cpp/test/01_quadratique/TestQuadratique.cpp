#include "TestQuadratique.h"

using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur		*|
 \*-------------------------------------*/

TestQuadratique::TestQuadratique() :
	epsilon(1e-6)
    {
    TEST_ADD(TestQuadratique::test2Solutions);
    TEST_ADD(TestQuadratique::test1Solution);
    TEST_ADD(TestQuadratique::test0Solution);
    }

TestQuadratique::~TestQuadratique()
    {
    // rien
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void TestQuadratique::test2Solutions(void)
    {
    ABC abc2Solutions = ABC(3, 3, -6);
    Quadratique quadratique(abc2Solutions);
    int nbSolutions = quadratique.solve();
    double* tabX = quadratique.getTabX();

    TEST_ASSERT(nbSolutions == 2);

    // works in this case but since we're working with floating point numbers ...
    TEST_ASSERT(tabX[0] == 1);
    TEST_ASSERT(tabX[1] == -2);

    //...this is better
    TEST_ASSERT_DELTA(tabX[0], 1, epsilon);
    TEST_ASSERT_DELTA(tabX[1], -2, epsilon);
    }

void TestQuadratique::test1Solution(void)
    {
    ABC abc1Solution = ABC(2, -4, 2);
    Quadratique quadratique(abc1Solution);
    int nbSolutions = quadratique.solve();
    double* tabX = quadratique.getTabX();

    TEST_ASSERT(nbSolutions == 1);

    // works in this case but since we're working with floating point numbers ...
    TEST_ASSERT(tabX[0] == 1);

    //... this is better
    TEST_ASSERT_DELTA(tabX[0], 1, epsilon);
    }

void TestQuadratique::test0Solution(void)
    {
    ABC abc0Solution = ABC(1, 1, 1);
    Quadratique quadratique(abc0Solution);
    int nbSolutions = quadratique.solve();

    TEST_ASSERT(nbSolutions == 0);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

