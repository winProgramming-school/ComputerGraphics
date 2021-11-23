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

	//카메라와 조명위치, 카메라가 바라보는 곳은 scene 생성 시 설정해주기
	float cameraPosz{  };
	float cameraPosx{  };
	float cameraPosy{  };

	float cameraDirPosx{ 0.0f };
	float cameraDirPosy{ 0.0f };
	float cameraDirPosz{ 0.0f };

	float lightPosz{  };
	float lightPosx{  };
	float lightPosy{  };

	//카메라 관련 vec3들
	glm::vec3 cameraPos{ glm::vec3(cameraPosx, cameraPosy, cameraPosz) };				//--- 카메라 위치
	glm::vec3 cameraDirection{ glm::vec3(cameraDirPosx, 0.0f, cameraDirPosz) };	//--- 카메라 바라보는 방향
	glm::vec3 cameraUp{ glm::vec3(0.0f, 1.0f, 0.0f) };

public:
	virtual ~scene();

	virtual void init() = 0;											//여기서 필요한 obj 로드 InitBuffer() 개념

	virtual void processKey(unsigned char key, int x, int y) = 0;		//키 입력 처리

	virtual void Update(int value) = 0;									//Timerfunction 역할

	virtual void Render() = 0;											//DrawScene 역할
};