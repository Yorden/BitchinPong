#include "CollisionManager.h"

CollisionManager* CollisionManager::instance = nullptr;

/* Constructor */
CollisionManager::CollisionManager(){
	boundsScale = vector3(10.0f, 5.5f, 0.1f);
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
void CollisionManager::Update(Player& player1, Player& player2, Ball& ball, std::vector<GameObject*> gameObjects, std::vector<Bomb*> bombs) {
	PlayerCollision(player1, ball);
	PlayerCollision(player2, ball);
}

/* RenderBoxes */
void CollisionManager::RenderBoxes(std::vector<GameObject*> gameObjects) {
	for(int i = 0; i < gameObjects.size(); i++) {
		GameObject* g = gameObjects[i];

		g->boundingBox->AddToRenderList();
	}
}

/* BallCollision */
bool CollisionManager::PlayerCollision(Player& player, Ball& ball) {
	/* Player1 Check */
	if (player.boundingBox->CollidesWith(*ball.boundingBox)) {
		ball.SwitchDirection(ball.GetName(), player.GetName());
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
	meshManager->AddCubeToQueue(matrix4(IDENTITY) * glm::scale(boundsScale * 2.0f), MERED, MERENDER::WIRE);
}