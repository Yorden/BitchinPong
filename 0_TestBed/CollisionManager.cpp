#include "CollisionManager.h"

CollisionManager* CollisionManager::instance = nullptr;

/* Constructor */
CollisionManager::CollisionManager(){
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

/* Update */
void CollisionManager::Update() {
	
}

/* RenderBoxes */
void CollisionManager::RenderBoxes(std::vector<GameObject*> gameObjects) {
	for(int i = 0; i < gameObjects.size(); i++) {
		GameObject* g = gameObjects[i];

		g->boundingBox->AddToRenderList();
	}
}

/* BallCollision */
bool CollisionManager::BallCollision(GameObject& player1, /*GameObject& player2,*/ GameObject& ball) {
	BoundingBox* p1 = player1.boundingBox;
	//BoundingBox* p2 = player2.boundingBox;
	BoundingBox* b = ball.boundingBox;

	float p1Left = vector3(player1.GetPosition() * vector4(p1->GetCentroid(), 1.0f)).x - p1->GetScale().x/2.0f;
	float p1Right = vector3(player1.GetPosition() * vector4(p1->GetCentroid(), 1.0f)).x + p1->GetScale().x/2.0f;
	float p1Top = vector3(player1.GetPosition() * vector4(p1->GetCentroid(), 1.0f)).y + p1->GetScale().y/2.0f;
	float p1Bottom = vector3(player1.GetPosition() * vector4(p1->GetCentroid(), 1.0f)).y - p1->GetScale().y/2.0f;

	//float p2Left = vector3(player2.GetPosition() * vector4(p2->GetCentroid(), 1.0f)).x - p2->GetScale().x/2.0f;
	//float p2Right = vector3(player2.GetPosition() * vector4(p2->GetCentroid(), 1.0f)).x + p2->GetScale().x/2.0f;
	//float p2Top = vector3(player2.GetPosition() * vector4(p2->GetCentroid(), 1.0f)).y + p2->GetScale().y/2.0f;
	//float p2Bottom = vector3(player2.GetPosition() * vector4(p2->GetCentroid(), 1.0f)).y - p2->GetScale().y/2.0f;

	float bLeft = vector3(ball.GetPosition() * vector4(b->GetCentroid(), 1.0f)).x - b->GetScale().x/2.0f;
	float bRight = vector3(ball.GetPosition() * vector4(b->GetCentroid(), 1.0f)).x + b->GetScale().x/2.0f;
	float bTop = vector3(ball.GetPosition() * vector4(b->GetCentroid(), 1.0f)).y + b->GetScale().y/2.0f;
	float bBottom = vector3(ball.GetPosition() * vector4(b->GetCentroid(), 1.0f)).y - b->GetScale().y/2.0f;

	/* Player1 Check */
	if (bLeft < p1Right &&
		bRight > p1Left &&
		bBottom < p1Top &&
		bTop > p1Bottom) {
			return true;
	}

	/* Player2 Check */
	//if (bLeft < p2Right &&
	//	bRight > p2Left &&
	//	bBottom < p2Top &&
	//	bTop > p2Bottom) {
	//		return true;
	//}

	return false;
}
