#include "stdafx.h"
#include "MenuScene.h"

extern GameFramework GameManager;

menuScene::~menuScene()
{
	//메모리 해제
	vertices_sphere.clear();
	vertices_sphere.shrink_to_fit();
	uvs_sphere.clear();
	uvs_sphere.shrink_to_fit();
	normals_sphere.clear();
	normals_sphere.shrink_to_fit();
	glDeleteShader(ourShader.ID);
}

void menuScene::init()
{
	ourShader.InitShader("vertex.glsl", "fragment.glsl");		// 쉐이더 생성
					 											
	//여기에 obj로드코드
	loadOBJ("sphere_.obj", vertices_sphere, uvs_sphere, normals_sphere);

	//여기에 InitBuffer 내용
	ourShader.use();
	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBO_position);

	//정점버퍼
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices_sphere.size() * sizeof(glm::vec3), &vertices_sphere[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	//노멀버퍼
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position[1]);
	glBufferData(GL_ARRAY_BUFFER, normals_sphere.size() * sizeof(glm::vec3), &normals_sphere[0], GL_STATIC_DRAW);
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
	projection = glm::perspective(glm::radians(60.0f), (float)WINDOW_LENGTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	//조명의 색은 흰색으로 고정
	glUniform3f(lightColor, 1.0f, 1.0f, 1.0f);

	CP.x = 0.0f;
	CP.y = 0.0f;
	CP.z = 10.0f;

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

	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void menuScene::processKey(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		glutLeaveMainLoop();
		break;
	case 's':
		scene * scene = GameManager.curScene;   ////현재 씬을 tmp에 넣고 지워줌
		GameManager.curScene = new gameScene;
		GameManager.curScene->init();
		GameManager.nowscene = GAME;
		delete scene;
		break;
	}
}

void menuScene::Mouse(int button, int state, int x, int y)
{

}
void menuScene::MouseMotion(int x, int y)
{

}
void menuScene::Update(const float frameTime)
{
	if (balljump_count >= 100 && !ballJump) {
		balljump_count = 0;
		ballJump = true;
	}
	balljump_count++;

	if (ballJump) {			//점프 발판을 밟았다면
		ball_y -= GRAVITY * frameTime;
	}
	else {						//점프 상태가 아니고 바닥과 닿아있지 않다면 중력 계속 작용
		if (ball_y > -1.0f)
			ball_y += GRAVITY * frameTime/ (1.5f);
	}

	if (ball_y >= 4.0f) {		//점프 최고 높이 달성 시 떨어지게 만듦
		ballJump = false;
	}
}

void menuScene::Render()
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
	view = glm::lookAt(CP.cameraPos, CD.cameraDirection, CP.cameraUp);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	

	//여기에 그리기

	glBindVertexArray(VAO);
	modelmat = glm::mat4(1.0f);
	modelmat = glm::translate(modelmat, glm::vec3(3.0f, ball_y, 0.0f));
	modelmat = glm::scale(modelmat, glm::vec3(0.1f, 0.1f, 0.1f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &modelmat[0][0]);
	glUniform3f(fragColor, 0.8f, 0.619f, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, vertices_sphere.size());

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glBindVertexArray(0);
	glUseProgram(0);
}