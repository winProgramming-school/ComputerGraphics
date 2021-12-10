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
	unsigned int projectionLocation{};		//투영행렬 uniform 위치
	unsigned int viewLocation{};			//뷰행렬 uniform 위치
	unsigned int modelLocation{};			//모델행렬 uniform 위치
	unsigned int fragColor{};				//프래그먼트 색상 uniform 위치

	unsigned int lightPos{};				//조명 위치 uniform 위치
	unsigned int lightColor{};				//조명 색 uniform 위치(필요 없을듯 흰색으로 고정)
	unsigned int viewPos{};					//시선벡터 uniform 위치

	glm::mat4 projection{ glm::mat4(1.0f) };	//투영행렬
	glm::mat4 view{ glm::mat4(1.0f) };			//뷰 행렬


	//카메라와 조명위치, 카메라가 바라보는 곳은 scene 생성 시 설정해주기
	struct CAMERAPOS CP;
	struct CAMERADIR CD;
	struct LIGHTPOS LP;

	int stage{ 1 };

public:
	~scene();

	virtual void init() = 0;											//여기서 필요한 obj 로드 InitBuffer() 개념

	virtual void processKey(unsigned char key, int x, int y) = 0;		//키 입력 처리

	virtual void Mouse(int button, int state, int x, int y) = 0;

	virtual void MouseMotion(int x, int y) = 0;

	virtual void Update(const float frameTime) = 0;						//Timerfunction 역할

	virtual void Render() = 0;											//DrawScene 역할
};