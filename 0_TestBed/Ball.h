/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#ifndef BALL
#define BALL

#include "ME\MyEngine.h"
#include "Player.h"

#include <stdlib.h>
#include <time.h>
#include <math.h>
class Ball : public GameObject
{
	Player* player1;
	Player* player2;
	String collidedWith;
	bool ballIsTemp;

public:
	/* Constructor */
	Ball(String ballName, matrix4 pos, vector3 vel, Player* p1, Player* p2, bool tempBall);
	
	/* Destructor */
	~Ball();

	/* GetCollidedWith */
	/* Returns string representing most recent paddle hit */
	String GetCollidedWith();

	/* SetCollidedWith */
	/* Sets string representing most recent paddle hit */
	void SetCollidedWith(String n);

	/* Update */
	/* Updates ball */
	void Update();

	/* Draw */
	/* Draws Ball */
	void Draw();

	/* Move */
	/* Moves ball */
	void Move() override;

	/* SwitchDirection */	
	/* Changes direction ball is moving when it collides with another GameObject */
	void SwitchDirection(GameObject& obj);

	/* InBounds */
	/* Checks to see if the ball is within the bounds of the arena */
	bool InBounds();

	void removeBall();
};
#endif

