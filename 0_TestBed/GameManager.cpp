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
	collisionManager  = CollisionManager::GetInstance();
	bombSpawnManager = BombSpawnManager::GetInstance();

	player1 = new Player("Player1", glm::translate(vector3(-8.0f, 0.0f, 0.0f)));
	player2 = new Player("Player2", glm::translate(vector3(8.0f, 0.0f, 0.0f)));
	ball1 = new Ball("Ball1", matrix4(IDENTITY), vector3(0.05, 0, 0));
	ball2 = new Ball("Ball2", matrix4(IDENTITY), vector3(-0.05, 0, 0));

	gameObjects.push_back(player1);
	gameObjects.push_back(player2);
	gameObjects.push_back(ball1);
	gameObjects.push_back(ball2);
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
	SafeDelete(grid);
	SafeDelete(window);

	// Release all the singletons used in the dll
	ReleaseAllSingletons();
}

void GameManager::InitMyEngine() {
	// Color of the screen
	windowColor = vector4(0.4f, 0.6f, 0.9f, 0.0f); // Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
		
	// Indicate window properties
	systemSingleton->WindowName = "Bitchin' Pong";
	systemSingleton->WindowWidth = 1280;
	systemSingleton->WindowHeight = 720;
	systemSingleton->WindowFullscreen = false;
	systemSingleton->WindowBorderless = false;

	// Get the singletons
	lightManagerSingleton = LightManagerSingleton::GetInstance();
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
			ProcessMouse();
			Update();
			Display();
		}
		Idle();
	}
}

void GameManager::Idle () {
	m_bFPC = true; //Enable the First Person Camera
}

void GameManager::Update () {
	systemSingleton->UpdateTime(); //Update the system

	player1->Update();
	player2->Update();
	ball1->Update();
	ball2->Update();

	for(int i = 0; i < bombSpawnManager->bombs.size(); i++) {
		if(bombSpawnManager->bombs[i]->boundingBox->Contains(vector3(ball1->GetPosition() * vector4(ball1->boundingBox->GetCentroid(), 1.0f)))) {
			std::cout << "Hey";
		}
	}

	//Update the mesh information
	meshManagerSingleton->Update();

	if(collisionManager->BallCollision(*player1, /**player2,*/ *ball1)) 
	{
		//ball->SwitchDirection("Ball", "Player1");
		ball1->SwitchDirection("Ball1", "Player1");
	}
	else if(collisionManager->BallCollision(*player2, *ball1)) 
	{
		ball1->SwitchDirection("Ball1", "Player2");
	}

	if(collisionManager->BallCollision(*player1, *ball2)) 
	{
		ball2->SwitchDirection("Ball2", "Player1");
	}
	else if(collisionManager->BallCollision(*player2, *ball2)) 
	{
		ball2->SwitchDirection("Ball2", "Player2");
	}
	
	//First person camera movement
	if(m_bFPC == true)
		CameraRotation();

	if(m_bArcBall == true)
		ArcBall();
}

void GameManager::Display (void) {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // clear the window

	grid->Render(100.0f); //renders the grid with a 100 scale

	player1->Draw();
	player2->Draw();
	ball1->Draw();
	ball2->Draw();
	collisionManager->RenderBoxes(gameObjects);
	collisionManager->DrawBounds();
	bombSpawnManager->DrawBombs();

	meshManagerSingleton->Render();

	openGLSingleton->GLSwapBuffers(); //Swaps the OpenGL buffers
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
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

void GameManager::Init( HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	// Is this running out of Visual Studio?
	if(IsDebuggerPresent())
	{
		printf("Shaders: ");
		system("cmd.exe /C xcopy \"../Solution/Shaders\" \"Shaders\" /y /q");
		window->CreateConsoleWindow();
	}

	// Get the system singleton
	systemSingleton = SystemSingleton::GetInstance();

	// Init the App System
	InitMyEngine();

	// Read the configuration file
	ReadConfig();

#pragma region Window Construction and Context setup
	// Create a new window and set its properties
	window = new WindowClass( hInstance, nCmdShow, WndProc);
	window->SetFullscreen(systemSingleton->IsWindowFullscreen());
	window->SetBorderless(systemSingleton->IsWindowBorderless());

	// Make the Window name a wide string
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wide = converter.from_bytes( systemSingleton->WindowName);

	// Create a window in the window class
	window->CreateMEWindow(wide.c_str(), systemSingleton->WindowWidth, systemSingleton->WindowHeight);
	
	// Get the instance of the class
	openGLSingleton = GLSystemSingleton::GetInstance();

	// Set OPENGL 3.x Context
	systemSingleton->m_RenderingContext = OPENGL3X;
	
	// Create context
	openGLSingleton->InitGLDevice(window->GetHandler());

	// Verify what is the OpenGL rendering context and save it to system (3.x might fail, in which case exit)
	if(openGLSingleton->IsNewOpenGLRunning() == false)
		exit(0);
#pragma endregion

	// Get the singletons
	cameraSingleton = CameraSingleton::GetInstance();
	//TEMPORARY SEE IF YOU LIKE AND CHANGE IF NOT
	cameraSingleton->SetPosition(vector3(0.0f, -10.0f, 10.0f));
	cameraSingleton->Rotate(-0.7f, 0.0f);
	
	meshManagerSingleton = MeshManagerSingleton::GetInstance();

	// Initialize the App Variables
	InitInternalAppVariables();
	InitGameObjects();

	//Color of the window
	if(systemSingleton->m_RenderingContext == OPENGL3X)
		glClearColor( windowColor.r, windowColor.g, windowColor.b, windowColor.a);

	//Start the clock
	systemSingleton->StartClock();

	printf("\n");
}

void GameManager::InitGameObjects() {
	player1->Init();
	player2->Init();
	ball1->Init();
	ball2->Init();
	meshManagerSingleton->Update();

	bombSpawnManager->SpawnBomb(gameObjects);
	bombSpawnManager->SpawnBomb(gameObjects);
	bombSpawnManager->SpawnBomb(gameObjects);
	bombSpawnManager->SpawnBomb(gameObjects);
	bombSpawnManager->SpawnBomb(gameObjects);
}

void GameManager::InitInternalAppVariables() {
	// The camera rotation and the arcball are not being used by default
	m_bFPC = false;
	m_bArcBall = false;
	
	// Set the properties for the light in the scene
	lightManagerSingleton->SetPosition( glm::vec3( 0, 0, 10) );
	lightManagerSingleton->SetColor( glm::vec3( 1, 1, 1) );
	lightManagerSingleton->SetIntensity ( 5.0f ); //Rotating Light
	lightManagerSingleton->SetIntensity ( 0.75f, 0 ); //Ambient light (Ambient Light is always the first light, or light[0])

	// Create a new grid initializing its properties and compiling it
	grid = new GridClass(MEAXIS::XY);
	grid->CompileGrid();
}
