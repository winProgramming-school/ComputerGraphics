#pragma once
#include "scene.h"

#define FLOOR_SIZE 0.3f

class Shader;

enum OBSTACLE{NORMAL, NONE, CONE};

typedef struct BALL {
	glm::mat4 modelmat{ glm::mat4(1.0f) };
	float x{0.0f};
	float y{1.0f};

	float rAngle{0.0f};
}BALL;



class gameScene : public scene {
public:
	std::vector< glm::vec3 > vertices_sphere;		//정점 저장 변수
	std::vector< glm::vec2 > uvs_sphere;
	std::vector< glm::vec3 > normals_sphere;		//노멀 저장 변수

	std::vector< glm::vec3 > vertices_floor;		//정점 저장 변수
	std::vector< glm::vec2 > uvs_floor;
	std::vector< glm::vec3 > normals_floor;		//노멀 저장 변수

	glm::mat4 Floor_modelmat{ glm::mat4(1.0f) };

	GLuint VAO[2];
	GLuint VBO_ball[2];
	GLuint VBO_floor[2];

	Shader ourShader;
	BALL ball;

	float floor_FirstZ{};							//화면에 보이는 바닥 타일 중 제일 작은 z좌표값

	int** map;

public:
	~gameScene();

	void InitMap();

	virtual void init() override;

	virtual void processKey(unsigned char key, int x, int y) override;

	virtual void Update(const float frametime) override;

	virtual void Render() override;
};