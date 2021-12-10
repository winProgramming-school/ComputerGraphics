#pragma once
#include "scene.h"

#define GRAVITY -15.0f

class Shader;

enum OBSTACLE{NORMAL, NONE, CONE};

typedef struct BALL {
	glm::mat4 modelmat{ glm::mat4(1.0f) };
	float x{0.0f};
	float y{1.0f};

	float r{ 0.8f };
	float g{ 0.619f };
	float b{ 1.0f };
	float rAngle{0.0f};

	bool isJump{ false };
	bool falling{ false };
}BALL;

typedef struct MOUSE {
	float x{};
	float y{};

	float move{};

	bool mouse_down{ true };
}MOUSE;

class gameScene : public scene {
public:
	std::vector< glm::vec3 > vertices_sphere;		//���� ���� ����
	std::vector< glm::vec3 > vertices_floor;		//���� ���� ����
	std::vector< glm::vec3 > vertices_back;		//���� ���� ����

	std::vector< glm::vec3 > vertices_ob1;		//���� ���� ����
	std::vector< glm::vec2 > uvs_sphere;
	std::vector< glm::vec2 > uvs_floor;
	std::vector< glm::vec2 > uvs_back;

	std::vector< glm::vec3 > normals_sphere;	//��� ���� ����
	std::vector< glm::vec2 > uvs_ob1;
	std::vector< glm::vec3 > normals_floor;		//��� ���� ����
	std::vector< glm::vec3 > normals_ob1;		//��� ���� ����
	std::vector< glm::vec3 > normals_back;		//��� ���� ����

	glm::mat4 modelmat{ glm::mat4(1.0f) };			//�� ��ȯ ���
	glm::mat4 modelmat_f{ glm::mat4(1.0f) };			//�� ��ȯ ���
	glm::mat4 modelmat_ob1{ glm::mat4(1.0f) };			//�� ��ȯ ���

	GLuint VAO;
	GLuint VBO_position[2];
	GLuint VAO_f;
	GLuint VBO_f_position[2];
	GLuint VAO_ob1;
	GLuint VBO_ob1_position[2];

	GLuint VAO_back;
	GLuint VBO_back_position[2];
	
	Shader ourShader;
	Shader ourShader2;

	BALL ball;
	MOUSE mouse;

	float floor_FirstZ{};							//ȭ�鿡 ���̴� �ٴ� Ÿ�� �� ���� ���� z��ǥ��
	int index{};									//�ٴ� ���� �ε���

	int** map;

	float floor_xPos = -2.0f;
	float floor_zPos = 0.0f;
	float speed{};
	float sizeOfWallx = 3.0f;
	float sizeOfWally = 0.01f;
	float sizeOfWallz = 3.0f;

	bool clearStage = false;
	bool overStage = false;
	
	////�ؽ�ó ���̴� uniform ���� ��ġ
	//unsigned int viewLocation2, projectionLocation2, modelLocation2;
	//unsigned int texture;

public:
	~gameScene();

	void InitMap();
	void InitTexture();
	void drawModel();

	virtual void init() override;

	virtual void processKey(unsigned char key, int x, int y) override;

	virtual void Mouse(int button, int state, int x, int y) override;

	virtual void MouseMotion(int x, int y) override;

	virtual void Update(const float frametime) override;

	virtual void Render() override;
};