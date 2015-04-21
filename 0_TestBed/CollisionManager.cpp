#include "CollisionManager.h"

CollisionManager* CollisionManager::instance = nullptr;

/* Constructor */
CollisionManager::CollisionManager(){
	boundingBoxes = std::vector<BoundingBox*>();
}

/* Destructor */
CollisionManager::~CollisionManager(){
	if(instance != nullptr)
		instance = nullptr;
}

/* GetInstance */
CollisionManager* CollisionManager::GetInstance() {
	if(instance == nullptr) {
		instance = new CollisionManager();
	}

	return instance;
}

/* GenerateBoundingBox */
void CollisionManager::GenerateBoundingBox(String name) {
	if(GetBox(name) != nullptr) {
		GetBox(name)->GenerateBoundingBox();
	}
	else {
		BoundingBox* b = new BoundingBox(name);
		boundingBoxes.push_back(b);
	}
}

/* GenerateBoundingBoxes */
void CollisionManager::GenerateBoundingBoxes(matrix4 p1, matrix4 p2, matrix4 b) {
	GenerateBoundingBox("Player1");
	GenerateBoundingBox("Player2");
	GenerateBoundingBox("Ball");
	RenderBoxes(p1, p2, b);
}

/* RenderBoxes */
void CollisionManager::RenderBoxes(matrix4 p1, matrix4 p2, matrix4 b) {
	GetBox("Player1")->AddToRenderList(p1);
	GetBox("Player2")->AddToRenderList(p2);
	GetBox("Ball")->AddToRenderList(b);
}

/* GetBox */
BoundingBox* CollisionManager::GetBox(String name) {
	int rectNum = IdentifyBox(name);

	if(rectNum != -1) 
		return boundingBoxes[rectNum];
	
	return nullptr;
}

/* IdentifyRectangle */
int CollisionManager::IdentifyBox(String n) {
	for(unsigned int i = 0; i < boundingBoxes.size(); i++) {
		if(boundingBoxes[i]->GetName() == n) 
			return i;
	}

	return -1;
}

/* PlayerInBounds */
matrix4 CollisionManager::PlayerInBounds(matrix4 p, String name) {
	matrix4 pPos = p;
	vector3 pScale(0.0f, 0.0f, 0.0f);

	if(IdentifyBox(name) != -1) {
		pPos *= glm::translate(GetBox(name)->GetCentroid());
		pScale = GetBox(name)->GetScale();
	}

	if(pPos[3].y + pScale.y/2.0f < -2.1) {
		p[3].y = -2 - pScale.y;
	}
	else if(pPos[3].y - pScale.y/2.0f > 2) {
		p[3].y = 2;
	}

	return p;
}

/* BallCollision */
bool CollisionManager::BallCollision(Player& p1, Player& p2, Ball& b) {
	vector3 p1Pos = static_cast<vector3>(p1.GetPosition() * vector4(GetBox("Player1")->GetCentroid(), 1.0f));
	vector3 p2Pos = static_cast<vector3>(p2.GetPosition() * vector4(GetBox("Player2")->GetCentroid(), 1.0f));
	vector3 bPos = static_cast<vector3>(b.GetPosition() * vector4(GetBox("Ball")->GetCentroid(), 1.0f));

	vector3 p1Min = p1Pos + GetBox("Player1")->GetMin();
	vector3 p1Max = p1Pos + GetBox("Player1")->GetMax();
	vector3 p2Min = p2Pos + GetBox("Player2")->GetMin();
	vector3 p2Max = p2Pos + GetBox("Player2")->GetMax();
	vector3 bMin = bPos + GetBox("Ball")->GetMin();
	vector3 bMax = bPos + GetBox("Ball")->GetMax();

	if(p1Min.x < bMax.x &&
		p1Max.x > bMin.x &&
		p1Min.y < bMax.y &&
		p1Max.y > bMin.y) {
			return true;
	} else if(p2Min.x < bMax.x &&
		p2Max.x > bMin.x &&
		p2Min.y < bMax.y &&
		p2Max.y > bMin.y) {
			return true;
	}

	return false;
}
