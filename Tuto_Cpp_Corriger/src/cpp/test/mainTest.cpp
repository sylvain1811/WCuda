#include <stdlib.h>
#include <fstream>
#include <string>

#include "cppTest+.h"

#include "TestQuadratique.h"
#include "TestAlgo.h"

using std::cout;
using std::endl;
using std::string;
using std::auto_ptr;

using Test::Suite;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static bool testAll(void);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainTest(void)
    {
    bool isOk = true;

    isOk &= testAll();

    cout << "\nisOK = " << isOk << endl;

    return isOk ? EXIT_SUCCESS : EXIT_FAILURE;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

bool testAll()
    {
    Suite testSuite;

    testSuite.add(auto_ptr < Suite > (new TestQuadratique()));
    testSuite.add(auto_ptr < Suite > (new TestAlgo()));

    return runTestHtml("out/outTest_HTML", testSuite);
    /// return runTestConsole("Test_Console", testSuite);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

