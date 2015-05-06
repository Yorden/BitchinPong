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

	/* Update */
	/* Updates CollisionManager */
	void Update(Player& player, Player& player2, Ball& ball1, Ball& ball2, std::vector<GameObject*> gameObjects, std::vector<Bomb*> bombs);

	/* Draw */
	/* Draws quad tree, gameobject bounding boxes, and the bounds of the arena */
	void Draw(std::vector<GameObject*> gameObjects);

	/* RenderBoxes */
	/* Draws cubes around models representing visualization of bounding box */
	void RenderBoxes(std::vector<GameObject*> gameObjects);

	/* IdentifyBox */
	/* Returns index of box specified by name, else -1 if the box doesn't exist */
	int IdentifyBox(String n);

	/* BallCollision */
	/* Detects if there is a collision between a players paddle and the ball */
	bool PlayerCollision(Player& player, Ball& ball);

	/* BallBallCollision */
	/* Detects if there is a collision between the two balls */
	bool BallBallCollision(Ball& ball1, Ball& ball2);

	/* BombCollision */
	/* Checks for collisions between the ball and bombs */
	//bool BombCollision(Ball& ball, std::vector<Bomb*>& bombs);
	bool BombCollision(Ball& ball, Bomb* bombs);

	/* DrawBounds */
	/* Draws square representing the bounds of the playing area */
	void DrawBounds();
};
#endif

