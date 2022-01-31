/// <summary>
/// author Szymon Staneczek Jan/Feb 2022
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processMousePressed(sf::Event t_newEvent);
	void processMouseRelease(sf::Event t_newEvent);
	void planeMovemenet();

	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupBigPlane();


	sf::Texture m_BigPlane;
	sf::Sprite m_BigPlaneSprite;
	sf::Vector2f m_BigPlaneVelociy{ 1.0f, -1.0f };
	sf::Vector2f m_BigPlaneLocation;	

	float m_BigPlaneHeading = 45.0f;



	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	bool m_exitGame; // control exiting game

	sf::Vector2f m_firstClick{ 0.0f, 0.0f };
	sf::Vector2f m_secondClick{ 0.0f, 0.0f };
};

#endif // !GAME_HPP

