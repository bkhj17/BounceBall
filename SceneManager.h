#pragma once
#include "singletonBase.h"

class gameNode;
class SceneManager : public singletonBase<SceneManager>
{
private:
	static gameNode* currentScene;
	static gameNode* readyScene;

	map<string, gameNode*> sceneList;

public:
	SceneManager();
	~SceneManager();

	void Init();
	void Release();
	void Update();
	void Render();

	gameNode* AddScene(string sceneName, gameNode* scene);
	bool ChangeScene(string sceneName);
};

