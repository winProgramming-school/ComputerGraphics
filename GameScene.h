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
	std::vector< glm::vec3 > vertices_sphere;		//���� ���� ����
	std::vector< glm::vec2 > uvs_sphere;
	std::vector< glm::vec3 > normals_sphere;		//��� ���� ����

	std::vector< glm::vec3 > vertices_floor;		//���� ���� ����
	std::vector< glm::vec2 > uvs_floor;
	std::vector< glm::vec3 > normals_floor;		//��� ���� ����

	glm::mat4 Floor_modelmat{ glm::mat4(1.0f) };

	GLuint VAO[2];
	GLuint VBO_ball[2];
	GLuint VBO_floor[2];

	Shader ourShader;
	BALL ball;

	float floor_FirstZ{};							//ȭ�鿡 ���̴� �ٴ� Ÿ�� �� ���� ���� z��ǥ��

	int** map;

public:
	~gameScene();

	void InitMap();

	virtual void init() override;

	virtual void processKey(unsigned char key, int x, int y) override;

	virtual void Update(const float frametime) override;

	virtual void Render() override;
};