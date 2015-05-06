/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#include "Bomb.h"
#include "Ball.h";

Bomb::Bomb(String n, matrix4 pos):
	GameObject(n, pos, vector3(2.0f), 0.0f, 0.0f)
{
}

Bomb::~Bomb(void)
{
}

void Bomb::Init() {
	GameObject::Init();
	meshManager->LoadModelUnthreaded("Minecraft\\Bomb.obj", name, position);
	boundingBox->GenerateBoundingBox_Model();
}

/* Update */
void Bomb::Update() {
	GameObject::Update();
	InBounds();
}

/* Draw */
void Bomb::Draw() {
	GameObject::Draw();
}

/* Move */
void Bomb::Move() {
	position *= glm::translate(velocity);
}
/* isActive */
bool Bomb::isActive(){
	return true;
}
/* InBounds */
bool Bomb::InBounds(){
	return true;
}
/*Explode*/
void Bomb::Explode(std::vector<Ball*> ballList, Player* player1, Player* player2){
	//ball1 = new Ball("Ball1", matrix4(IDENTITY), vector3(0.05, 0, 0), player1, player2);
	for(int i = 0; i < 8; i++)
	{
		//gets theh x and the y direction
		float xdirection = position[0][3] +glm::cos((2*PI/8)*i);
		float ydirection = position[0][2] +glm::sin((2*PI/8)*i);
		//creates a new ball moving in that direction
		Ball* b = new Ball("Ball", matrix4(IDENTITY), vector3(xdirection, ydirection, 0), player1, player2);
		ballList.push_back(b);
	}
}
