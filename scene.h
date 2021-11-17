#pragma once

enum GAME_STATUS { RUN, PAUSE, GAMEOVER };

class scene {
public:
	GAME_STATUS status;

public:
	virtual ~scene();

	virtual void init() = 0;											//여기서 필요한 obj 로드 InitBuffer() 개념

	virtual void processKey(unsigned char key, int x, int y) = 0;		//키 입력 처리

	virtual void Update(int value) = 0;									//Timerfunction 역할

	virtual void Render() = 0;											//DrawScene 역할
};