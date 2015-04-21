/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#include "Player.h"

/* Constructor */
Player::Player(matrix4 pos, String n) {
	name = n;
	position = pos;
	acceleration = 0.0f;
	velocity = vector3(0.0f, 0.0f, 0.0f);
}

/* Destructor */
Player::~Player() {
}

/* GetName */
String Player::GetName() {
	return name;
}

/* GetPosition */
matrix4 Player::GetPosition() {
	return position;
}

/* SetPosition */
void Player::SetPosition(matrix4 pos) {
	position = pos;
}

/* GetAcceleration */
float Player::GetAcceleration() {
	return acceleration;
}

/* IncrementAcceleration */
void Player::IncrementAcceleration(float val) {
	acceleration += val;
}

/* Update */
void Player::Update() {
	if(acceleration >= 0.03f)
		acceleration = 0.03f;
	else if(acceleration <= -0.03f)
		acceleration = -0.03f;

	if(acceleration != 0) {
		position *= glm::translate(velocity);
		velocity.y = acceleration;
		acceleration *= 0.965f;
	}
}
