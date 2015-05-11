/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#include "GameObject.h"

/* Constructor */
GameObject::GameObject(String n, matrix4 pos, vector3 vel, float maxSp, float accel) {
	name = n;
	type = "GameObject";
	position = pos;
	velocity = vel;
	maxSpeed = maxSp;
	acceleration = accel;
	boundingBox = new BoundingBox(name, pos);

	meshManager = MeshManagerSingleton::GetInstance();
}

/* Destructor */
GameObject::~GameObject() {
	if(boundingBox != nullptr) {
		boundingBox = nullptr;
	}
}

/* GetName */
String GameObject::GetName() {
	return name;
}

/* GetType */
String GameObject::GetType() {
	return type;
}

/* IsActive */
bool GameObject::IsActive() {
	return isActive;
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

/* Update */
void GameObject::Update() {
	if(glm::length(velocity) > 0.0f) {
		Move();
	}
	boundingBox->SetPosition(position);
}

/* Draw */
void GameObject::Draw() {
	meshManager->SetModelMatrix(position, type);
	meshManager->AddInstanceToRenderList(type);
}