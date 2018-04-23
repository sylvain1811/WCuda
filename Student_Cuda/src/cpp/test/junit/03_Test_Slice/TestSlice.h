#pragma once

#include "cpptest.h"

using Test::Suite;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class TestSlice: public Suite
    {
    public:

	TestSlice(int deviceId);

    private:

	void testPi(void);

    private:

	int deviceId;

    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

