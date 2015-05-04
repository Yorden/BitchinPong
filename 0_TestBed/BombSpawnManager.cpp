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
	//float randX = (std::rand() % 7) - (std::rand() % 7);
	//float randY = (std::rand() % 3) - (std::rand() % 3);
	float randX = (rand() % 12);
	randX -= 6;

	float randY = (rand() % 4);
	randY -= 2;
	
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