#pragma once
#include "scene.h"

class Shader;


class gameScene : public scene {
public:
	std::vector< glm::vec3 > vertices_sphere;		//정점 저장 변수
	std::vector< glm::vec2 > uvs_sphere;
	std::vector< glm::vec3 > normals_sphere;		//노멀 저장 변수

	glm::mat4 modelmat{ glm::mat4(1.0f) };			//모델 변환 행렬

	GLuint VAO;
	GLuint VBO_position[2];

	Shader ourShader;

public:
	~gameScene();

	virtual void init() override;

	virtual void processKey(unsigned char key, int x, int y) override;

	virtual void Update(const float frametime) override;

	virtual void Render() override;
};