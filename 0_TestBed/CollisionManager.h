/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#ifndef COLLISION_MANAGER
#define COLLISION_MANAGER

#include "ME\MyEngine.h";
#include "GameObject.h"
#include "Player.h"
#include "Bomb.h"
#include "Ball.h"
#include "BoundingBox.h"
#include "QuadTree.h"

class CollisionManager
{
public:
	static CollisionManager* instance;
	QuadTree* quadTree;
	vector3 boundsScale;
	std::vector<std::vector<GameObject*>> groups;

	/* Constructor */
	CollisionManager();

	/* Destructor */
	~CollisionManager();

	/* GetInstance */
	/* Returns CollisionManager singleton */
	static CollisionManager* GetInstance();

	/* CheckCollisions */
	/* Checks for collisions between gameobjects in game */
	void CheckCollisions(std::vector<GameObject*>& gameObjects, Player& player1, Player& player2);


	/* PlayerCollisions */
	/* Handles logic for ball-player collisions */
	void PlayerCollision(Ball& ball, Player& player);

	/* BombCollisions */
	/* Handles logic for ball-bomb collisions */
	void BombCollision(std::vector<GameObject*>& gameObjects, Ball& ball, Bomb& bomb, Player& player1, Player& player2);

	/* BallCollisions */
	/* Handles logic for ball-ball collisions */
	void BallCollision(Ball& ball1, Ball& ball2);

	/* Draw */
	/* Draws quad tree, gameobject bounding boxes, and the bounds of the arena */
	void Draw(std::vector<GameObject*> gameObjects);

	/* DrawBounds */
	/* Draws square representing the bounds of the playing area */
	void DrawBounds();

	/* RenderBoxes */
	/* Draws cubes around models representing visualization of bounding box */
	void RenderBoxes(std::vector<GameObject*> gameObjects);
};
#endif

