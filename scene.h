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

public:
	virtual ~scene();

	virtual void init() = 0;											//���⼭ �ʿ��� obj �ε� InitBuffer() ����

	virtual void processKey(unsigned char key, int x, int y) = 0;		//Ű �Է� ó��

	virtual void Update(int value) = 0;									//Timerfunction ����

	virtual void Render() = 0;											//DrawScene ����
};