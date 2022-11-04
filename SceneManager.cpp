#include "Game.h"
#include "SceneManager.h"
#include "gameNode.h"

gameNode *SceneManager::currentScene = NULL;
gameNode *SceneManager::readyScene = NULL;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	currentScene = NULL;
	readyScene = NULL;
}

void SceneManager::Release()
{
	map<string, gameNode*>::iterator it;

	for (it = sceneList.begin(); it != sceneList.end();) {
		if (it->second != NULL) {
			if (it->second == currentScene) {
				it->second->release();
			}

			SAFE_DELETE(it->second);

			it = sceneList.erase(it);
		}
		else ++it;
	}

	getSingleton()->releaseSingleton();
}

void SceneManager::Update()
{
	if (currentScene) currentScene->update();
}

void SceneManager::Render()
{
	if (currentScene) currentScene->render();
}

gameNode * SceneManager::AddScene(string sceneName, gameNode * scene)
{
	if (!scene) return NULL;

	sceneList.insert(make_pair(sceneName, scene));

	return scene;
}

bool SceneManager::ChangeScene(string sceneName)
{
	map<string, gameNode*>::iterator it;
	it = sceneList.find(sceneName);

	if (it == sceneList.end()) return false;

	if ((it->second) == currentScene) return false;

	if (SUCCEEDED((it->second)->init())) {
		if (currentScene) currentScene->release();

		currentScene = it->second;
		return true;
	}

	return false;
}
