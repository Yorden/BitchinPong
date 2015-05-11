/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#include "Bomb.h"
#include "Ball.h";

/* Constructor */
Bomb::Bomb(String n, matrix4 pos):
	GameObject(n, pos, vector3(2.0f), 0.0f, 0.0f) {

		type = "Bomb";
		boundingBox->GenerateBoundingBox_Model(type);
}

/* Destructor */
Bomb::~Bomb(void){
	GameObject::~GameObject();
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
}

/* Explode */
void Bomb::Explode(std::vector<GameObject*>& gameObjects, Player& player1, Player& player2, Ball& ball) {
	float x;
	float y;

	for(int i = -1; i < 2; i++) {
		x = ball.GetVelocity().x + cosf(PI / 8 * i) * 0.05f;
		y = ball.GetVelocity().y + sinf(PI / 8 * i) * 0.05f;

		Ball* b = new Ball("Ball_" + std::to_string(gameObjects.size()), position, vector3(x, y, 0), &player1, &player2);

		gameObjects.push_back(b);
	}

	for(int i = 0; i < gameObjects.size(); i++) {
		if(gameObjects[i]->GetName() == name) {
			gameObjects.erase(gameObjects.begin() + i);
			break;
		}
	}
}

/* InBounds */
bool Bomb::InBounds(){
	return true;
}
