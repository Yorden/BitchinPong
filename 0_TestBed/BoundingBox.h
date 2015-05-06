/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#ifndef BOUNDING_BOX
#define BOUNDING_BOX

#include "ME\MyEngine.h"

class BoundingBox
{
public:
	String name; // Name used to relate to instance in mesh manager
	vector3 scale; // Size of rectangle
	matrix4 position; // Box position
	vector3 centroid; // Centroid of rectangle
	vector3 minVertices; // Min xy-values of rectangle
	vector3 maxVertices; // Max xy-values of rectangle

	/* Constructor */
	BoundingBox(String n, matrix4 pos);

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

	/* SetPosition */
	/* Sets position of box in global space */
	void SetPosition(matrix4 pos);

	/* GenerateBoundingBox_Model */
	/* Creates collision box around specified model */
	void GenerateBoundingBox_Model();

	/* GenerateBoundingBox_Manual */
	/* Creates collision box at specified location with specified scale */
	void GenerateBoundingBox_Manual(matrix4 pos, vector3 s);

	/* Contains */
	/* Returns true if the box contains the point specified */
	bool Contains(vector3 point);

	/* CollidesWith */
	/* Returns true if colliding with other specified box */
	bool CollidesWith(BoundingBox& other);

	/* AddToRenderList */
	/* Creates visual representation of collision rectangle surrounding model */
	void AddToRenderList();

};
#endif
