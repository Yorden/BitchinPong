/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#include "InputManager.h"

InputManager* InputManager::instance = nullptr;

/* Constructor */
InputManager::InputManager() {
}

/* Copy Constructor */
InputManager::InputManager(InputManager const& other) {
}

/* Copy Assignment Operator */
InputManager& InputManager::operator = (InputManager const& other) {
	return *this;
}

/* Destructor */
InputManager::~InputManager() {
	if(instance != nullptr)
		instance = nullptr;
}


