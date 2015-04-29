#ifndef BOMB_SPAWN_MANAGER
#define BOMB_SPAWN_MANAGER

#include "ME\MyEngine.h"
#include "Bomb.h"
#include <random>
#include <time.h>

class BombSpawnManager
{
	static BombSpawnManager* instance;

public:
	std::vector<Bomb*> bombs;
	float spawnTimer;

	/* Constructor */
	BombSpawnManager();

	/* Destructor */
	~BombSpawnManager();

	/* GetInstance */
	/* Returns singleton */
	static BombSpawnManager* GetInstance();

	/* GetBombs */
	/* Returns array containing bombs on screen */
	std::vector<Bomb*> GetBombs();

	/* SpawnBomb */
	/* Adds bomb to play field */
	void SpawnBomb(std::vector<GameObject*>& gameObjects);
	
	/* DrawBombs */
	/* Draws bombs to screen */
	void DrawBombs();
};
#endif

