/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#include "Bomb.h"


Bomb::Bomb(String n, matrix4 pos):
	GameObject(n, pos, vector3(2.0f), 0.0f, 0.0f)
{
}

Bomb::~Bomb(void)
{
}

void Bomb::Init() {
	GameObject::Init();
	meshManager->LoadModelUnthreaded("Minecraft\\CubePrimitive.obj", name, position * glm::scale(vector3(3.0f)));
	boundingBox->GenerateBoundingBox();
	boundingBox->scale *= 3.0f;
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