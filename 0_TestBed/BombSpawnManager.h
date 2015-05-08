/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#ifndef BOMB_SPAWN_MANAGER
#define BOMB_SPAWN_MANAGER

#include "ME\MyEngine.h"
#include "Bomb.h"
#include <random>
#include <time.h>

class BombSpawnManager
{
	static BombSpawnManager* instance;
	float spawnTimer;

public:
	/* Constructor */
	BombSpawnManager();

	/* Destructor */
	~BombSpawnManager();

	/* GetInstance */
	/* Returns singleton */
	static BombSpawnManager* GetInstance();

	/* SpawnBombs */
	/* Adds specified number of bombs to gameObjects list */
	void SpawnBombs(std::vector<GameObject*>& gameObjects, int num);

	/* SpawnBomb */
	/* Adds bomb to play field */
	void SpawnBomb(std::vector<GameObject*>& gameObjects);
};
#endif

