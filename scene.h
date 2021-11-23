#pragma once

enum GAME_STATUS { RUN, PAUSE, GAMEOVER };

class scene {
public:
	GAME_STATUS status;
	unsigned int projectionLocation{};		//������� uniform ��ġ
	unsigned int viewLocation{};			//����� uniform ��ġ
	unsigned int modelLocation{};			//����� uniform ��ġ
	unsigned int fragColor{};				//�����׸�Ʈ ���� uniform ��ġ

	unsigned int lightPos{};				//���� ��ġ uniform ��ġ
	unsigned int lightColor{};				//���� �� uniform ��ġ(�ʿ� ������ ������� ����)
	unsigned int viewPos{};					//�ü����� uniform ��ġ

	glm::mat4 projection{ glm::mat4(1.0f) };	//�������
	glm::mat4 view{ glm::mat4(1.0f) };			//�� ���

	//ī�޶�� ������ġ, ī�޶� �ٶ󺸴� ���� scene ���� �� �������ֱ�
	float cameraPosz{  };
	float cameraPosx{  };
	float cameraPosy{  };

	float cameraDirPosx{ 0.0f };
	float cameraDirPosy{ 0.0f };
	float cameraDirPosz{ 0.0f };

	float lightPosz{  };
	float lightPosx{  };
	float lightPosy{  };

	//ī�޶� ���� vec3��
	glm::vec3 cameraPos{ glm::vec3(cameraPosx, cameraPosy, cameraPosz) };				//--- ī�޶� ��ġ
	glm::vec3 cameraDirection{ glm::vec3(cameraDirPosx, 0.0f, cameraDirPosz) };	//--- ī�޶� �ٶ󺸴� ����
	glm::vec3 cameraUp{ glm::vec3(0.0f, 1.0f, 0.0f) };

public:
	virtual ~scene();

	virtual void init() = 0;											//���⼭ �ʿ��� obj �ε� InitBuffer() ����

	virtual void processKey(unsigned char key, int x, int y) = 0;		//Ű �Է� ó��

	virtual void Update(int value) = 0;									//Timerfunction ����

	virtual void Render() = 0;											//DrawScene ����
};