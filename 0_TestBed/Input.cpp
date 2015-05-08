/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#include "GameManager.h"

/* ProcessKeyboard */
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
		player1->MovePlayer(1);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		player1->MovePlayer(-1);
	}

	/* Player 2 Positioning */
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		player2->MovePlayer(1);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		player2->MovePlayer(-1);
	}
}