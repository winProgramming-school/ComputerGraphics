#pragma once
#include "scene.h"
#include <windows.h>

#define GRAVITY -15.0f

class Shader;


typedef struct BALL {
	glm::mat4 modelmat{ glm::mat4(1.0f) };
	float x{ 0.0f };
	float y{ 1.0f };

	float r{ 0.8f };
	float g{ 0.619f };
	float b{ 1.0f };
	float rAngle{ 0.0f };

	bool isJump{ false };
	bool falling{ false };

	void Init() {
		x =0.0f;
		y =1.0f;

		r =0.8f;
		g =0.619f;
		b =1.0f;
		rAngle =0.0f;

		isJump = false;
		falling = false;
	}

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
	int lifePoint{3};								//���						

	int** map;

	

	float floor_xPos = -2.0f;
	float floor_zPos = 0.0f;
	float speed{};
	float sizeOfWallx = 3.0f;
	float sizeOfWally = 0.01f;
	float sizeOfWallz = 3.0f;

	float obstacle_speed[5]{ 4.0f, 5.0f,6.0f, 7.0f, 8.0f };		//���� ��ֹ� �ӵ�
	float obstacle_y[5]{ 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };			//���� ��ֹ� ����
	bool obstacle_up[5]{ true, true, false, false, true };		//���� ��ֹ� up or down

	bool clearStage = false;
	bool overStage = false;

	bool pause{ false };
	bool testmode{ false };

	////�ؽ�ó ���̴� uniform ���� ��ġ
	//unsigned int viewLocation2, projectionLocation2, modelLocation2;
	//unsigned int texture;

public:
	~gameScene();

	void InitMap();
	void InitTexture();
	void drawModel();
	void SoundSystem();
	void Play(int Sound_num, int cannel);

	virtual void init() override;

	virtual void processKey(unsigned char key, int x, int y) override;

	virtual void Mouse(int button, int state, int x, int y) override;

	virtual void MouseMotion(int x, int y) override;

	virtual void Update(const float frametime) override;

	virtual void Render() override;
};