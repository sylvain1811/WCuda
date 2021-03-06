#pragma once

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class Algo
    {

	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	Algo();

	virtual ~Algo();

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	/**
	 * returns z = phi(h(x))
	 */
	int z(int x);

    protected:

	int phi(int y);

	/**
	 * must be overridden
	 */
	virtual int h(int x) = 0;

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
