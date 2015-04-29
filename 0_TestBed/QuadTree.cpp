#include "QuadTree.h"

/* Constructor */
QuadTree::QuadTree() {
	minNumObjects = 2;
	groups = vector<vector<GameObject*>>();
	squares = vector<vector<Square>>();
}

/* Destructor */
QuadTree::~QuadTree() {
}

/* GetGroups */
vector<vector<GameObject*>> QuadTree::GetGroups() {
	return groups;
}

/* GetSquares */
vector<vector<QuadTree::Square>> QuadTree::GetSquares() {
	return squares;
}


/* GenerateQuadTree */
void QuadTree::GenerateQuadTree(vector<GameObject*> gameObjects, matrix4 pos, vector3 scale) {
	int counter = 0;
	vector<GameObject*> containing;
	
	BoundingBox* box = new BoundingBox("Square", pos);
	box->scale *= 3.0f;

	for(int i = 0; gameObjects.size(); i++) {
	}
}
