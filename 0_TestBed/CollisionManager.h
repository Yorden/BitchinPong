#ifndef COLLISION_MANAGER
#define COLLISION_MANAGER

#include "ME\MyEngine.h";
#include "Player.h"
#include "Ball.h"
#include "Bomb.h"
#include "BoundingBox.h"

class CollisionManager
{
	static CollisionManager* instance;
	vector3 boundsScale;

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
	void Update(Player& player, Player& player2, Ball& ball, std::vector<GameObject*> gameObjects, std::vector<Bomb*> bombs);

	/* RenderBoxes */
	/* Draws cubes around models representing visualization of bounding box */
	void RenderBoxes(std::vector<GameObject*> gameObjects);

	/* IdentifyBox */
	/* Returns index of box specified by name, else -1 if the box doesn't exist */
	int IdentifyBox(String n);

	/* BallCollision */
	/* Detects if there is a collision between a players paddle and the ball */
	bool PlayerCollision(Player& player, Ball& ball);

	/* BombCollision */
	/* Checks for collisions between the ball and bombs */
	bool BombCollision(Ball& ball, std::vector<Bomb*>& bombs);

	/* DrawBounds */
	/* Draws square representing the bounds of the playing area */
	void DrawBounds();
};
#endif

