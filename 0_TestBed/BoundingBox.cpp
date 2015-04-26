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
BoundingBox::~BoundingBox() {
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

/* GenerateBoundingBox */
void BoundingBox::GenerateBoundingBox() {
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

/* AddToRenderList */
void BoundingBox::AddToRenderList() {
	MeshManagerSingleton* meshManager = MeshManagerSingleton::GetInstance();
	meshManager->AddCubeToQueue(position * glm::translate(centroid) * glm::scale(scale), MEBLUE, MERENDER::WIRE);
}