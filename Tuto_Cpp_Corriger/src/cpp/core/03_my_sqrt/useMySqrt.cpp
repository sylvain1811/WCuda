#include <iostream>
#include <math.h>

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

void useMySqrt(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void useSqrtOK(void);
static void useSqrtKO(void);
static void mySqrt(double x, double* ptrY);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void useMySqrt(void)
    {
    cout << "\nMySqrt" << endl;

    useSqrtOK();

    //will make a Segmentation fault
   // useSqrtKO();
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void useSqrtOK(void)
    {
    cout << "useSqrtOK" << endl;

    double x = 4;
    double y; // allocates memory for a double

    mySqrt(x, &y); // uses the pointer to y to change its value

    cout << "sqrt(" << x << ")=" << y << endl;
    }

/**
 * Segmentation fault
 */
void useSqrtKO(void)
    {
    cout << "useSqrtKO, will make a segfault" << endl;

    double x = 4;
    double* ptrY; // creates a pointer but does not allocate space for a double

    // when you try to change the value of *ptrY in the mySqrt function,
    // the OS doesn't allow you because the space is not allocated
    mySqrt(x, ptrY);

    cout << "sqrt(" << x << ")=" << *ptrY << endl;
    }

void mySqrt(double x, double* ptrY)
    {
    // v1
//	{
//	double y = sqrt(x);
//	*ptrY = y;
//	}

    // v2
	{
	*ptrY = sqrt(x);
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

