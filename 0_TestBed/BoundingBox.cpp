/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#include "BoundingBox.h"

/* Constructor */
BoundingBox::BoundingBox(String n, matrix4 pos) {
	name = n;
	scale = vector3(0.0f);
	position = pos;
	centroid = vector3(0.0f);
	minVertices = vector3(0.0f);
	maxVertices = vector3(0.0f);
}

/* Destructor */
BoundingBox::~BoundingBox() 
{
}

/* GetName */
String BoundingBox::GetName() {
	return name;
}

/* GetScale */
vector3 BoundingBox::GetScale() {
	return scale;
}

/* GetCentroid */
vector3 BoundingBox::GetCentroid() {
	return centroid;
}

/* GetMin */
vector3 BoundingBox::GetMin() {
	return minVertices;
}

/* GetMax */
vector3 BoundingBox::GetMax() {
	return maxVertices;
}

/* SetPosition */
void BoundingBox::SetPosition(matrix4 pos) {
	position = pos;
}

/* GenerateBoundingBox_Model */
void BoundingBox::GenerateBoundingBox_Model() {
	MeshManagerSingleton* mesh = MeshManagerSingleton::GetInstance();

	std::vector<vector3> vertices = mesh->GetVertices(name);

	for(int i = 0; i < vertices.size(); i++) {
		vector2 vertex = vector2(vertices[i].x, vertices[i].y);

		if(vertex.x < minVertices.x)
			minVertices.x = vertex.x;
		else if(vertex.x > maxVertices.x)
			maxVertices.x = vertex.x;

		if(vertex.y < minVertices.y)
			minVertices.y = vertex.y;
		else if(vertex.y > maxVertices.y)
			maxVertices.y = vertex.y;

		centroid = (minVertices + maxVertices) / 2.0f;
		scale.x = glm::distance(vector3(minVertices.x, 0.0f, 0.0f), vector3(maxVertices.x, 0.0f, 0.0f));
		scale.y = glm::distance(vector3(0.0f, minVertices.y, 0.0f), vector3(0.0f, maxVertices.y, 0.0f));
		scale.z = 0.01f;
	}
}

/* GenerateBoundingBox_Manual */
void BoundingBox::GenerateBoundingBox_Manual(matrix4 pos, vector3 s) {
	float left  = -s.x/2;
	float right = s.x/2;
	float top = s.y/2;
	float bottom  = -s.y/2;

	minVertices = vector3(left, bottom, 0.0f);
	maxVertices = vector3(right, top, 0.0f);
	centroid = (minVertices + maxVertices) / 2.0f;
	scale = s;
}

/* Contains */
bool BoundingBox::Contains(vector3 point) {
	float minX = (position * vector4(centroid, 1.0f)).x - scale.x / 2;
	float maxX = (position * vector4(centroid, 1.0f)).x + scale.x / 2;
	float minY = (position * vector4(centroid, 1.0f)).y - scale.y / 2;
	float maxY = (position * vector4(centroid, 1.0f)).y + scale.y / 2;

	if(point.x >= minX &&
		point.x <= maxX &&
		point.y >= minY && 
		point.y <= maxY) {
			return true;
	}

	return false;
}

/* CollidesWith */
bool BoundingBox::CollidesWith(BoundingBox& other) {
	float minX = (position * vector4(centroid, 1.0f)).x - scale.x/2.0f;
	float maxX = (position * vector4(centroid, 1.0f)).x + scale.x/2.0f;
	float minY = (position * vector4(centroid, 1.0f)).y - scale.y/2.0f;
	float maxY = (position * vector4(centroid, 1.0f)).y + scale.y/2.0f;

	float otherMinX = (other.position * vector4(other.centroid, 1.0f)).x - other.scale.x/2.0f;
	float otherMaxX = (other.position * vector4(other.centroid, 1.0f)).x + other.scale.x/2.0f;
	float otherMinY = (other.position * vector4(other.centroid, 1.0f)).y - other.scale.y/2.0f;
	float otherMaxY = (other.position * vector4(other.centroid, 1.0f)).y + other.scale.y/2.0f;

	if (minX < otherMaxX &&
		maxX > otherMinX &&
		minY < otherMaxY &&
		maxY > otherMinY) {
			return true;
	}
	
	return false;
}

/* AddToRenderList */
void BoundingBox::AddToRenderList() {
	MeshManagerSingleton* meshManager = MeshManagerSingleton::GetInstance();
	meshManager->AddCubeToQueue(position * glm::translate(centroid) * glm::scale(scale), MEBLUE, MERENDER::WIRE);
}