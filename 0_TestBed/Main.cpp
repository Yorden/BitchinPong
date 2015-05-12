/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#include "Main.h"

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
	GameManager* pong = GameManager::GetInstance(hInstance, lpCmdLine, nCmdShow);

	pong->Run();

	GameManager::ReleaseInstance();

	return 0;
}