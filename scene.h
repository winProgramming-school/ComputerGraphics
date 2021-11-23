#pragma once

enum GAME_STATUS { RUN, PAUSE, GAMEOVER };

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

public:
	virtual ~scene();

	virtual void init() = 0;											//여기서 필요한 obj 로드 InitBuffer() 개념

	virtual void processKey(unsigned char key, int x, int y) = 0;		//키 입력 처리

	virtual void Update(int value) = 0;									//Timerfunction 역할

	virtual void Render() = 0;											//DrawScene 역할
};