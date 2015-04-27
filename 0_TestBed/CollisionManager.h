#ifndef COLLISION_MANAGER
#define COLLISION_MANAGER

#include "ME\MyEngine.h";
#include "Player.h"
#include "Ball.h"
#include "BoundingBox.h"

class CollisionManager
{
	static CollisionManager* instance;

public:
	/* Constructor */
	CollisionManager();

	/* Destructor */
	~CollisionManager();

	/* GetInstance */
	/* Returns CollisionManager singleton */
	static CollisionManager* GetInstance();

	/* Update */
	/* Updates CollisionManager */
	void Update();

	/* RenderBoxes */
	/* Draws cubes around models representing visualization of bounding box */
	void RenderBoxes(std::vector<GameObject*> gameObjects);

	/* IdentifyBox */
	/* Returns index of box specified by name, else -1 if the box doesn't exist */
	int IdentifyBox(String n);

	/* BallCollision */
	/* Detects if there is a collision between a players paddle and the ball */
	bool BallCollision(GameObject& player1, /*GameObject& player2,*/ GameObject& ball);
};
#endif

