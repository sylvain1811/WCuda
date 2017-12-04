#include <omp.h>
#include "MathTools.h"
#include "OmpTools.h"
#include "../02_Slice/00_pi_tools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforPromotionTab_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPforPromotionTab(int n);
static void syntaxeSimplifier(double* tabSumThread, int n);
static void syntaxeFull(double* tabSumThread, int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforPromotionTab_Ok(int n)
    {
    return isAlgoPI_OK(piOMPforPromotionTab, n, "Pi OMP for promotion tab");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * De-synchronisation avec PromotionTab
 */
double piOMPforPromotionTab(int n)
    {
    const double DX = 1 / (double) n;
    double sum = 0;
    const int NB_THREAD = OmpTools::setAndGetNaturalGranularity();
    double tabSommeThread[NB_THREAD];

    // Initialisation séquentielle
    for (int c = 0; c < NB_THREAD; c++)
	{
	tabSommeThread[c] = 0;
	}

#pragma omp parallel for
    for (int i = 0; i < n; i++)
	{
	double xi = i * DX;
	const int TID = OmpTools::getTid();
	tabSommeThread[TID] += fpi(xi);
	}

    // Reduction sequentielle du tableau promu -> GRATUIT
    double somme = 0;
    for (int i = 0; i < NB_THREAD; i++)
	{
	somme += tabSommeThread[i];
	}

    return somme * DX;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

