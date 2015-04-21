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

	player1 = new Player(glm::translate(vector3(-6.0f, 0.0f, 0.0f)), "Player1");
	player2 = new Player(glm::translate(vector3(6.0f, 0.0f, 0.0f)), "Player2");
	ball = new Ball();
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

void GameManager::InitPlayers() {
	meshManagerSingleton = MeshManagerSingleton::GetInstance();
	meshManagerSingleton->LoadModel("Minecraft\\MC_Creeper.obj", "Player1", player1->GetPosition());
	meshManagerSingleton->LoadModel("Minecraft\\MC_Creeper.obj", "Player2", player2->GetPosition());
	meshManagerSingleton->LoadModel("Minecraft\\CubePrimitive.obj", "Ball", ball->GetPosition());
	cameraSingleton->SetPosition(vector3(0.0f,0.0f,10.0f));
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

	// Initialize the App Variables
	InitInternalAppVariables();
	InitPlayers();

	//Color of the window
	if(systemSingleton->m_RenderingContext == OPENGL3X)
		glClearColor( windowColor.r, windowColor.g, windowColor.b, windowColor.a);

	//Start the clock
	systemSingleton->StartClock();

	printf("\n");
}
void GameManager::ReadConfig()
{
	//If we are reading the changes the changes, know what file to open
	String sRoot = systemSingleton->m_pFolder->GetFolderRoot();
	String App = systemSingleton->ApplicationName;
	App = sRoot + App + ".cfg";

	FileReaderClass reader;
	//If the file doesnt exist, create it and exit this method
	if(reader.ReadFile(App.c_str()) == MEErrors::ERROR_FILE_MISSING)
	{
		WriteConfig();
		return;
	}
	
	//read the file
	reader.Rewind();
	while(reader.ReadNextLine() == RUNNING)
	{
		String sWord = reader.GetFirstWord();

		int nLenght  = reader.m_sLine.length();
		char* zsTemp = new char[nLenght];
		
		if(sWord == "Fullscreen:")
		{
			int nValue;
			sscanf_s(reader.m_sLine.c_str(), "Fullscreen: %d", &nValue);
			if(nValue == 0)
				systemSingleton->SetWindowFullscreen(false);
			else
				systemSingleton->SetWindowFullscreen(true);
		}
		else if(sWord == "Borderless:")
		{
			int nValue;
			sscanf_s(reader.m_sLine.c_str(), "Borderless: %d", &nValue);
			if(nValue == 0)
				systemSingleton->SetWindowBorderless(false);
			else
				systemSingleton->SetWindowBorderless(true);
		}
		else if(sWord == "Resolution:")
		{
			int nValue1;
			int nValue2;
			sscanf_s(reader.m_sLine.c_str(), "Resolution: [ %d x %d ]", &nValue1,  &nValue2);
			systemSingleton->WindowWidth = nValue1;
			systemSingleton->WindowHeight = nValue2;
		}
		else if(sWord == "Ambient:")
		{
			float fValueX;
			float fValueY;
			float fValueZ;
			sscanf_s(reader.m_sLine.c_str(), "Ambient: [%f,%f,%f]", &fValueX, &fValueY, &fValueZ);
			lightManagerSingleton->SetColor(vector3(fValueX, fValueY, fValueZ), 0);
		}
		else if(sWord == "Background:")
		{
			float fValueX;
			float fValueY;
			float fValueZ;
			float fValueW;
			sscanf_s(reader.m_sLine.c_str(), "Background: [%f,%f,%f,%f]", &fValueX, &fValueY, &fValueZ, &fValueW);
			windowColor = vector4(fValueX, fValueY, fValueZ, fValueW);
		}
		else if(sWord == "AmbientPower:")
		{
			float fValue;
			sscanf_s(reader.m_sLine.c_str(), "AmbientPower: %f", &fValue);
			lightManagerSingleton->SetIntensity(fValue, 0);
		}
		else if(sWord == "Data:")
		{
			sscanf_s(reader.m_sLine.c_str(), "Data: %s", zsTemp, nLenght);
			systemSingleton->m_pFolder->SetFolderData( zsTemp );
		}
		else if(sWord == "3DS:")
		{
			sscanf_s(reader.m_sLine.c_str(), "3DS: %s", zsTemp, nLenght);
			systemSingleton->m_pFolder->SetFolderM3DS( zsTemp );
		}
		else if(sWord == "BTO:")
		{
			sscanf_s(reader.m_sLine.c_str(), "BTO: %s", zsTemp, nLenght);
			systemSingleton->m_pFolder->SetFolderMBTO( zsTemp );
		}
		else if(sWord == "FBX:")
		{
			sscanf_s(reader.m_sLine.c_str(), "FBX: %s", zsTemp, nLenght);
			systemSingleton->m_pFolder->SetFolderMFBX( zsTemp );
		}
		else if(sWord == "OBJ:")
		{
			sscanf_s(reader.m_sLine.c_str(), "OBJ: %s", zsTemp, nLenght);
			systemSingleton->m_pFolder->SetFolderMOBJ( zsTemp );
		}
		else if(sWord == "POM:")
		{
			sscanf_s(reader.m_sLine.c_str(), "POM: %s", zsTemp, nLenght);
			systemSingleton->m_pFolder->SetFolderMPOM( zsTemp );
		}
		else if(sWord == "Level:")
		{
			sscanf_s(reader.m_sLine.c_str(), "Level: %s", zsTemp, nLenght);
			systemSingleton->m_pFolder->SetFolderLVL( zsTemp );
		}
		else if(sWord == "Textures:")
		{
			sscanf_s(reader.m_sLine.c_str(), "Textures: %s", zsTemp, nLenght);
			systemSingleton->m_pFolder->SetFolderTextures( zsTemp );
		}

		delete[] zsTemp;
		zsTemp = nullptr;
	}
	reader.CloseFile();
}
void GameManager::WriteConfig()
{
	// Write the configuration for this application
	String sRoot = systemSingleton->m_pFolder->GetFolderRoot();
	String App = systemSingleton->ApplicationName;
	App = sRoot + App + ".cfg";

	FILE *pFile; 
	fopen_s(&pFile, App.c_str(),"w");
	if(!pFile)	//If we couldn't create the file we exit without changes.
		return;

	rewind(pFile);
	fprintf(pFile,"# Configuration file for the program: %s", systemSingleton->GetAppName().c_str());
	
	fprintf(pFile,"\n\nFullscreen: ");
	if(systemSingleton->IsWindowFullscreen())
		fprintf(pFile,"1");
	else
		fprintf(pFile,"0");

	fprintf(pFile,"\nBorderless: ");
	if(systemSingleton->IsWindowBorderless())
		fprintf(pFile,"1");
	else
		fprintf(pFile,"0");

	fprintf(pFile,"\nContext: OPENGL3X"); //Only openGL3X context is supported ATM

	fprintf(pFile,"\n\n# Resolution: [ 640 x 480 ]");
	fprintf(pFile,"\n# Resolution: [ 1280 x 720 ]");
	fprintf(pFile,"\n# Resolution: [ 1680 x 1050 ]");
	fprintf(pFile,"\n# Resolution: [ 1920 x 1080 ]");
	fprintf(pFile,"\n# Resolution: [ 2650 x 1440 ]");
	fprintf(pFile,"\nResolution: [ %d x %d ]", systemSingleton->WindowWidth, systemSingleton->WindowHeight);

	fprintf(pFile,"\n\nAmbient: [%.2f,%.2f,%.2f]",
		lightManagerSingleton->GetColor(0).r, lightManagerSingleton->GetColor(0).g, lightManagerSingleton->GetColor(0).b);
	fprintf(pFile,"\nAmbientPower: %.2f", lightManagerSingleton->GetIntensity(0));

	fprintf(pFile,"\n\nBackground: [%.3f,%.3f,%.3f,%.3f]",
		windowColor.r, windowColor.g, windowColor.b, windowColor.a);

	fprintf(pFile,"\n\n# Folders:");
	
	fprintf(pFile,"\nData:		%s", systemSingleton->m_pFolder->GetFolderData().c_str());
	fprintf(pFile,"\n3DS:		%s", systemSingleton->m_pFolder->GetFolderM3DS().c_str());
	fprintf(pFile,"\nBTO:		%s", systemSingleton->m_pFolder->GetFolderMBTO().c_str());
	fprintf(pFile,"\nFBX:		%s", systemSingleton->m_pFolder->GetFolderMFBX().c_str());
	fprintf(pFile,"\nOBJ:		%s", systemSingleton->m_pFolder->GetFolderMOBJ().c_str());
	fprintf(pFile,"\nLevel:		%s", systemSingleton->m_pFolder->GetFolderLVL().c_str());
	fprintf(pFile,"\nTextures:	%s", systemSingleton->m_pFolder->GetFolderTextures().c_str());

	fclose(pFile);
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
	float fTimeSpan = systemSingleton->LapClock(0); //Check the time difference between this method calls
	static float fRunTime = 0.0f;
	fRunTime += fTimeSpan; //Update the run time count

	player1->Update();
	player2->Update();
	ball->Update();

	player1->SetPosition(collisionManager->PlayerInBounds(player1->GetPosition(), "Player1"));
	player2->SetPosition(collisionManager->PlayerInBounds(player2->GetPosition(), "Player2"));
	collisionManager->GenerateBoundingBoxes(player1->GetPosition(), player2->GetPosition(), ball->GetPosition());	

	meshManagerSingleton->SetModelMatrix(player1->GetPosition(), "Player1");
	meshManagerSingleton->SetModelMatrix(player2->GetPosition(), "Player2");
	meshManagerSingleton->SetModelMatrix(ball->GetPosition(), "Ball");

	meshManagerSingleton->Update(); //Update the mesh information
	meshManagerSingleton->AddInstanceToRenderList("ALL");

	if(collisionManager->BallCollision(*player1, *player2, *ball)) {
		ball->SwitchDirection();
	}

	
	//First person camera movement
	if(m_bFPC == true)
		CameraRotation();

	if(m_bArcBall == true)
		ArcBall();

	printf("FPS: %d, %.3f\r", systemSingleton->FPS, fRunTime);//print the Frames per Second
}

void GameManager::Display (void) {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // clear the window

	grid->Render(100.0f); //renders the grid with a 100 scale

	meshManagerSingleton->Render();

	openGLSingleton->GLSwapBuffers(); //Swaps the OpenGL buffers
}
