/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

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

/* CheckCollisions */
void CollisionManager::CheckCollisions(std::vector<GameObject*>& gameObjects, Player& player1, Player& player2) {
	groups.clear();
	groups = quadTree->GenerateGroups(gameObjects, matrix4(IDENTITY), vector3(36.0f, 20.0f, 0.0f));

	for(int i = 0; i < groups.size(); i++) {
		for(int j = 0; j < groups[i].size(); j++) {
			for(int k = j + 1; k < groups[i].size(); k++) {
				GameObject* g1 = groups[i][j];
				GameObject* g2 = groups[i][k];

				String g1Type = g1->GetType();
				String g2Type = g2->GetType();

				if(g1Type == "Player" && g2Type == "Ball") {
					Ball* ball = (Ball*)g2;
					Player* player = (Player*)g1;

					PlayerCollision(*ball, *player);
				}
				else if(g2Type == "Player" && g1Type == "Ball") {
					Ball* ball = (Ball*)g1;
					Player* player = (Player*)g2;

					PlayerCollision(*ball, *player);
				}
				else if(g1Type == "Bomb" && g2Type == "Ball") {
					Ball* ball = (Ball*)g2;
					Bomb* bomb = (Bomb*)g1;

					BombCollision(gameObjects, *ball, *bomb, player1, player2);
				}
				else if(g2Type == "Bomb" && g1Type == "Ball") {
					Ball* ball = (Ball*)g1;
					Bomb* bomb = (Bomb*)g2;

					BombCollision(gameObjects, *ball, *bomb, player1, player2);
				}
				else if(g1Type == "Ball" && g2Type == "Ball") {
					Ball* ball1 = (Ball*)g1;
					Ball* ball2 = (Ball*)g2;

					BallCollision(*ball1, *ball2);
				}
			}
		}
	}
}

/* PlayerCollision */
void CollisionManager::PlayerCollision(Ball& ball, Player& player) {
	if(ball.boundingBox->CollidesWith(*player.boundingBox) && player.name != ball.GetCollidedWith()) {
		ball.SwitchDirection(player);
	}
}

/* BallCollision */
void CollisionManager::BallCollision(Ball& ball1, Ball& ball2) {
	if(ball1.boundingBox->CollidesWith(*ball2.boundingBox)) {
		//ball1.SwitchDirection(ball2);
		ball2.SwitchDirection(ball1);
	}
}

/* BombCollision */
void CollisionManager::BombCollision(std::vector<GameObject*>& gameObjects, Ball& ball, Bomb& bomb, Player& player1, Player& player2) {	
	if(ball.boundingBox->CollidesWith(*bomb.boundingBox)) {
		bomb.Explode(gameObjects, player1, player2);
	}
}

/* Draw */
void CollisionManager::Draw(std::vector<GameObject*> gameObjects) {
	RenderBoxes(gameObjects);
	quadTree->DrawTree();
	DrawBounds();
}

/* DrawBounds */
void CollisionManager::DrawBounds() {
	MeshManagerSingleton* meshManager = MeshManagerSingleton::GetInstance();
	meshManager->AddCubeToQueue(matrix4(IDENTITY) * glm::scale(boundsScale), MERED, MERENDER::WIRE);
}

/* RenderBoxes */
void CollisionManager::RenderBoxes(std::vector<GameObject*> gameObjects) {
	for(int i = 0; i < gameObjects.size(); i++) {
		GameObject* g = gameObjects[i];

		g->boundingBox->AddToRenderList();
	}
}