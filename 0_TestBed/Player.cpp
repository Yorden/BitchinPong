/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#include "Player.h"

/* Constructor */
Player::Player(String n, matrix4 pos) : 
	GameObject(n, pos, vector3(0), 0.1f, 0.005f) {

		health = 100;
		totalHealth = 100;
}

/* Destructor */
Player::~Player() {
}

/* Init */
void Player::Init() {
	GameObject::Init();
	meshManager->LoadModelUnthreaded("Minecraft\\MC_Creeper.obj", name, position);
	boundingBox->GenerateBoundingBox_Model();
	position *= glm::translate(-boundingBox->GetScale()/2.0f);
	boundingBox->SetPosition(position);
}

/* GetPosition */
matrix4 Player::GetPosition() {
	return position * glm::translate(boundingBox->GetCentroid());
}

/* LoseHealth */
void Player::LoseHealth(float damage) {
	health -= damage;
}

/* Update */
void Player::Update() {
	GameObject::Update();
	InBounds();
}

/* Draw */
void Player::Draw() {
	GameObject::Draw();
	if(position[3].x < 0) DrawHealthBar(-18);
	if(position[3].x > 0) DrawHealthBar(18);
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
bool Player::InBounds() 
{
	float minY = position[3].y + boundingBox->GetCentroid().y - boundingBox->GetScale().y/2;
	float maxY = position[3].y + boundingBox->GetCentroid().y + boundingBox->GetScale().y/2;

	//2.0 -6
	if(maxY > 10) {
		position[3][1] = 10 - boundingBox->GetScale().y;
		return false;
	}
	else if(minY < -10) {
		position[3][1] = -10;
		return false;
	}

	return true;
}

/* DrawHealthBar */
void Player::DrawHealthBar(float xPos) {
	MeshManagerSingleton* meshManager = MeshManagerSingleton::GetInstance();

	meshManager->AddCubeToQueue(matrix4(IDENTITY) * glm::translate(vector3(xPos, 0.0f, 0.0f)) * glm::scale(vector3(1.0f, 20.0f * (health/totalHealth), 0.5f)), MEGREEN, MERENDER::SOLID);
}