/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#include "Bomb.h"


Bomb::Bomb(matrix4 pos):
	GameObject("Bomb", pos, vector3(0,0,0), 0.0f, 0.0f)
{
}

Bomb::~Bomb(void)
{
}

void Bomb::Init() {
	GameObject::Init();
	meshManager->LoadModelUnthreaded("Minecraft\\CubePrimitive.obj", name, position);
	boundingBox->GenerateBoundingBox();
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

bool Bomb::isActive(){
	return true;
}

bool Bomb::InBounds(){
	return true;
}