#include "Quadratique.h"

#include <math.h> //sqrt, nan
#include <assert.h>

using std::cout;
using std::endl;
/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur		*|
 \*-------------------------------------*/

/**
 * constructeur dominant
 */
Quadratique::Quadratique(double a, double b, double c) :
	a(a), b(b)
    {
    assert(a != 0);

    this->c = c;

    this->tabX = new double[2];
    tabX[0] = nan("");
    tabX[1] = nan("");
    }

/**
 * call constructeur dominant
 */
Quadratique::Quadratique(ABC abc) :
	Quadratique(abc.a, abc.b, abc.c)
    {
    // rien de plus
    }

Quadratique::~Quadratique()
    {
    delete[] tabX;

    // debug pedagogique
//	{
//	cout << "Quadratique::tabX is deleted" << endl;
//	}
    }

/*--------------------------------------*\
 |*		Methode	public		*|
 \*-------------------------------------*/

int Quadratique::solve()
    {
    discriminant();

    if (delta > 0)
	{
	double sqrtDelta = sqrt(delta);

	tabX[0] = (-b + sqrtDelta) / (2 * a);
	tabX[1] = (-b - sqrtDelta) / (2 * a);

	nbSolution = 2;
	}
    else if (delta == 0)
	{
	tabX[0] = -b / (2 * a);

	nbSolution = 1;
	}
    else
	{
	nbSolution = 0;
	}

    return nbSolution;
    }

double* Quadratique::getTabX()
    {
    return tabX;
    }

/*--------------------------------------*\
 |*		Methode	private		*|
 \*-------------------------------------*/

void Quadratique::discriminant()
    {
    this->delta = b * b - 4 * a * c;
    }

/*--------------------------------------*\
 |*		Hors classe		*|
 \*-------------------------------------*/

/**
 * friend
 */
ostream& operator <<(ostream& stream, const Quadratique& q)
    {
    stream << endl << q.a << "x ² + " << q.b << "x + " << q.c;

    if (q.nbSolution >= 1)
	{
	stream << " = 0 ssi" << endl;
	for (int i = 0; i < q.nbSolution; i++)
	    {
	    stream << "x" << i << " = " << q.tabX[i] << endl;
	    }
	}

    stream << endl;

    return stream;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

