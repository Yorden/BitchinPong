/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#include "Ball.h"

/* Constructor */
Ball::Ball(String ballName, matrix4 pos, vector3 vel, Player* p1, Player* p2) :
	GameObject(ballName, pos, vel, 0.5, 0.1) {

		player1 = p1;
		player2 = p2;
}

/* Destructor */
Ball::~Ball() {
}

/* Init */
void Ball::Init() {
	GameObject::Init();
	meshManager->LoadModelUnthreaded("Minecraft\\Ball.obj", name, position);
	boundingBox->GenerateBoundingBox_Model();
}

/* Update */
void Ball::Update() {
	GameObject::Update();
	InBounds();
	meshManager->SetModelMatrix(position, name);
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
void Ball::SwitchDirection(GameObject& ball, GameObject& collis)
{
	//Setting the velocity's x value to negative one, reversing it
	velocity.x *= -1;
	
	//Calculating the center points for both the ball and collision target in the global positioning
	vector3 ballCenter = vector3(meshManager->GetModelMatrix(ball.GetName()) * vector4(getCenterPoint(ball.GetName()), 1.0f));
	vector3 collisCenter = vector3(meshManager->GetModelMatrix(collis.GetName()) * vector4(getCenterPoint(collis.GetName()), 1.0f));

	//The difference between the two points is calculated as the velocity's y value
	velocity.y = (ballCenter.y - collisCenter.y)/5.0f;

	//Capping the y velocity of the ball
	if(velocity.y > 0.05)
	{
		velocity.y = 0.05;
	}
	else if(velocity.y < -0.05)
	{
		velocity.y = -0.05;
	}
}

//A function to handle balls interacting with other balls
void Ball::ballOnBallCollision(GameObject& thisBall, GameObject& otherBall)
{
	//Getting the center of the balls as above
	vector3 thisBallCenter = vector3(meshManager->GetModelMatrix(thisBall.GetName()) * vector4(getCenterPoint(thisBall.GetName()), 1.0f));
	vector3 otherBallCenter = vector3(meshManager->GetModelMatrix(otherBall.GetName()) * vector4(getCenterPoint(otherBall.GetName()), 1.0f));

	//If the balls have a difference of y values that is greater than the difference between x values, the balls will change y values
	if((thisBallCenter.y - otherBallCenter.y) > (thisBallCenter.x - otherBallCenter.x))
	{
		velocity.y *= -1;
	}
	//Otherwise, they will negate their x values
	else
	{
		velocity.x *= -1;
	}
}

// checks if the ball went passed a player
bool Ball::InBounds(){
	//Getting a random number between 0 and 1. This will be used to determine if the balls will go left or right
	float randXDirect = (rand() % 2);
	
	//Another random value will determine the y angle of the ball 
	float randYDirect = (rand() % 95 + 5);
	//The random number is subtracted by 50, meaning it will either be in the positive range or a negative value
	randYDirect -= 50;
	//The numebr is divided by a large number to bring it into the proper range
	randYDirect /= 1000;	


	float randSpawnX = (rand() % 12);
	randSpawnX -= 6;

	float randSpawnY = (rand() % 6);
	randSpawnY -= 3;

	//X Value: Will move back into center position 
	if(position[3][0] > 18 || position[3][0] < -18) {
		if(position[3].x < 0) player1->LoseHealth(5);
		else player2->LoseHealth(5);

		if(randXDirect == 0)
		{
			velocity = vector3(0.05,randYDirect,0);
		}
		else 
		{
			velocity = vector3(-0.05,randYDirect,0);
		}
		position[3][0] = randSpawnX;
		position[3][1] = randSpawnY;
		return true;
	}

	//Y Value: Will bounce by reversing y value of the velocity
	if(position[3][1] > 10.0f || position[3][1] < -10.0f) {
		velocity.y *= -1;
		return true;
	}

	return false;
}

//The function to calculate the center point of a specific matrix (used in the switch direction function
vector3 Ball::getCenterPoint(String targetMatName){
	//The functionality is the same as in the BoundingBox class
	//Getting the proper matrix  and setting up vector3s for the centroid and max/min vertex values
	MeshManagerSingleton* meshManager = MeshManagerSingleton::GetInstance();
	std::vector<vector3> vertices = meshManager->GetVertices(targetMatName);
	vector3 centroid;
	vector3 minVertices;
	vector3 maxVertices;
	//Calculating the maximum and minimum values
	for(int i = 0; i < vertices.size(); i++) {
		vector2 vertex = vector2(vertices[i].x, vertices[i].y);

		if(vertex.x < minVertices.x)
			minVertices.x = vertex.x;
		else if(vertex.x > maxVertices.x)
			maxVertices.x = vertex.x;

		if(vertex.y < minVertices.y)
			minVertices.y = vertex.y;
		else if(vertex.y > maxVertices.y)
			maxVertices.y = vertex.y;

		//Getting the centroid to be returned below
		centroid = (minVertices + maxVertices) / 2.0f;
	}
	return centroid;
}
