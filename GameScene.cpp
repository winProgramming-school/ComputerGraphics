#pragma once

#include "stdafx.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <fstream>
#include"fmod.hpp"
#include"fmod_errors.h"
extern GameFramework GameManager;
using namespace FMOD;

System* fSystem;
Sound* bgSound;
Sound* effectSound[5];
Channel* fChannel[3];

gameScene::~gameScene()
{
	//�޸� ����
	vertices_sphere.clear();
	vertices_sphere.shrink_to_fit();
	vertices_floor.clear();
	vertices_floor.shrink_to_fit();
	vertices_back.clear();
	vertices_back.shrink_to_fit();

	uvs_sphere.clear();
	uvs_sphere.shrink_to_fit();
	uvs_floor.clear();
	uvs_floor.shrink_to_fit();
	uvs_back.clear();
	uvs_back.shrink_to_fit();

	normals_sphere.clear();
	normals_sphere.shrink_to_fit();
	normals_floor.clear();
	normals_floor.shrink_to_fit();
	normals_back.clear();
	normals_back.shrink_to_fit();

	glDeleteShader(ourShader.ID);
	glDeleteShader(ourShader2.ID);


	fSystem->release();
	for (int i = 0; i < 10; i++)
		delete[] map[i];
	delete[] map;
}

void gameScene::SoundSystem() {
	FMOD::System_Create(&fSystem);

	fSystem->init(4, FMOD_INIT_NORMAL, NULL);

	fSystem->createSound("stageBGM.wav", FMOD_LOOP_NORMAL | FMOD_DEFAULT, NULL, &bgSound);
	fSystem->createSound("jump.wav", FMOD_LOOP_OFF | FMOD_DEFAULT, NULL, &effectSound[0]);
	fSystem->createSound("fall.wav", FMOD_LOOP_OFF | FMOD_DEFAULT, NULL, &effectSound[1]);
	fSystem->createSound("crush.wav", FMOD_LOOP_OFF | FMOD_DEFAULT, NULL, &effectSound[2]);
	fSystem->createSound("menu.wav", FMOD_LOOP_OFF | FMOD_DEFAULT, NULL, &effectSound[3]);
	fSystem->createSound("clear.wav", FMOD_LOOP_OFF | FMOD_DEFAULT, NULL, &effectSound[4]);

}

