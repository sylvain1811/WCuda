#include "AlgoB.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur		*|
 \*-------------------------------------*/

/**
 * constructeur principal
 *
 */
AlgoB::AlgoB() :
	Algo()
    {
    }

AlgoB::~AlgoB()
    {
    // rien, car aucun new dans le constructeur
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

/**
 * override
 */
int AlgoB::h(int x)
    {
    return x - 1;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

