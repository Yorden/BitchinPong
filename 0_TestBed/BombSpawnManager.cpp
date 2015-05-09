#include "BombSpawnManager.h"

/* Declare Singleton*/
BombSpawnManager* BombSpawnManager::instance = nullptr;

/* Constructor */
BombSpawnManager::BombSpawnManager() {
	std::srand(time(NULL));
}

/* Destructor */
BombSpawnManager::~BombSpawnManager() {
}

/* GetInstance */
BombSpawnManager* BombSpawnManager::GetInstance() {
	if(instance == nullptr) {
		instance = new BombSpawnManager();
	}

	return instance;
}

/* SpawnBombs */
void BombSpawnManager::SpawnBombs(std::vector<GameObject*>& gameObjects, int num) {
	for(int i = 0; i < num; i++) {
		SpawnBomb(gameObjects);
	}
}

/* SpawnBomb */
void BombSpawnManager::SpawnBomb(std::vector<GameObject*>& gameObjects) {
	String name = "Bomb" + std::to_string(gameObjects.size());
	float randX = (rand() % 16) - (rand() % 16);
	float randY = (rand() % 9) - (rand() % 9);
	
	Bomb* b = new Bomb("Bomb_" + std::to_string(std::rand() % 1000), matrix4(IDENTITY) * glm::translate(vector3(randX, randY, 0.0f)));

	gameObjects.push_back(b);
}