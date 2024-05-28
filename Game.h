#pragma once

#include "Entity.h"
#include "Scene.h"

#include<fstream>
#include<iostream>
#include <memory>

#include<SFML/Graphics.hpp>

typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;
struct WindowConfig { int W, H, FL, FS; };

/*
SR Shape Radius
CR Colision Radius
FR 
FG
FB Fill Colors RGB
OR
OG
OB Outline Colors RGB
OT Outline Thickness
V Vertices / Vmin VMAX vertices
L LifeSpan
S Speed / Smin SMAX speeds
SI Spawn Interval
*/
class Game
{

	WindowConfig			m_windowConfig;
	sf::RenderWindow		m_window;	//the window to be drawn
	sf::Clock				m_deltaClock;

	//Scenes
	std::string				m_currentMap;
	std::string				m_currentScene;
	SceneMap				m_sceneMap;

	std::shared_ptr<Scene> currentScene();

	bool					m_running				{ true };
	void init(const std::string& path);
	void sUserInput();
	void update();
public:

	Game(const std::string& config);
	void changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene = false);
	void run();
	void quit();
	bool isRunning();

	sf::RenderWindow& window()

};

