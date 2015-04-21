#include "Main.h"

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
	GameManager* pong = GameManager::GetInstance(hInstance, lpCmdLine, nCmdShow);

	pong->Run();

	GameManager::ReleaseInstance();

	return 0;
}