#pragma once
#include <string>
#include<memory>
#include<SFML/Graphics.hpp>

class Game
{
public:
	sf::Window m_window;
	Game(const std::string& config){}

	void init(const std::string& path);

};

