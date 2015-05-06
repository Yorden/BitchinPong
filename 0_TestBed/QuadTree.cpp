#include "QuadTree.h"

/* Constructor */
QuadTree::QuadTree() {
	minNumObjects = 2;
	groups = vector<vector<GameObject*>>();
	squares = vector<Square*>();
	drawTest = new Square(matrix4(IDENTITY), vector3(20.0f, 10.0f, 0.1f));
}

/* Destructor */
QuadTree::~QuadTree() {
}

/* GetGroups */
vector<vector<GameObject*>> QuadTree::GetGroups() {
	return groups;
}

/* GetSquares */
vector<QuadTree::Square*> QuadTree::GetSquares() {
	return squares;
}


/* GenerateQuadTree */
void QuadTree::GenerateQuadTree(vector<GameObject*> gameObjects, matrix4 pos, vector3 scale) {
	squares.push_back(new Square(pos, scale));
	vector<GameObject*>* gameObjectsPointer = &gameObjects;

	int counter = 0;
	vector<GameObject*> containing;
	
	BoundingBox* box = new BoundingBox("Square", pos);
	box->GenerateBoundingBox_Manual(pos, scale);

	for(int i = 0; i < gameObjects.size(); i++) {
		if(box->Contains(vector3(gameObjects[i]->GetPosition() * vector4(1.0f)) + gameObjects[i]->boundingBox->GetCentroid())) {
			containing.push_back(gameObjects[i]);
		}
	}

	if(containing.size() > minNumObjects) {
		matrix4 topLeft = pos * glm::translate(vector3(-scale.x/4, scale.y/4, 0.0f));
		matrix4 topRight = pos * glm::translate(vector3(scale.x/4, scale.y/4, 0.0f));
		matrix4 bottomLeft = pos * glm::translate(vector3(-scale.x/4, -scale.y/4, 0.0f));
		matrix4 bottomRight = pos * glm::translate(vector3(scale.x/4, -scale.y/4, 0.0f));
		vector3 newScale = scale / 2.0f;
		
		GenerateQuadTree(containing, topLeft, newScale);
		GenerateQuadTree(containing, topRight, newScale);
		GenerateQuadTree(containing, bottomLeft, newScale);
		GenerateQuadTree(containing, bottomRight, newScale);
	}
	else {
	}
}

/* DrawTree */
void QuadTree::DrawTree() {
	for(int i = 0; i < squares.size(); i++) {
		squares[i]->Draw();
	}
}
