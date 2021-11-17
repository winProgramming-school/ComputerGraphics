#pragma once

enum GAME_STATUS { RUN, PAUSE, GAMEOVER };

class scene {
public:
	GAME_STATUS status;

public:
	virtual ~scene();

	virtual void init() = 0;											//���⼭ �ʿ��� obj �ε� InitBuffer() ����

	virtual void processKey(unsigned char key, int x, int y) = 0;		//Ű �Է� ó��

	virtual void Update(int value) = 0;									//Timerfunction ����

	virtual void Render() = 0;											//DrawScene ����
};