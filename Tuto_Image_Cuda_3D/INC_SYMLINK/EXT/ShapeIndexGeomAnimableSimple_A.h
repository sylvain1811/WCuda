#ifndef SHAPEINDEXGEOMANIMABLESIMPLE_A_H_
#define SHAPEINDEXGEOMANIMABLESIMPLE_A_H_

#include "ShapeIndexedGeomAnimable.h"
#include "VertexMode.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_SCENE3D_GL ShapeIndexGeomAnimableSimple_A: public ShapeIndexedGeomAnimable
    {
	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/
    public:

	/**
	 * flags :
	 *  VertexMode::ENABLE_COORDINATE Mandatory!
	 *  VertexMode::ENABLE_COLOR_RGBA
	 *  VertexMode::ENABLE_NORMAL
	 *  VertexMode::ENABLE_TEXTURE
	 *  unsigned int flag= ENABLE_COORDINATE | ENABLE_NORMAL, ...
	 *
	 *  The order in the Buffer is the same
	 *  getBuffer(0) will get the VertexCoordinate Buffer.
	 */
	ShapeIndexGeomAnimableSimple_A(GLenum primitiveType, unsigned int vertexLength, unsigned int indexLenght, unsigned int flags,
		BufferFactory_I* ptrBufferFactory);

	virtual ~ShapeIndexGeomAnimableSimple_A();

	/*--------------------------------------*\
	|*		Surcharge		*|
	 \*-------------------------------------*/

    protected:

	virtual void initGL();

	virtual void fillBufferGL();

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    protected:

	virtual void fillTabCoordinate(float* tabCoordinateXYZ, unsigned int vertexSize)=0;

	virtual void fillTabIndex(unsigned int* tabIndex, unsigned int indexSize)=0;

	virtual void fillTabColor(unsigned char* tabColorRGBA, unsigned int vertexSize);

	virtual void fillTabNormal(float* tabNormalXYZ, float* tabVertexXYZ, unsigned int vertexSize, unsigned int* tabIndex, unsigned int indexSize);

	virtual void fillTabTextureCoord(float* tabTextureCoordXY, unsigned int vertexSize);

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:
	unsigned int flags;

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
