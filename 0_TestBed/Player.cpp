/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#include "Player.h"

/* Constructor */
Player::Player(String n, matrix4 pos) : 
	GameObject(n, pos, vector3(0), 0.05f, 0.005f) {
}

/* Destructor */
Player::~Player() {
}

/* Update */
void Player::Update() {
	GameObject::Update();
}

/* Move */
void Player::Move() {
	position *= glm::translate(velocity);
	velocity *= 0.95f;
}

/* MovePlayer */
void Player::MovePlayer(int dir) {
	if(velocity.y < maxSpeed && velocity.y > -maxSpeed)
		velocity.y +=  acceleration * dir;
}

/* InBounds */
bool Player::InBounds() {

	return true;
}
