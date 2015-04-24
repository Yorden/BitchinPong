/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#ifndef PLAYER
#define PLAYER

#include "GameObject.h"

class Player : public GameObject
{
public:
	/* Constructor */
	Player(String n, matrix4 pos);

	/* Destructor */
	~Player();

	/* Update */
	/* Updates Player */
	void Update();

	/* Move */
	/* Moves player in specified direction */
	void Move() override;

	/* MovePlayer */
	/* Moves player according to user input */
	void MovePlayer(int dir);

	/* InBounds */
	/* Checks to see if Player is in bounds */
	bool InBounds();
};
#endif

