#pragma once
#include "stdafx.h"
enum GAME_STATUS { RUN, PAUSE, GAMEOVER };

struct CAMERAPOS {
	float x{};
	float y{};
	float z{};
	glm::vec3 cameraPos{ glm::vec3(x, y, z) };
	glm::vec3 cameraUp{ glm::vec3(0.0f, 1.0f, 0.0f) };
};

struct CAMERADIR {
	float x{};
	float y{};
	float z{};
	glm::vec3 cameraDirection{ glm::vec3(x, y, z) };
};

struct LIGHTPOS {
	float x{};
	float y{};
	float z{};
};

class scene {
public:
	GAME_STATUS status;
	unsigned int projectionLocation{};		//������� uniform ��ġ
	unsigned int viewLocation{};			//����� uniform ��ġ
	unsigned int modelLocation{};			//����� uniform ��ġ
	unsigned int fragColor{};				//�����׸�Ʈ ���� uniform ��ġ

	unsigned int lightPos{};				//���� ��ġ uniform ��ġ
	unsigned int lightColor{};				//���� �� uniform ��ġ(�ʿ� ������ ������� ����)
	unsigned int viewPos{};					//�ü����� uniform ��ġ

	glm::mat4 projection{ glm::mat4(1.0f) };	//�������
	glm::mat4 view{ glm::mat4(1.0f) };			//�� ���


	//ī�޶�� ������ġ, ī�޶� �ٶ󺸴� ���� scene ���� �� �������ֱ�
	struct CAMERAPOS CP;
	struct CAMERADIR CD;
	struct LIGHTPOS LP;

	int stage{ 1 };

public:
	~scene();

	virtual void init() = 0;											//���⼭ �ʿ��� obj �ε� InitBuffer() ����

	virtual void processKey(unsigned char key, int x, int y) = 0;		//Ű �Է� ó��

	virtual void Mouse(int button, int state, int x, int y) = 0;

	virtual void MouseMotion(int x, int y) = 0;

	virtual void Update(const float frameTime) = 0;						//Timerfunction ����

	virtual void Render() = 0;											//DrawScene ����
};