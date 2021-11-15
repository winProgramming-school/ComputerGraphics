#pragma once

enum GAME_STATUS { RUN, PAUSE, GAMEOVER };

class scene {
public:
	GAME_STATUS status;

public:
	virtual ~scene();

	virtual void init() = 0;

	virtual void processKey(unsigned char key, int x, int y) = 0;

	virtual void Update(int value) = 0;

	virtual void Render(HDC hdc) = 0;
};