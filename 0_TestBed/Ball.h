#ifndef BALL
#define BALL

#include "ME\MyEngine.h"
#include "Player.h"
class Ball
{
	String name;
	matrix4 position;
	vector3 velocity;
	float acceleration;

public:
	/* Constructor */
	Ball();
	
	/* Destructor */
	~Ball(void);

	/* GetName */
	/* Returns ball name used for identification */
	String GetName();

	/* GetPosition */
	/* Returns ball position in global space */
	matrix4 GetPosition();

	/* Update */
	/* Updates ball */
	void Update();

	/* SwitchDirection */
	/* Switches ball direction when it hits a paddle/wall */
	void SwitchDirection(String ballName, String collisName);

	void isOutOfBounds();

	vector3 getCenterPoint(String targetMatName);
};
#endif

