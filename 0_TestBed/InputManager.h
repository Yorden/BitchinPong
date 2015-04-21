/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include "GameManager.h"

class InputManager
{
	static InputManager* instance;

public:
	/* Constructor */
	InputManager(void);

	/* Copy Constructor */
	InputManager(InputManager const& other);

	/* Copy Assignment Operator */
	InputManager& operator = (InputManager const& other);

	/* Destructor */
	~InputManager(void);
};
#endif

