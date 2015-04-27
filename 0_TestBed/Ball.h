/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#ifndef BALL
#define BALL

#include "ME\MyEngine.h"
#include "Player.h"

class Ball : public GameObject
{

public:
	/* Constructor */
	Ball(matrix4 pos, vector3 vel);
	
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
	/* Switches ball direction when it hits a paddle/wall */
	void SwitchDirection(String collisName);

	bool InBounds();

	vector3 getCenterPoint(String targetMatName);
};
#endif

