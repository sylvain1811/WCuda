#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <assert.h>

#include "Quadratique.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void useQuadratique(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void useABC();
static void useQuadratiqueStandard(void);
static void useQuadratiqueABC(void);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * see too unit test
 * /src/cpp/test
 */
void useQuadratique(void)
    {
    useABC();
    useQuadratiqueStandard();
    useQuadratiqueABC();
    }

/*--------------------------------------*\
 |*		private			*|
 \*-------------------------------------*/

void useABC()
    {
    cout << "ABC" << endl;

    ABC abc = ABC(1,2,3);
    cout<<abc;
    }

void useQuadratiqueStandard(void)
    {
    cout << "\nQuadratique Standard" << endl;

    Quadratique q1(3, 3, -1); // {1,-2}
    Quadratique q2(2, -4, 2); // {1}
    Quadratique q3(1, 1, 1); // none
    Quadratique q4(3, 3, -1); // {1,-2}

    q1.solve();
    q2.solve();
    q3.solve();

    cout << q1;
    cout << q2;
    cout << q3;
    cout << q4;
    } // qi est détruit, tabX est détruit

void useQuadratiqueABC(void)
    {
    cout << "\nQuadratique ABC" << endl;

    ABC abc1 = ABC(3, 3, -6);
    ABC abc2 = ABC(2, -4, 2);
    ABC abc3 = ABC(1, 1, 1);

    Quadratique q1(abc1); // {1,-2}
    Quadratique q2(abc2); // {1}
    Quadratique q3(abc3); // none

    q1.solve();
    q2.solve();
    q3.solve();

    cout << q1;
    cout << q2;
    cout << q3;
    } // qi est détruit, tabX est détruit

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

