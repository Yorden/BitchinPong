/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#include "GameObject.h"

/* Constructor */
GameObject::GameObject(String n, matrix4 pos, vector3 vel, float maxSp, float accel) {
	name = n;
	position = pos;
	velocity = vel;
	maxSpeed = maxSp;
	acceleration = accel;
}

/* Destructor */
GameObject::~GameObject() {
}

/* GetName */
String GameObject::GetName() {
	return name;
}

/* GetPosition */
matrix4 GameObject::GetPosition() {
	return position;
}

/* SetPosition */
void GameObject::SetPosition(matrix4 pos) {
	position = pos;
}

/* GetVelocity */
vector3 GameObject::GetVelocity() {
	return velocity;
}

/* GetAcceleration */
float GameObject::GetAcceleration() {
	return acceleration;
}

/* Init */
void GameObject::Init() {
	meshManager = MeshManagerSingleton::GetInstance();
	boundingBox = new BoundingBox(name, position);
}

/* Update */
void GameObject::Update() {
	if(glm::length(velocity) > 0.0f) {
		Move();
	}

	meshManager->SetModelMatrix(position, name);
	boundingBox->GenerateBoundingBox_Model();
	boundingBox->SetPosition(position);
}

/* Draw */
void GameObject::Draw() {
	meshManager->AddInstanceToRenderList(name);
}