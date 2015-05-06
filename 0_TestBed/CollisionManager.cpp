#include "CollisionManager.h"

CollisionManager* CollisionManager::instance = nullptr;

/* Constructor */
CollisionManager::CollisionManager(){
	boundsScale = vector3(20.0f, 10.0f, 0.1f);
	quadTree = new QuadTree();
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
void CollisionManager::Update(Player& player1, Player& player2, Ball& ball1, Ball& ball2, std::vector<GameObject*> gameObjects, std::vector<Bomb*> bombs) {
	PlayerCollision(player1, ball1);
	PlayerCollision(player2, ball1);

	PlayerCollision(player1, ball2);
	PlayerCollision(player2, ball2);

	BallBallCollision(ball1, ball2);
	BallBallCollision(ball2, ball1);
}

/* RenderBoxes */
void CollisionManager::RenderBoxes(std::vector<GameObject*> gameObjects) {
	for(int i = 0; i < gameObjects.size(); i++) {
		GameObject* g = gameObjects[i];

		g->boundingBox->AddToRenderList();
	}
}

/* RenderQuadTree */
void CollisionManager::RenderQuadTree() {
	quadTree->DrawTree();
}

/* BallCollision */
bool CollisionManager::PlayerCollision(Player& player, Ball& ball) {
	/* Player1 Check */
	if (player.boundingBox->CollidesWith(*ball.boundingBox)) {
		ball.SwitchDirection(ball, player);
		return true;
	}
	return false;
}

/* BallCollision */
bool CollisionManager::BallBallCollision(Ball& ball1, Ball& ball2) {
	if (ball1.boundingBox->CollidesWith(*ball2.boundingBox)) {
		ball1.ballOnBallCollision(ball1, ball2);
		return true;
	}
	return false;
}

/* BombCollisions */
bool CollisionManager::BombCollision(Ball& ball, std::vector<Bomb*>& bombs) {
	return false;
}

/* DrawBounds */
void CollisionManager::DrawBounds() {
	MeshManagerSingleton* meshManager = MeshManagerSingleton::GetInstance();
	meshManager->AddCubeToQueue(matrix4(IDENTITY) * glm::scale(boundsScale), MERED, MERENDER::WIRE);
}