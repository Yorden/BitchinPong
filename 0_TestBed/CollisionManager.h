#ifndef COLLISION_MANAGER
#define COLLISION_MANAGER

#include "ME\MyEngine.h";
#include "Player.h"
#include "Ball.h"
#include "BoundingBox.h"

class CollisionManager
{
	static CollisionManager* instance;
	std::vector<BoundingBox*> boundingBoxes;
	std::vector<matrix4> boundingBoxMatrices;

public:
	/* Constructor */
	CollisionManager();

	/* Destructor */
	~CollisionManager();

	/* GetInstance */
	/* Returns CollisionManager singleton */
	static CollisionManager* GetInstance();

	/* GenerateBoundingBox */
	/* Creates bounding box around specified model */
	void GenerateBoundingBox(String name);

	/* GenerateCollisionBoxes */
	/* Generates bounding boxes around players */
	void GenerateBoundingBoxes(matrix4 p1, matrix4 p2, matrix4 b);

	/* RenderBoxes */
	/* Draws cubes around models representing visualization of bounding box */
	void RenderBoxes(matrix4 p1, matrix4 p2, matrix4 b);

	/* GetBox */
	/* Returns rectangle from collisionBoxes list at specified index */
	BoundingBox* GetBox(String name);

	/* IdentifyBox */
	/* Returns index of box specified by name, else -1 if the box doesn't exist */
	int IdentifyBox(String n);

	/* PlayersInBounds */
	/* Checks to see if player is in bounds and still on screen */
	matrix4 PlayerInBounds(matrix4 p, String name);

	/* BallCollision */
	/* Detects if there is a collision between a players paddle and the ball */
	bool BallCollision(Player& p1, /*Player& p2,*/ Ball& b);
};
#endif

