#pragma once
#include "scene.h"

#define GRAVITY -15.0f

class Shader;

enum OBSTACLE{NORMAL, NONE, CONE};

typedef struct BALL {
	glm::mat4 modelmat{ glm::mat4(1.0f) };
	float x{0.0f};
	float y{10.0f};

	float rAngle{0.0f};

	bool isJump{ false };
}BALL;



class gameScene : public scene {
public:
	std::vector< glm::vec3 > vertices_sphere;		//정점 저장 변수
	std::vector< glm::vec3 > vertices_floor;		//정점 저장 변수
	std::vector< glm::vec2 > uvs_sphere;
	std::vector< glm::vec2 > uvs_floor;
	std::vector< glm::vec3 > normals_sphere;		//노멀 저장 변수
	std::vector< glm::vec3 > normals_floor;		//노멀 저장 변수

	glm::mat4 modelmat{ glm::mat4(1.0f) };			//모델 변환 행렬
	glm::mat4 modelmat_f{ glm::mat4(1.0f) };			//모델 변환 행렬

	GLuint VAO;
	GLuint VBO_position[2];
	GLuint VAO_f;
	GLuint VBO_f_position[2];

	
	Shader ourShader;
	BALL ball;

	float floor_FirstZ{};							//화면에 보이는 바닥 타일 중 제일 작은 z좌표값

	int** map;

	float floor_xPos = -2.0f;
	float floor_zPos = 0.0f;
	float speed{};


public:
	~gameScene();

	void InitMap();

	virtual void init() override;

	virtual void processKey(unsigned char key, int x, int y) override;

	virtual void Update(const float frametime) override;

	virtual void Render() override;
};