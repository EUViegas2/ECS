#include "Scene.h"
#include "Game.h"

Scene::Scene() = default;

Scene::Scene(Game* game) : m_game(game) {}

Scene::~Scene() = default;

void Scene::setPaused(bool paused) {
    m_paused = paused;
}

void Scene::simulate(const size_t frames) {}

void Scene::registerAction(int inputKey, const std::string& actionName) {
    m_actionMap[inputKey] = actionName;
}

float Scene::width() const {
    return static_cast<float>(m_game->window().getSize().x);
}

float Scene::height() const {
    return static_cast<float>(m_game->window().getSize().y);
}

size_t Scene::currentFrame() const {
    return m_currentFrame;
}

bool Scene::hasEnded() const {
    return m_hasEnded;
}

const ActionMap& Scene::getActionMap() const {
    return m_actionMap;
}