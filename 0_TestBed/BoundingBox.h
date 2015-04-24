/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#ifndef BOUNDING_BOX
#define BOUNDING_BOX

#include "ME\MyEngine.h"

class BoundingBox
{
	String name; // Name used to relate to instance in mesh manager
	vector3 scale; // Size of rectangle
	vector3 centroid; // Centroid of rectangle
	vector3 minVertices; // Min xy-values of rectangle
	vector3 maxVertices; // Max xy-values of rectangle

public:
	/* Constructor */
	BoundingBox(String n);

	/* Destructor */
	~BoundingBox();

	/* GetName */
	/* Returns name of rectangle */
	String GetName();

	/* GetScale */
	/* Returns vector containing scaling in xy-directions */
	vector3 GetScale();

	/* GetCentroid */
	/* Returns centroid of rectangle */
	vector3 GetCentroid();

	/* GetMin */
	/* Returns min xy-values of box */
	vector3 GetMin();

	/* GetMax */
	/* Returns max xy-values of box */
	vector3 GetMax();

	/* GenerateBoundingBox */
	/* Creates collision rectangle around specified model */
	void GenerateBoundingBox();

	/* AddToRenderList */
	/* Creates visual representation of collision rectangle surrounding model */
	void AddToRenderList(matrix4 pos);
};
#endif
