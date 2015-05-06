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

/* GetBombs */
std::vector<Bomb*> BombSpawnManager::GetBombs() {
	return bombs;
}

/* SpawnBomb */
void BombSpawnManager::SpawnBomb(std::vector<GameObject*>& gameObjects) {
	String name = "Bomb" + std::to_string(bombs.size());

	float randX = (rand() % 38);
	randX -= 20;

	float randY = (rand() % 18);
	randY -= 10;
	
	Bomb* b = new Bomb(name, matrix4(IDENTITY) * glm::translate(vector3(randX, randY, 0.0f)));
	b->Init();

	bombs.push_back(b);
	gameObjects.push_back(b);
}

/* DrawBombs */
void BombSpawnManager::DrawBombs() {
	for(int i = 0; i < bombs.size(); i++) {
		bombs[i]->Draw();
	}
}