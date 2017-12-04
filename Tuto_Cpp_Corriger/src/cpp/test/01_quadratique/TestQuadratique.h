#pragma once

#include "cpptest.h"

#include "Quadratique.h"

class TestQuadratique: public Test::Suite
    {

	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	TestQuadratique(void);

	virtual ~TestQuadratique();

	/*--------------------------------------*\
	 |*		Methode			*|
	 \*-------------------------------------*/

    private:

	void test2Solutions(void);

	void test1Solution(void);

	void test0Solution(void);

	/*--------------------------------------*\
	 |*		Attributes private	*|
	 \*-------------------------------------*/

    private:

	double epsilon;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

