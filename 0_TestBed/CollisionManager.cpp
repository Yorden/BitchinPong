#include "CollisionManager.h"

CollisionManager* CollisionManager::instance = nullptr;

/* Constructor */
CollisionManager::CollisionManager(){
	boundsScale = vector3(36.0f, 20.0f, 0.1f);
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
void CollisionManager::Update(Player& player1, Player& player2,  std::vector<Ball*> ballList, std::vector<GameObject*> gameObjects, std::vector<Bomb*> bombs) {
	
	int ballListSize = ballList.size();
	for(int i = 0; i < ballListSize; i++){
		for(int j = i+1; j < ballListSize; j++){
			BallBallCollision(*ballList[i] , *ballList[j]);
		}
	}

	for(int i = 0; i < ballListSize; i++){
		PlayerCollision(player1, *ballList[i]);
		PlayerCollision(player2, *ballList[i]);
	}



	

	groups.clear();
	groups = quadTree->GenerateGroups(gameObjects, matrix4(IDENTITY), vector3(36.0f, 20.0f, 0.0f));
}

/* Draw */
void CollisionManager::Draw(std::vector<GameObject*> gameObjects) {
	RenderBoxes(gameObjects);
	quadTree->DrawTree();
	DrawBounds();
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
//bool CollisionManager::BombCollision(Ball& ball, std::vector<Bomb*>& bombs) {
bool CollisionManager::BombCollision(Ball& ball, Bomb* bomb) {	
	if (ball.boundingBox->CollidesWith(*bomb->boundingBox))
	{
		return true;
	}
	return false;
}

/* DrawBounds */
void CollisionManager::DrawBounds() {
	MeshManagerSingleton* meshManager = MeshManagerSingleton::GetInstance();
	meshManager->AddCubeToQueue(matrix4(IDENTITY) * glm::scale(boundsScale), MERED, MERENDER::WIRE);
}