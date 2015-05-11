/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#include "GameManager.h"
#include <locale>
#include <codecvt>
#include <string>

/* Instance of the application */
GameManager* GameManager::instance = nullptr;

/* Constructor */
GameManager::GameManager() {
	//Initialize all the singletons to nullptrs
	systemSingleton = nullptr;
	window = nullptr;
	openGLSingleton = nullptr;
	lightManagerSingleton = nullptr;
}

/* Copy Constructor */
GameManager::GameManager(GameManager const& other){
}

/* Copy Assignment Operator */
GameManager& GameManager::operator = (GameManager const& other) {
	return *this; 
}

/* Destructor */
GameManager::~GameManager() {
	// Call the release method when the instance is destroyed
	Release();
	delete player1;
	delete player2;
	delete ball1;
}

/* GetInstance */
GameManager* GameManager::GetInstance( HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow) {
	// If the instance does not exist
	if(instance == nullptr)
	{
		// Create the instance
		instance = new GameManager( );
		// Initialize the instance
		instance->Init(hInstance, lpCmdLine, nCmdShow);
	}
	// Return the instance
	return instance;
}

void GameManager::ReleaseInstance() {
	// If the instance exists
	if(instance != nullptr)
	{
		// Delete the instance
		delete instance;
		// Make the pointer a nullptr reference
		instance = nullptr;
	}
}

void GameManager::Release() {
	SafeDelete(window);

	// Release all the singletons used in the dll
	ReleaseAllSingletons();
}

void GameManager::Run () {
	//Run the main loop until the exit message is sent
	MSG msg = {0};
	while( WM_QUIT != msg.message )
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			ProcessKeyboard();
			Update();
			Display();
		}
	}
}

/* Update */
void GameManager::Update () {
	systemSingleton->UpdateTime();

	//The core of the gameplay will only execute if both players have a health greater than 0
	if(player1->health > 0 && player2->health > 0)
	{
		CleanUp();

		bombSpawnManager->RandSpawn(gameObjects);

		// Update all current GameObjects
		for(int i = 0; i < gameObjects.size(); i++) {
			gameObjects[i]->Update();
		}

		// Check for collisions
		collisionManager->CheckCollisions(gameObjects, *player1, *player2);
	
		//Update the mesh information
		meshManagerSingleton->Update();
	}
	//Otherwise, the game will stop playinjg (most functions will stop executing) and the camera will move into a different position
	//If Player 1 is defeated
	else if(player1->health <= 0)
	{
		cameraSingleton->SetPosition(vector3(-50.0f, 0.0f, 20.0f));
	}
	//If Player 2 is defeated
	else if(player2->health <= 0)
	{
		cameraSingleton->SetPosition(vector3(50.0f, 0.0f, 20.0f));
	}
}

/* Display */
void GameManager::Display (void) {
	// Clear the window
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Draw all current GameObjects
	for(int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->Draw();
	}

	// Draw collision data
	//collisionManager->Draw(gameObjects);

	// Draw Battle Arena
	meshManagerSingleton->AddInstanceToRenderList("BattleArena");

	// Render everything
	meshManagerSingleton->Render();

	//Swaps the OpenGL buffers
	openGLSingleton->GLSwapBuffers();
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	//Callbacks for winapp 
    switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

/* Init */
void GameManager::Init( HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow) {
	// Initialize singletons
	systemSingleton = SystemSingleton::GetInstance();
	cameraSingleton = CameraSingleton::GetInstance();
	collisionManager  = CollisionManager::GetInstance();
	openGLSingleton = GLSystemSingleton::GetInstance();
	lightManagerSingleton = LightManagerSingleton::GetInstance();
	bombSpawnManager = BombSpawnManager::GetInstance();

	// Create a new window and set its properties
	window = new WindowClass( hInstance, nCmdShow, WndProc);
	window->SetFullscreen(systemSingleton->IsWindowFullscreen());
	window->SetBorderless(systemSingleton->IsWindowBorderless());
	systemSingleton->WindowName = "Bitchin' Pong";
	systemSingleton->WindowWidth = 1280;
	systemSingleton->WindowHeight = 720;
	systemSingleton->WindowFullscreen = false;
	systemSingleton->WindowBorderless = false;
	windowColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);

	// Make the Window name a wide string
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wide = converter.from_bytes( systemSingleton->WindowName);
	window->CreateMEWindow(wide.c_str(), systemSingleton->WindowWidth, systemSingleton->WindowHeight);

	// Set OPENGL 3.x Context
	systemSingleton->m_RenderingContext = OPENGL3X;
	openGLSingleton->InitGLDevice(window->GetHandler());

	// Verify what is the OpenGL rendering context and save it to system (3.x might fail, in which case exit)
	if(openGLSingleton->IsNewOpenGLRunning() == false)
		exit(0);
	
	// Set camera position/orientation
	cameraSingleton->SetPosition(vector3(0.0f, -25.0f, 20.0f));
	cameraSingleton->Rotate(-0.8f, 0.0f);

	// Set the properties for the light in the scene
	lightManagerSingleton->SetPosition( glm::vec3( 0, 0, 10) );
	lightManagerSingleton->SetColor( glm::vec3( 1, 1, 1) );
	lightManagerSingleton->SetIntensity ( 5.0f ); //Rotating Light
	lightManagerSingleton->SetIntensity ( 0.75f, 0 ); //Ambient light (Ambient Light is always the first light, or light[0])
	

	meshManagerSingleton = MeshManagerSingleton::GetInstance();

	// Load models 
	LoadModels();

	// Initialize GameObjects
	InitGameObjects();

	//Start the clock
	systemSingleton->StartClock();

	printf("\n");
}

/* InitGameObjects */
void GameManager::InitGameObjects() {
	player1 = new Player("Player1", glm::translate(vector3(-16.0f, 0.0f, 0.0f)));
	player2 = new Player("Player2", glm::translate(vector3(16.0f, 0.0f, 0.0f)));
	ball1 = new Ball("MainBall", matrix4(IDENTITY), vector3(0.2f, 0, 0), player1, player2);

	gameObjects.push_back(player1);
	gameObjects.push_back(player2);
	gameObjects.push_back(ball1);

	bombSpawnManager->SpawnBombs(gameObjects, 60);
}

/* LoadModels */
void GameManager::LoadModels() {
	meshManagerSingleton->LoadModelUnthreaded("BattleArena.obj", "BattleArena", 
												glm::rotate(matrix4(IDENTITY), 90.0f, vector3(1.0f, 0, 0)) * 
												glm::rotate(matrix4(IDENTITY), 90.0f, vector3(0, 1.0f, 0)) * 
												glm::translate(vector3(0, -2.0f, 0)) * 
												glm::scale(vector3(1.45f, 1.0f, 1.75f)));

	meshManagerSingleton->LoadModelUnthreaded("Player.obj", "Player");
	meshManagerSingleton->LoadModelUnthreaded("Ball.obj", "Ball");
	meshManagerSingleton->LoadModelUnthreaded("Bomb.obj", "Bomb");
}

/* CleanUp */
void GameManager::CleanUp() {
	int arrSize = gameObjects.size();
	std::vector<GameObject*> stillActive;

	for(int i = 0; i < arrSize; i++) {
		if(gameObjects[i]->IsActive()) {
			stillActive.push_back(gameObjects[i]);
		}
	}

	gameObjects = stillActive;
}
