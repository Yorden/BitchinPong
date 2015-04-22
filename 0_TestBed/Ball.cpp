#include "Ball.h"

/* Constructor */
Ball::Ball(){
	position = matrix4(IDENTITY);
	position = glm::scale(position, vector3(0.5f,0.5f,0.5f));
	velocity = vector3(0.05f, 0.0f, 0.0f);
}

/* Destructor */
Ball::~Ball() {
}

/* GetName */
String Ball::GetName() {
	return name;
}

/* GetPositon */
matrix4 Ball::GetPosition() {
	return position;
}

/* Update */
void Ball::Update() {
	isOutOfBoundsX();
	position *= glm::translate(velocity);
}

/* SwitchDirection */
void Ball::SwitchDirection() {
	velocity *= -1;
}
// checks if the ball went passed a player
void Ball::isOutOfBoundsX(){
	if(position[3][0] > 8 || position[3][0] < -8)
	{
		position[3][0] = 0;

	}

}