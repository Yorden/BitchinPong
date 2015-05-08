/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#include "Ball.h"

/* Constructor */
Ball::Ball(String ballName, matrix4 pos, vector3 vel, Player* p1, Player* p2) :
	GameObject(ballName, pos, vel, 0.5f, 0.5f) {
		type = "Ball";

		player1 = p1;
		player2 = p2;
		collidedWith = "";

		boundingBox->GenerateBoundingBox_Model(type);
}

/* Destructor */
Ball::~Ball() {
	GameObject::~GameObject();
}

/* GetCollidedWith */
String Ball::GetCollidedWith() {
	return collidedWith;
}

/* SetCollidedWith */
void Ball::SetCollidedWith(String n) {
	collidedWith = n;
}

/* Update */
void Ball::Update() {
	GameObject::Update();
	InBounds();
}

/* Draw */
void Ball::Draw() {
	GameObject::Draw();
}

/* Move */
void Ball::Move() {
	position *= glm::translate(velocity);
}

/* SwitchDirection */
void Ball::SwitchDirection(GameObject& obj)
{
	collidedWith = obj.GetName();

	//Setting the velocity's x value to negative one, reversing it
	velocity.x *= -1;

	//Calculating the center points for both the ball and collision target in the global positioning
	float ballY = position[3].y;
	float objY = obj.position[3].y;

	//The difference between the two points is calculated as the velocity's y value
	velocity.y = -(objY - ballY)/10;
	glm::normalize(velocity);
	velocity.x *= 0.4f/abs(velocity.x);

	if(velocity.y > maxSpeed) {
		velocity.y = maxSpeed;
	}
}

/* InBounds */
bool Ball::InBounds(){
	// If the player is out of bounds...
	if(position[3][0] > 18 || position[3][0] < -18) {
		// So we can hit either paddle regardless of direction
		collidedWith = "";

		// Find out which player to hurt
		if(position[3].x < 0) player1->LoseHealth(5);
		else player2->LoseHealth(5);

		// Random position to spawn to
		float randSpawnX = (rand() % 3) - (rand() % 3);
		float randSpawnY = (rand() % 6) - (rand() % 6);
		// Random float 0 and 360 used to determine direction of ball
		float randDirection = ((rand() % 45) - (rand() % 45)) * (rand() - rand());

		position[3].x = randSpawnX;
		position[3].y = randSpawnY;

		velocity = vector3(cos(randDirection * PI/180), sin(randDirection * PI/180), 0.0f);
		glm::normalize(velocity);
		velocity *= .5f;
		return true;
	}

	//Y Value: Will bounce by reversing y value of the velocity
	if(position[3][1] > 10.0f || position[3][1] < -10.0f) {
		velocity.y *= -1;
		return true;
	}

	return false;
}
