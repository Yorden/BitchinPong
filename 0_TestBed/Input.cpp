#include "GameManager.h"
void GameManager::ProcessKeyboard()
{
	float fSpeed = 0.1f;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		//To correctly terminate the application releasing memory
		PostMessage(window->GetHandler(), WM_QUIT, NULL, NULL); 
		//exit(0); //will not terminate cleanly at this point
	}

	/* Player 1 Positioning */
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		player1->IncrementAcceleration(0.05f);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		player1->IncrementAcceleration(-0.05f);
	}

	/* Player 2 Positioning */
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		player2->IncrementAcceleration(0.05f);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		player2->IncrementAcceleration(-0.005f);
	}
}

void GameManager::ProcessMouse(){
	m_bArcBall = false;
	m_bFPC = false;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
		m_bArcBall = true;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		m_bFPC = true;

	static bool bLeft_Released = false;
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		bLeft_Released = true;
	}
	else
	{
		if(bLeft_Released == true)
		{
		}
		bLeft_Released = false;
	}
}
void GameManager::CameraRotation(float a_fSpeed){
	UINT	MouseX, MouseY;		// Coordinates for the mouse
	UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

	CenterX = systemSingleton->WindowX + systemSingleton->WindowWidth / 2;
	CenterY = systemSingleton->WindowY + systemSingleton->WindowHeight / 2;
	
	float DeltaMouse;
	POINT pt;

	GetCursorPos(&pt);
	
	MouseX = pt.x;
	MouseY = pt.y;

	SetCursorPos(CenterX, CenterY);

	static float fAngleX = 0.0f;
	static float fAngleY = 0.0f;

	if(MouseX < CenterX)
	{
		DeltaMouse = static_cast<float>(CenterX - MouseX);
		fAngleY += DeltaMouse * a_fSpeed;
	}
	else if(MouseX > CenterX)
	{
		DeltaMouse = static_cast<float>(MouseX - CenterX);
		fAngleY -= DeltaMouse * a_fSpeed;
	}

	if(MouseY < CenterY)
	{
		DeltaMouse = static_cast<float>(CenterY - MouseY);
		fAngleX -= DeltaMouse * a_fSpeed;
	}
	else if(MouseY > CenterY)
	{
		DeltaMouse = static_cast<float>(MouseY - CenterY);
		fAngleX += DeltaMouse * a_fSpeed;
	}
	cameraSingleton->Rotate(fAngleX, fAngleY);
}
void GameManager::ArcBall(float a_fSensitivity){
	static matrix4 arcball;
	UINT	MouseX, MouseY;		// Coordinates for the mouse
	UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

	CenterX = systemSingleton->WindowX + systemSingleton->WindowWidth / 2;
	CenterY = systemSingleton->WindowY + systemSingleton->WindowHeight / 2;
	
	float DeltaMouse;
	POINT pt;

	GetCursorPos(&pt);
	
	MouseX = pt.x;
	MouseY = pt.y;

	SetCursorPos(CenterX, CenterY);

	static float fVerticalAngle = 0.0f;
	static float fHorizontalAngle = 0.0f;

	float fSpeed = 0.001f;

	if(MouseX < CenterX)
	{
		DeltaMouse = static_cast<float>(CenterX - MouseX);
		arcball = glm::rotate(arcball, a_fSensitivity * DeltaMouse, vector3(0.0f, 1.0f, 0.0f));
	}
	else if(MouseX > CenterX)
	{
		DeltaMouse = static_cast<float>(MouseX - CenterX);
		arcball = glm::rotate(arcball, -a_fSensitivity * DeltaMouse, vector3(0.0f, 1.0f, 0.0f));
	}

	if(MouseY < CenterY)
	{
		DeltaMouse = static_cast<float>(CenterY - MouseY);
		arcball = glm::rotate(arcball, a_fSensitivity * DeltaMouse, vector3(1.0f, 0.0f, 0.0f));
	}
	else if(MouseY > CenterY)
	{
		DeltaMouse = static_cast<float>(MouseY - CenterY);
		arcball = glm::rotate(arcball, -a_fSensitivity * DeltaMouse, vector3(1.0f, 0.0f, 0.0f));
	}
}