#pragma once

#include <iostream>

#include "ABC.h"

using std::ostream;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class Quadratique
    {

	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	/**
	 * Hyp: a!=0
	 */
	Quadratique(double a, double b, double c);

	/**
	 * Hyp: abc.a !=0
	 */
	Quadratique(ABC abc);

	virtual ~Quadratique();

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	/**
	 * returns the number of solutions
	 */
	int solve();

	/**
	 * returns the array of solutions
	 */
	double* getTabX();

	/**
	 * surcharge <<
	 */
	friend ostream& operator <<(ostream& stream, const Quadratique& q);

    private:

	void discriminant();

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	double a;
	double b;
	double c;

	// Outputs
	double* tabX;
	int nbSolution;

	// Tools
	double delta;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
