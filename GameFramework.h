#pragma once
#include "scene.h"

enum SCENE { MENU, GAME, STAGE2 };

class scene;

class GameFramework
{
public:
	scene* curScene{};
	SCENE nowscene{};
	clock_t prevFrameTime{};
	clock_t curFrameTime{};

public:
	GameFramework();
	~GameFramework();

	void Reset();
	void Clear();

	void Create();
	void OnDraw();
	void OnUpdate(const float frameTime);
	void KeyBoard(unsigned char key, int x, int y);
	void Mouse(int button, int state, int x, int y);
	void MouseMotion(int x, int y);

	float GetTick();
};