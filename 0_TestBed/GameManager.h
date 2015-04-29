/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#ifndef GAME_MANAGER
#define GAME_MANAGER

#include "ME\MyEngine.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Ball.h"
#include "BombSpawnManager.h"
#include <SFML\Graphics.hpp>
#include <chrono>

using namespace MyEngine; // So we can access classes in dll

class GameManager
{
	bool m_bFPC;// First Person Camera flag
	bool m_bArcBall;// Arcball flag
	vector4 windowColor;

	// Game variables
	std::vector<GameObject*> gameObjects;
	Player* player1;
	Player* player2;
	Ball* ball1;
	Ball* ball2;

	// Singletons
	static GameManager* instance; // GameManager singleton
	SystemSingleton* systemSingleton; // System singleton
	CameraSingleton* cameraSingleton; // Camera singleton
	CollisionManager* collisionManager; // Collision manager singleton
	GLSystemSingleton* openGLSingleton; // OpenGL singleton for rendering context
	LightManagerSingleton* lightManagerSingleton; // Light manager singleton
	MeshManagerSingleton* meshManagerSingleton; // Mesh manager singleton
	BombSpawnManager* bombSpawnManager; // Bomb manager singleton
	GridClass* grid; // Grid that represents coordinate system
	WindowClass* window; // Window class

public:
	/* Get Instance*/
	/* Access class singleton */
	static GameManager* GetInstance(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow);

	/* Release Instance */
	/* Destroys class singleton */
	static void ReleaseInstance();

	/* Run */
	/* Run main game loop */
	void Run();

private:
	/* Constructor */
	GameManager();
	/* Copy Constructor */
	GameManager(GameManager const& other);
	/* Copy Assignment Operator */
	GameManager& operator = (GameManager const& other);
	/* Destructor */
	~GameManager();

	/* Update */
	/* Updates game*/
	void Update();

	/* Display */
	/* Displays game */
	void Display();

	/* Idle */
	/* Runs faster than update */
	void Idle();

	/* InitAppSystem */
	/* Initialize MyEngine variables */
	void InitMyEngine();

	/* InitGameObjects */
	/* Initializes GameObjects */
	void InitGameObjects();

	/* InitAppVariables */
	/* Initializes this applications internal variables */
	void InitInternalAppVariables();
	
	/* Init */
	/* Initializes the MyEngine window and rendering context */
	void Init( HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow);

	/* Release */
	/* Releases the application */
	void Release();

	/* ProcessKeyboard */
	/* Process user keyboard input */
	void ProcessKeyboard();

	/* ProcessMouse */
	/*  Process user mouse input */
	void ProcessMouse();

	/* ArcBall */
	/* Process the arcball of the scene, rotating an object in the center of it a_fSensitivity is a factor of change */
	void ArcBall(float a_fSensitivity = 0.1f);

	/* CameraRotation */
	/* Manages the rotation of the camera a_fSpeed is a factor of change */
	void CameraRotation(float a_fSpeed = 0.001f);

	void ReadConfig();

	void WriteConfig();
};

#endif

