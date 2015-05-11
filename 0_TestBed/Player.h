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
	float totalHealth;

	/* Constructor */
	Player(String n, matrix4 pos);

	/* Destructor */
	~Player();

	/* LoseHealth */
	/* Decrements players health */
	void LoseHealth(float damage);

	/* Update */
	/* Updates Player */
	void Update();

	/* Draw */
	/* Draws Player */
	void Draw() override;

	/* Move */
	/* Moves player in specified direction */
	void Move() override;

	/* MovePlayer */
	/* Moves player according to user input */
	void MovePlayer(int dir);

	/* InBounds */
	/* Checks to see if Player is in bounds */
	bool InBounds();

	/* DrawHealthBar */
	/* Draw players health bar to screen */
	void DrawHealthBar(float xPos);
public:
	float health;
};
#endif

