#pragma once

#include "Actions.h"
#include "EntityManager.h"

class Game;
typedef std::map < int, std::string > ActionMap;


class Scene
{
protected:
	Game*					m_game = nullptr;
	EntityManager			m_entityManager;
	ActionMap				m_actionMap;

	bool					m_paused{ false };
	bool					m_hasEnded{ false };
	size_t					m_currentFrame{ 0 };


	virtual void onEnd() = 0;
	void setPaused(bool paused);


public:

	Scene() {};
	Scene(Game* game);
	virtual void update() = 0;
	virtual void sDoAction(const Action& action) = 0;
	virtual void sRender() = 0;
	void simulate(size_t frames);

	void registerAction(int inputKey, const std::string& actionName);
	[[nodiscard]] float width() const;

	[[nodiscard]] float height() const;

	[[nodiscard]] size_t currentFrame() const;

	[[nodiscard]] bool hasEnded() const;

	[[nodiscard]] const ActionMap& getActionMap() const;
};

