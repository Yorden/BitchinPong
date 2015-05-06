/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "ME\MyEngine.h"
#include "BoundingBox.h"

class GameObject
{
public:
	/* Variables */
	String name; // Used to identify instance in mesh/collision managers
	matrix4 position; // Gameobject global position
	vector3 velocity; // Current velocity
	float acceleration; // Current acceleration
	float maxSpeed; // Maximum speed
	BoundingBox* boundingBox; // BoundingBox pointer
	MeshManagerSingleton* meshManager; // MeshManager singleton

	/* Constructor */
	GameObject(String n, matrix4 pos, vector3 vel, float maxSp, float accel);

	/* Destructor */
	~GameObject();

	/* GetName */
	/* Returns string used to identify instance of GameObject in mesh/collision managers */
	String GetName();

	/* GetPosition */
	/* Returns position of GameObject in global space */
	virtual matrix4 GetPosition();

	/* SetPosition */
	/* Sets position of GameObject in global space */
	void SetPosition(matrix4 pos);

	/* GetVelocity */
	/* returns the current velocity of the GameObject */
	vector3 GetVelocity();

	/* GetAcceleration */
	/* Returns current acceleration of the GameObject */
	float GetAcceleration();

	/* Init */
	/* Initializes GameObject */
	virtual void Init();

	/* Update */
	/* Updates GameObject */
	virtual void Update();

	/* Draw */
	/* Draw GameObject */
	virtual void Draw();

	/* Move */
	/* Moves GameObject in specified direction */
	virtual void Move() = 0;

	/* InBounds */
	/* Checks whether or not the object is in bounds */
	virtual bool InBounds() = 0;
};
#endif

