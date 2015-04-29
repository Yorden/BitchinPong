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
class Ball : public GameObject
{
public:
	/* Constructor */
	Ball(String ballName, matrix4 pos, vector3 vel);
	
	/* Destructor */
	~Ball();

	/* Init */
	/* Initializes Ball */
	void Init();

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
	void SwitchDirection(GameObject& ball,  GameObject& collis);

	//The function to handle balls running into one another
	void ballOnBallCollision(GameObject& thisBall, GameObject& otherBall);

	/* Switches ball direction when it hits a paddle/wall */
	bool InBounds();

	vector3 getCenterPoint(String targetMatName);
};
#endif

