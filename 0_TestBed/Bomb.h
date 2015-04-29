/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#ifndef BOMB
#define BOMB

#include "ME\MyEngine.h"
#include "Player.h"

class Bomb : public GameObject
{
public:
	/*Constructor*/
	Bomb(String n, matrix4 pos);

	/* Destructor */
	~Bomb(void);

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

	/* isActive */
	/* Checks to see if the ball hit the bomb */
	bool isActive();

	bool InBounds();

	vector3 getCenterPoint(String targetMatName);
};
#endif

