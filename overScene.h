#pragma once
#include "scene.h"

class Shader;

class overScene : public scene {
public:
	std::vector< glm::vec3 > vertices_back;
	std::vector< glm::vec2 > uvs_back;
	std::vector< glm::vec3 > normals_back;

	GLuint VAO_back;
	GLuint VBO_back_position[2];

	Shader ourShader2;


public:
	~overScene();

	void InitTexture();

	virtual void init() override;

	virtual void processKey(unsigned char key, int x, int y) override;

	virtual void Mouse(int button, int state, int x, int y) override;

	virtual void MouseMotion(int x, int y) override;

	virtual void Update(const float frameTime) override;

	virtual void Render() override;
};