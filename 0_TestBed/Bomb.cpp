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
	meshManager->LoadModelUnthreaded("Minecraft\\Bomb.obj", name, position);
	meshManager->SetModelMatrix(position * glm::scale(vector3(0.5f)), name);
	boundingBox->GenerateBoundingBox_Model();
	boundingBox->scale *= 0.5f;
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