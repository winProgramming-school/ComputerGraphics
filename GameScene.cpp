#include "stdafx.h"
#include <fstream>
extern GameFramework framework;

gameScene::~gameScene()
{
	//메모리 해제
	vertices_sphere.clear();
	vertices_sphere.shrink_to_fit();
	vertices_floor.clear();
	vertices_floor.shrink_to_fit();
	uvs_sphere.clear();
	uvs_sphere.shrink_to_fit();
	uvs_floor.clear();
	uvs_floor.shrink_to_fit();
	normals_sphere.clear();
	normals_sphere.shrink_to_fit();
	normals_floor.clear();
	normals_floor.shrink_to_fit();
	glDeleteShader(ourShader.ID);

	for (int i = 0; i < 10; i++)
		delete[] map[i];
	delete[] map;
}
void gameScene::InitMap() {
	std::ifstream fin{ "map1.txt" };

	map = new int* [3000];
	for (int i = 0; i < 3000; ++i) {
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
	while (fin >> ch && num != 3000) // 파일이 끝날때까지 한 줄씩 읽어오기
	{
		map[num][i] = ch - '0';
		i++;

		if (i % 5 == 0) {
			num++;
			i = 0;
		}
	}

	for (int i = 0; i < 100; ++i) {
		for (int j = 0; j < 5; ++j) {
			std::cout << map[i][j];
		}
		std::cout << std::endl;
	}

	fin.close(); // 파일 닫기
}

void gameScene::init()
{
	ourShader.InitShader("vertex.glsl", "fragment.glsl");		// 쉐이더 생성

//여기에 obj로드코드
	loadOBJ("sphere_.obj", vertices_sphere, uvs_sphere, normals_sphere);

	//여기에 InitBuffer 내용
	ourShader.use();
	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBO_position);

	//ball 정점버퍼
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices_sphere.size() * sizeof(glm::vec3), &vertices_sphere[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	//ball 노멀버퍼
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position[1]);
	glBufferData(GL_ARRAY_BUFFER, normals_sphere.size() * sizeof(glm::vec3), &normals_sphere[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	loadOBJ("MyCube.obj", vertices_floor, uvs_floor, normals_floor);


	glGenVertexArrays(1, &VAO_f);
	glGenBuffers(2, VBO_f_position);

	//floor 정점버퍼
	glBindVertexArray(VAO_f);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_f_position[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices_floor.size() * sizeof(glm::vec3), &vertices_floor[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	//floor 노멀버퍼
	glBindBuffer(GL_ARRAY_BUFFER, VBO_f_position[1]);
	glBufferData(GL_ARRAY_BUFFER, normals_floor.size() * sizeof(glm::vec3), &normals_floor[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	//uniform위치 불러오기
	viewLocation = glGetUniformLocation(ourShader.ID, "viewTransform");
	projectionLocation = glGetUniformLocation(ourShader.ID, "projectionTransform");
	modelLocation = glGetUniformLocation(ourShader.ID, "modelTransform");
	fragColor = glGetUniformLocation(ourShader.ID, "inputColor");
	lightPos = glGetUniformLocation(ourShader.ID, "lightPos");
	lightColor = glGetUniformLocation(ourShader.ID, "lightColor");
	viewPos = glGetUniformLocation(ourShader.ID, "viewPos");

	//투영행렬은 변화 없으므로 미리 설정
	projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_LENGTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	//카메라 위치
	CP.x = 0.0f;
	CP.y = 11.0f;
	CP.z = 11.0f;

	//빛 위치
	LP.x = 1.0f;
	LP.y = 1.5f;
	LP.z = 1.0f;

	//카메라 방향
	CD.x = 0.0f;
	CD.y = 0.0f;
	CD.z = 0.0f;

	//조명을 흰색으로 고정
	glUniform3f(lightColor, 1.0f, 1.0f, 1.0f);

	//조명 위치 초기화
	glUniform3f(lightPos, LP.x, LP.y, LP.z);

	//viewPos(시선벡터) 초기화
	glUniform3f(viewPos, CD.x, CD.y, CD.z);

	InitMap();

	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void gameScene::processKey(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		glutLeaveMainLoop();
		break;
	}
}

void gameScene::Update(const float frametime)
{
	ball.rAngle -= frametime * 250;
	speed += 0.1f;
}

void gameScene::Render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	ourShader.use();

	//카메라 업데이트
	CP.cameraPos = glm::vec3(CP.x, CP.y, CP.z);
	CD.cameraDirection = glm::vec3(CD.x, CD.y, CD.z);
	CP.cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	view = glm::lookAt(CP.cameraPos, CD.cameraDirection, CP.cameraUp);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);



	//여기에 그리기

	//ball
	glBindVertexArray(VAO);
	modelmat = glm::mat4(1.0f);
	modelmat = glm::scale(modelmat, glm::vec3(0.2f, 0.2f, 0.2f));
	modelmat = glm::translate(modelmat, glm::vec3(0.0f, 10.0f, 0.0f));
	modelmat = glm::rotate(modelmat, glm::radians(ball.rAngle), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &modelmat[0][0]);
	glUniform3f(fragColor, 0.8f, 0.619f, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, vertices_sphere.size());

	//floor
	glBindVertexArray(VAO_f);

	for (int i = 0; i < 100; i++) {
		floor_zPos = i * -1.0f + speed;
		for (int j = 0; j < 5; j++) {
			modelmat_f = glm::mat4(1.0f);
			if (j == 0) {
				floor_xPos = -2.0f;
				glUniform3f(fragColor, 1.0f, 0.0f, 0.0f);//빨
			}
			else if (j == 1) {
				floor_xPos = -1.0f;
				glUniform3f(fragColor, 1.0f, 1.0f, 0.0f);//노
			}
			else if (j == 2) {
				floor_xPos = 0.0f;
				glUniform3f(fragColor, 0.8f, 1.0f, 1.0f);//연하늘
			}
			else if (j == 3) {
				floor_xPos = 1.0f;
				glUniform3f(fragColor, 0.0f, 0.99f, 0.0f);//그린
			}
			else if (j == 4) {
				floor_xPos = 2.0f;
				glUniform3f(fragColor, 0.0f, 0.0f, 1.0f);//블루
			}
			//modelmat_f = glm::rotate(modelmat_f, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			modelmat_f = glm::scale(modelmat_f, glm::vec3(3.0f, 0.01f, 3.0f));
			modelmat_f = glm::translate(modelmat_f, glm::vec3(floor_xPos, 0.0f, floor_zPos));
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &modelmat_f[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, vertices_floor.size());

		}
	}


	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glBindVertexArray(0);
	glUseProgram(0);
}