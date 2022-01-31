/// <summary>
/// @author Szymon Staneczek
/// @date Jan/Feb 2022
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupBigPlane(); // loads big plane

}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type)
		{
			processMousePressed(newEvent);
		}
		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			processMouseRelease(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

void Game::processMousePressed(sf::Event t_newEvent)
{
	m_firstClick.x = t_newEvent.mouseButton.x;
	m_firstClick.y = t_newEvent.mouseButton.y;

}

void Game::processMouseRelease(sf::Event t_newEvent)
{
	m_secondClick.x = t_newEvent.mouseButton.x;
	m_secondClick.y = t_newEvent.mouseButton.y;
	sf::Vector2f velocity = m_secondClick - m_firstClick;

	float headingRadians = std::atan2(velocity.y, velocity.x);
	float headingDegrees = 180.0f * headingRadians / static_cast<float>(M_PI);
	headingDegrees += 90.0f;
	if (sf::Mouse::Left == t_newEvent.mouseButton.button)
	{
		m_BigPlaneVelociy = velocity / 100.0f;
		m_BigPlaneHeading = headingDegrees;
		m_BigPlaneSprite.setRotation(headingDegrees);
	}
}

void Game::planeMovemenet()
{
	m_BigPlaneLocation += m_BigPlaneVelociy;
	m_BigPlaneSprite.setPosition(m_BigPlaneLocation);

}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	planeMovemenet();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_welcomeMessage);
	m_window.draw(m_BigPlaneSprite);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	

}

void Game::setupBigPlane()
{
	if (!m_BigPlane.loadFromFile("ASSETS\\IMAGES\\planes.png"))
	{
		std::cout << "problem loading big plane texture" << std::endl;
	}

	sf::IntRect bigPlaneRect{ 3, 11, 104, 93 };
	sf::Vector2f bigPlaneStart{ 300.0f, 180.0f };

	m_BigPlaneSprite.setTexture(m_BigPlane);
	m_BigPlaneSprite.setTextureRect(bigPlaneRect);
	m_BigPlaneSprite.setPosition(bigPlaneStart);
	m_BigPlaneLocation = bigPlaneStart;

	m_BigPlaneSprite.setOrigin(bigPlaneRect.height / 2.0f, bigPlaneRect.width / 2.0f);
	m_BigPlaneSprite.setRotation(m_BigPlaneHeading);
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>

