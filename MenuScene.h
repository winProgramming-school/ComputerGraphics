#pragma once
#include "scene.h"

class Shader;

class menuScene : public scene {
public:
	std::vector< glm::vec3 > vertices_sphere;		//정점 저장 변수
	std::vector< glm::vec2 > uvs_sphere;			
	std::vector< glm::vec3 > normals_sphere;		//노멀 저장 변수

	std::vector< glm::vec3 > vertices_back;
	std::vector< glm::vec2 > uvs_back;
	std::vector< glm::vec3 > normals_back;

	glm::mat4 modelmat{ glm::mat4(1.0f) };			//뷰 행렬

	GLuint VAO;
	GLuint VBO_position[2];
	GLuint VAO_back;
	GLuint VBO_back_position[2];

	Shader ourShader;
	Shader ourShader2;

	int balljump_count{ 0 };
	bool ballJump{ false };
	float ball_y{ -1.0f };

public:
	~menuScene();

	void InitTexture();

	virtual void init() override;

	virtual void processKey(unsigned char key, int x, int y) override;

	virtual void Mouse(int button, int state, int x, int y) override;

	virtual void MouseMotion(int x, int y) override;

	virtual void Update(const float frameTime) override;

	virtual void Render() override;
};