#pragma once

enum SCENE { MENU, GAME, STAGE2 };

class GameFramework
{
public:
	scene* curScene;
	SCENE nowscene;
	clock_t prevFrameTime;
	clock_t curFrameTime;

public:
	GameFramework();
	~GameFramework();

	void Reset();
	void Clear();

	void Create(HWND hWnd);
	void OnDraw();
	void OnUpdate(int value);
	void KeyBoard(unsigned char key, int x, int y);

	float GetTick();
};