void gameScene::Play(int Sound_num, int cannel) {

	fSystem->playSound(effectSound[Sound_num], NULL, 0, &fChannel[cannel]);
	//fSystem->playSound(bgSound[Sound_num], NULL, 0, Channel);
}
void gameScene::InitMap() {
	std::ifstream fin;
	if (stage == 1) {
		fin.open("map1.txt");
	}
	else {
		fin.open("map2.txt");
	}


	map = new int* [1050];
	for (int i = 0; i < 1050; ++i) {
		map[i] = new int[5];
	}

	if (!fin) {
		std::cout << "Error, no such file exists" << std::endl;
		exit(100);
	}
	int num = 0;
	char ch;
	int tmp;
	int i = 0;
	while (fin >> ch && num != 1050) // ������ ���������� �� �پ� �о����
	{
		map[num][i] = ch - '0';
		i++;

		if (i % 5 == 0) {
			num++;
			i = 0;
		}
	}

	//for (int i = 0; i < 100; ++i) {
	//   for (int j = 0; j < 5; ++j) {
	//      std::cout << map[i][j];
	//   }
	//   std::cout << std::endl;
	//}

	fin.close(); // ���� �ݱ�
}
void gameScene::InitTexture() {
	ourShader2.use();
	glActiveTexture(GL_TEXTURE0);
	int width;
	int height;
	int numberOfChannel;
	//glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data1 = stbi_load("1.bmp", &width, &height, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data1);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data2 = stbi_load("clear.bmp", &width, &height, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data2);


	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data3 = stbi_load("over.bmp", &width, &height, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data3);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data3);

}
void gameScene::init()
{

	SoundSystem();
	fSystem->playSound(bgSound, NULL, 0, &fChannel[0]);
	fChannel[1]->setPaused(true);
	fChannel[2]->setPaused(true);
	ourShader.InitShader("vertex.glsl", "fragment.glsl");      // ���̴� ����

	//���⿡ obj�ε��ڵ�
	loadOBJ("sphere_.obj", vertices_sphere, uvs_sphere, normals_sphere);
	loadOBJ("term_ob1.obj", vertices_ob1, uvs_ob1, normals_ob1);
	loadOBJ("MyCube.obj", vertices_floor, uvs_floor, normals_floor);
	loadOBJ("wall.obj", vertices_back, uvs_back, normals_back);

	//���⿡ InitBuffer ����
	ourShader.use();
	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBO_position);
	//ball ��������
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices_sphere.size() * sizeof(glm::vec3), &vertices_sphere[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	//ball ��ֹ���
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position[1]);
	glBufferData(GL_ARRAY_BUFFER, normals_sphere.size() * sizeof(glm::vec3), &normals_sphere[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	glGenVertexArrays(1, &VAO_f);
	glGenBuffers(2, VBO_f_position);
	//floor ��������
	glBindVertexArray(VAO_f);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_f_position[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices_floor.size() * sizeof(glm::vec3), &vertices_floor[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	//floor ��ֹ���
	glBindBuffer(GL_ARRAY_BUFFER, VBO_f_position[1]);
	glBufferData(GL_ARRAY_BUFFER, normals_floor.size() * sizeof(glm::vec3), &normals_floor[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	glGenVertexArrays(1, &VAO_ob1);
	glGenBuffers(2, VBO_ob1_position);
	//��ֹ�1(����) ��������
	glBindVertexArray(VAO_ob1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_ob1_position[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices_ob1.size() * sizeof(glm::vec3), &vertices_ob1[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	//��ֹ�1(����) ��ֹ���
	glBindBuffer(GL_ARRAY_BUFFER, VBO_ob1_position[1]);
	glBufferData(GL_ARRAY_BUFFER, normals_ob1.size() * sizeof(glm::vec3), &normals_ob1[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	//uniform��ġ �ҷ�����
	viewLocation = glGetUniformLocation(ourShader.ID, "viewTransform");
	projectionLocation = glGetUniformLocation(ourShader.ID, "projectionTransform");
	modelLocation = glGetUniformLocation(ourShader.ID, "modelTransform");
	fragColor = glGetUniformLocation(ourShader.ID, "inputColor");
	lightPos = glGetUniformLocation(ourShader.ID, "lightPos");
	lightColor = glGetUniformLocation(ourShader.ID, "lightColor");
	viewPos = glGetUniformLocation(ourShader.ID, "viewPos");

	//��������� ��ȭ �����Ƿ� �̸� ����
	projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_LENGTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	//ī�޶� ��ġ

	CP.x = 0.0f;
	CP.y = 5.0f;
	CP.z = 15.0f;

	//�� ��ġ
	LP.x = 1.0f;
	LP.y = 1.5f;
	LP.z = 1.0f;

	//ī�޶� ����
	CD.x = 0.0f;
	CD.y = 0.0f;
	CD.z = 0.0f;

	//����
	lifePoint = 3;

	//������ ������� ����
	glUniform3f(lightColor, 1.0f, 1.0f, 1.0f);

	//���� ��ġ �ʱ�ȭ
	glUniform3f(lightPos, LP.x, LP.y, LP.z);

	//viewPos(�ü�����) �ʱ�ȭ
	glUniform3f(viewPos, CD.x, CD.y, CD.z);

	InitMap();

	//���⼭���� �ؽ�ó
	ourShader2.InitShader("vertex2.glsl", "fragment2.glsl");      // �ؽ�ó�뽦�̴� ����
	ourShader2.use();

	glGenVertexArrays(1, &VAO_back);
	glGenBuffers(2, VBO_back_position);

	//wall ��������
	glBindVertexArray(VAO_back);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_back_position[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices_back.size() * sizeof(glm::vec3), &vertices_back[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	//wall uv����
	glBindBuffer(GL_ARRAY_BUFFER, VBO_back_position[1]);
	glBufferData(GL_ARRAY_BUFFER, uvs_back.size() * sizeof(glm::vec2), &uvs_back[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	//viewLocation2 = glGetUniformLocation(ourShader2.ID, "viewTransform");
	//projectionLocation2 = glGetUniformLocation(ourShader2.ID, "projectionTransform");
	//modelLocation2 = glGetUniformLocation(ourShader2.ID, "modelTransform");
	//glUniformMatrix4fv(projectionLocation2, 1, GL_FALSE, &projection[0][0]);
	//glUniformMatrix4fv(viewLocation2, 1, GL_FALSE, glm::value_ptr(view));

	InitTexture();

	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void gameScene::drawModel() {

	ourShader.use();

	//ball
	glBindVertexArray(VAO);
	modelmat = glm::mat4(1.0f);
	modelmat = glm::translate(modelmat, glm::vec3(ball.x + mouse.move, ball.y, 0.0f));
	modelmat = glm::rotate(modelmat, glm::radians(ball.rAngle), glm::vec3(1.0f, 0.0f, 0.0f));
	modelmat = glm::scale(modelmat, glm::vec3(0.12f, 0.12f, 0.12f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &modelmat[0][0]);
	glUniform3f(fragColor, ball.r, ball.g, ball.b);
	glDrawArrays(GL_TRIANGLES, 0, vertices_sphere.size());

	//floor
	glBindVertexArray(VAO_f);

	int end = index + 100;
	if (index >= 920) {
		end = 1050;
	}

	for (int i = index; i < end; i++) {
		floor_zPos = i * -1.0f + speed;
		for (int j = 0; j < 5; j++) {
			modelmat_f = glm::mat4(1.0f);

			//�ʰ� ����
			if (map[i][j] == 0) {//0 : base (�⺻ ��)

				glUniform3f(fragColor, 0.8f, 1.0f, 1.0f);//���ϴ�
				sizeOfWallx = 3.0f;
				sizeOfWally = 0.01f;
				sizeOfWallz = 3.0f;
			}
			else if (map[i][j] == 1) {//1 : ��ֹ�(������ ����)
				glUniform3f(fragColor, 0.8f, 0.0f, 0.0f);
				sizeOfWallx = 3.0f;
				sizeOfWally = 2.0f;
				sizeOfWallz = 3.0f;
			}
			else if (map[i][j] == 2) {//2 : ��, �����̰�
				glUniform3f(fragColor, 0.4f, 0.4f, 0.4f);
				sizeOfWallx = 3.0f;
				sizeOfWally = obstacle_y[j];
				sizeOfWallz = 3.0f;
			}
			else if (map[i][j] == 3) {//3 : ���� ����

				glUniform3f(fragColor, 0.0f, 0.0f, 1.0f);//���
				sizeOfWallx = 3.0f;
				sizeOfWally = 0.01f;
				sizeOfWallz = 3.0f;
			}
			else if (map[i][j] == 4) {//4 : �� ����
				glUniform3f(fragColor, 0.0f, 0.0f, 0.0f);
				sizeOfWallx = 3.0f;
				sizeOfWally = 0.00f;
				sizeOfWallz = 3.0f;
			}
			else {
				glUniform3f(fragColor, 1.0f, 1.0f, 1.0f);
				sizeOfWallx = 3.0f;
				sizeOfWally = 0.01f;
				sizeOfWallz = 3.0f;
			}

			if (j == 0) {
				floor_xPos = -2.0f;
			}
			else if (j == 1) {
				floor_xPos = -1.0f;
			}
			else if (j == 2) {
				floor_xPos = 0.0f;
			}
			else if (j == 3) {
				floor_xPos = 1.0f;
			}
			else if (j == 4) {
				floor_xPos = 2.0f;
			}

			modelmat_f = glm::scale(modelmat_f, glm::vec3(sizeOfWallx, sizeOfWally, sizeOfWallz));
			modelmat_f = glm::translate(modelmat_f, glm::vec3(floor_xPos, 0.0f, floor_zPos));

			//if (map[i][j] == 1) {
			//    glm::vec4 tmp;
			//    float max_z{};
			//    float max_x{};
			//    float max_y{};
			//    float min_z{};
			//    float min_y{};
			//    float min_x{};
			//    tmp = modelmat_f * glm::vec4(vertices_floor[0], 1);
			//    max_x = tmp.x;
			//    min_x = tmp.x;
			//    min_z = tmp.z;
			//    max_z = tmp.z;
			//    for (int i = 1; i < vertices_floor.size(); ++i) {
			//        tmp = modelmat_f * glm::vec4(vertices_floor[i], 1);
			//        max_x = (max_x < tmp.x) ? tmp.x : max_x;
			//        max_z = (max_z < tmp.z) ? tmp.z : max_z;
			//        min_x = (min_x > tmp.x) ? tmp.x : min_x;
			//        min_z = (min_z > tmp.z) ? tmp.z : min_z;
			//    }
			//    float center_x = (max_x + min_x) / 2;
			//    float center_z = (max_z + min_z) / 2;
			//    float length_x = (max_x - min_x) / 2;
			//}


			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &modelmat_f[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, vertices_floor.size());
		}
	}
}
void gameScene::processKey(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		glutLeaveMainLoop();
		break;
	case 'c':
		overStage = false;
		clearStage = true;
		break;
		//case 'o':
		//	clearStage = false;
		//	overStage = true;
		//	break;
	case 'r':
		ball.Init();
		speed = 0;
		index = 0;
		lifePoint = 3;
		break;
	case 'p':
		if (pause) {
			pause = false;
		}
		else {
			pause = true;
		}
		break;
	case 't':
		if (testmode) {
			testmode = false;
		}
		else {
			testmode = true;
		}
		break;
	case 'v':
		index = 920;
		speed = 930;
		break;
	}
}

void gameScene::Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (mouse.mouse_down) {
			mouse.mouse_down = false;
			mouse.x = x;
			mouse.y = y;
		}
	}


	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		mouse.mouse_down = true;
		ball.x += mouse.move;
		mouse.move = 0.0f;
	}
}

void gameScene::MouseMotion(int x, int y)
{
	mouse.move = (x - mouse.x) / 50;
}

void gameScene::Update(const float frametime)
{
	// ���� ���������� update �ߴ�
	if (pause) {
		return;
	}

	if (!ball.falling) {
		//�ε��� ����
		if ((int)speed > 10) {
			index = (int)speed - 10;
		}
		if (speed >= 1030) {
			clearStage = true;
			fChannel[0]->setPaused(true);
		}
		if (ball.rAngle >= 360.0f) {      //ȸ�� ���� ���� ���� ����
			ball.rAngle = 0.0f;
		}

		ball.rAngle += frametime * 250;

		// ���� �̵�
		speed += 10 * frametime;
	}

	// ����� Ball Jump �ڵ�
	if (ball.isJump) {         //���� ������ ��Ҵٸ�
		Play(0, 1);
		ball.y -= GRAVITY * frametime * 2;
	}
	else {                  //���� ���°� �ƴϰ� �ٴڰ� ������� �ʴٸ� �߷� ��� �ۿ�
		if (ball.y > 1.3f || ball.falling)
			ball.y += GRAVITY * frametime * 2;
		else
			ball.y = 0.8f;
	}

	if (ball.y >= 8.0f) {      //���� �ְ� ���� �޼� �� �������� ����
		ball.isJump = false;
	}

	if (testmode) {
		return;
	}

	// �����̴� ��ֹ� update
	for (int i = 0; i < 5; ++i) {
		if (obstacle_y[i] >= 5.0f && obstacle_up[i]) {
			obstacle_up[i] = false;
		}
		if (obstacle_y[i] <= 0.25f && !obstacle_up[i]) {
			obstacle_up[i] = true;
		}
		if (obstacle_up[i]) {
			obstacle_y[i] += obstacle_speed[i] * frametime;
		}
		else {
			obstacle_y[i] -= obstacle_speed[i] * frametime;
		}
	}

	if (ball.y <= -8.0f) {     // �������� �ֱ�
		lifePoint = 0;
	}

	if (lifePoint == 0)			//������ �� �پ���
	{
		Play(1, 1);
		fChannel[0]->setPaused(true);
		overStage = true;
	}

	// ���� ���� ��ֹ� �浹
	for (int i = 0; i < 5; ++i) {
		float center_x = -6.0f + i * 3.0f;
		float center_z = ((index + 10.0f) * -1.0f + speed) * 3;

		// ���� ����
		if (map[index + 10][i] == 3) {
			if (center_x - 1.5f <= ball.x + mouse.move && center_x + 1.5 >= ball.x + mouse.move && ball.y <= 1.3f && ball.y >= 0.7f) {
				ball.isJump = true;
			}
		}

		// ��ֹ�
		else if (map[index + 10][i] == 1) {
			float distance = (center_x - (ball.x + mouse.move)) * (center_x - (ball.x + mouse.move));
			if (sqrt(distance) < 1.5f + 0.8f && (ball.y - 0.8f) <= 2.0f) {
				Play(2, 1);
				ball.r = 0.0f;
				ball.g = 1.0f;
				ball.b = 0.0f;
				lifePoint -= 1;

			}
		}

		// �� ����
		else if (map[index + 10][i] == 4) {
			if (center_x - 1.5f <= ball.x + mouse.move && center_x + 1.5 >= ball.x + mouse.move && ball.y <= 1.3f && ball.y >= 0.7f) {
				ball.falling = true;
			}
		}

		// �����̴� ��ֹ�
		else if (map[index + 10][i] == 2) {
			float distance = (center_x - (ball.x + mouse.move)) * (center_x - (ball.x + mouse.move));
			if (sqrt(distance) < 1.5f + 0.8f && (ball.y - 0.8f) <= obstacle_y[i]) {
				Play(2, 1);
				ball.r = 0.0f;
				ball.g = 1.0f;
				ball.b = 1.0f;
				lifePoint -= 1;
			}
		}
	}


}

void gameScene::Render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	ourShader.use();

	//����ȭ��
	CP.cameraPos = glm::vec3(CP.x, CP.y, CP.z);
	CD.cameraDirection = glm::vec3(CD.x, CD.y, CD.z);
	CP.cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	view = glm::lookAt(CP.cameraPos, CD.cameraDirection, CP.cameraUp);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	glViewport(0, 0, WINDOW_LENGTH, WINDOW_HEIGHT);
	drawModel();

	//�̴ϸ�
	CP.cameraPos = glm::vec3(CP.x, CP.y + 12.0f, CP.z - 4.0f);
	CD.cameraDirection = glm::vec3(CD.x, CD.y, CD.z);
	CP.cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	view = glm::lookAt(CP.cameraPos, CD.cameraDirection, CP.cameraUp);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	glViewport(WINDOW_LENGTH - 100, WINDOW_HEIGHT - 100, WINDOW_LENGTH / 8, WINDOW_HEIGHT / 8);
	drawModel();

	CP.cameraPos = glm::vec3(CP.x, CP.y, CP.z);
	CD.cameraDirection = glm::vec3(CD.x, CD.y, CD.z);
	CP.cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	view = glm::lookAt(CP.cameraPos, CD.cameraDirection, CP.cameraUp);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	glViewport(0, 0, WINDOW_LENGTH, WINDOW_HEIGHT);

	if (clearStage) {
		fChannel[0]->setPaused(true);
		Play(4, 2);
		scene* scene = GameManager.curScene;   ////���� ���� tmp�� �ְ� ������
		GameManager.curScene = new clearScene;
		GameManager.curScene->init();
		if (stage == 1) {
			GameManager.curScene->stage = 1;
		}
		else if (stage == 2) {
			GameManager.curScene->stage = 2;
		}

		GameManager.nowscene = CLEAR; //�ٽý���
		delete scene;
	}

	else if (overStage) {
		fChannel[0]->setPaused(true);
		if (ball.falling) {}
		else Play(3, 2);
		scene* scene = GameManager.curScene;   ////���� ���� tmp�� �ְ� ������
		GameManager.curScene = new overScene;
		GameManager.curScene->init();
		if (stage == 1) {
			GameManager.curScene->stage = 1;
		}
		else if (stage == 2) {
			GameManager.curScene->stage = 2;
		}
		GameManager.nowscene = OVER; //�ٽý���
		delete scene;
	}

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glBindVertexArray(0);
	glUseProgram(0);
}