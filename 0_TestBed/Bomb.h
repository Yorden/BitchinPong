/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#ifndef BOMB
#define BOMB

#include "ME\MyEngine.h"
#include "Player.h"
#include "Ball.h"

class Bomb : public GameObject
{
public:
	/*Constructor*/
	Bomb(String n, matrix4 pos);

	/* Destructor */
	~Bomb(void);

	/* Update */
	/* Updates ball */
	void Update();

	/* Draw */
	/* Draws Ball */
	void Draw();

	/* Move */
	/* Moves ball */
	void Move() override;

	/* Explode */
	void Explode(std::vector<GameObject*>& gameObjects, Player& player1, Player& player2);

	/* InBounds */
	/* Checks to see if the bomb is within the bounds of the screen */
	bool InBounds();
};
#endif

