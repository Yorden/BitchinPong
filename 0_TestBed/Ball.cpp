#include "Ball.h"

/* Constructor */
Ball::Ball(){
	position = matrix4(IDENTITY);
	position = glm::scale(position, vector3(0.5f,0.5f,0.5f));
	velocity = vector3(0.05f, 0.0f, 0.0f);
}

/* Destructor */
Ball::~Ball() {
}

/* GetName */
String Ball::GetName() {
	return name;
}

/* GetPositon */
matrix4 Ball::GetPosition() {
	return position;
}

/* Update */
void Ball::Update() {
	isOutOfBounds();
	position *= glm::translate(velocity);
}

/* SwitchDirection */
void Ball::SwitchDirection(String ballName, String collisName) {
	//Setting the velocity's x value to negative one, reversing it
	velocity.x *= -1;

	//Calculating the center points for both the ball and collision target
	vector3 ballCenter = getCenterPoint(ballName);
	vector3 collisCenter = getCenterPoint(collisName);

	//Setting the y value of the velocity to the difference between the collision's center point and the ball's center point
	velocity.y = (collisCenter.y - ballCenter.y)/15.0f;
}

// checks if the ball went passed a player
void Ball::isOutOfBounds(){
	//X Value: Will move back into center position 
	if(position[3][0] > 8 || position[3][0] < -8)
	{
		position[3][0] = 0;
		position[3][1] = 0;

	}

	//Y Value: Will bounce by reversing y value of the velocity
	if(position[3][1] > 4 || position[3][1] < -4)
	{
		velocity.y *= -1;

	}
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
