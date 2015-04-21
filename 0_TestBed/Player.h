/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#ifndef PLAYER
#define PLAYER

#include "ME\MyEngine.h"

class Player
{
	String name;
	matrix4 position;
	vector3 velocity;
	float acceleration;

public:
	/* Constructor */
	Player(matrix4 pos, String n);
	/* Destructor */
	~Player();

	/* GetName */
	/* Returns name */
	String GetName();

	/* GetPosition */
	/* Returns matrix representing player in global space */
	matrix4 GetPosition();

	/* SetPosition */
	/* Sets player position in global space */
	void SetPosition(matrix4 pos);

	/* GetAcceleration */
	/* Returns players current acceleration */
	float GetAcceleration();

	/* IncrementAcceleration */
	/* Increases/reduces acceleration */
	void IncrementAcceleration(float val);

	/* Update */
	/* Updates player */
	void Update();
};
#endif

