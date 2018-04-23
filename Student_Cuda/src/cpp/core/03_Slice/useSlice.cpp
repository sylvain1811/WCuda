#include <iostream>
#include "Grid.h"
#include "Device.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

#include "Slice.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useSlice(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useSlice()
    {
    int n = 100000;

    // Partie interessante GPGPU
	{
	// Grid cuda
	int mp = Device::getMPCount();
	int coreMP = Device::getCoreCountMP();

	// Entrelacement
	dim3 dg = dim3(mp, 2, 1);  		// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
	dim3 db = dim3(coreMP, 3, 1);   	// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
	Grid grid(dg, db);

	Slice slice(n, grid); // on passe la grille à Slice pour pouvoir facilement la faire varier de l'extérieur (ici) pour trouver l'optimum
	slice.run();
	cout << "Slice PI : " << slice.getPi() << endl;
	}
    return true;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

