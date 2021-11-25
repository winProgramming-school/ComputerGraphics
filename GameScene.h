#pragma once
#include "scene.h"

namespace BALL {
	//���� ��ġ
	float x{0.0f};
	float y{1.0f};
	float z{0.0f};			//BALL�� z��ǥ�� ��� ����

	float rAngle{ 0.0f };	//�� �������� ����
}

class Shader;
class gameScene : public scene {
public:
	std::vector< glm::vec3 > vertices_sphere;		//���� ���� ����
	std::vector< glm::vec2 > uvs_sphere;
	std::vector< glm::vec3 > normals_sphere;		//��� ���� ����

	glm::mat4 modelmat{ glm::mat4(1.0f) };			//�� ��ȯ ���

	GLuint VAO;
	GLuint VBO_position[2];

	Shader ourShader;
public:
	virtual ~gameScene() override;

	virtual void init() override;

	virtual void processKey(unsigned char key, int x, int y) override;

	virtual void Update(const float frametime) override;

	virtual void Render() override;
};