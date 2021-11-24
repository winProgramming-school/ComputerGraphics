#include "menuScene.h"
#include "stdafx.h"

extern GameFramework framework;

menuScene::~menuScene()
{
	//�޸� ����
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
	ourShader.InitShader("vertex.glsl", "fragment.glsl");		// ���̴� ����
					 											
	//���⿡ obj�ε��ڵ�
	loadOBJ("sphere.obj", vertices_sphere, uvs_sphere, normals_sphere);

	//���⿡ InitBuffer ����
	ourShader.use();
	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBO_position);

	//��������
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices_sphere.size() * sizeof(glm::vec3), &vertices_sphere[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	//��ֹ���
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position[1]);
	glBufferData(GL_ARRAY_BUFFER, normals_sphere.size() * sizeof(glm::vec3), &normals_sphere[0], GL_STATIC_DRAW);
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
	projection = glm::perspective(glm::radians(60.0f), (float)WINDOW_LENGTH / (float)WINDOW_HEIGHT, 0.3f, 100.0f);
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	//������ ���� ������� ����
	glUniform3f(lightColor, 1.0f, 1.0f, 1.0f);

	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void menuScene::processKey(unsigned char key, int x, int y)
{
	switch (key)
	{

	}
}

void menuScene::Update(int value)
{

}

void menuScene::Render()
{
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	//ī�޶� ������Ʈ
	cameraPos = glm::vec3(cameraPosx, cameraPosy, cameraPosz);
	cameraDirection = glm::vec3(cameraDirPosx, 0.0f, cameraDirPosz);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	
	//���� ��ġ ������Ʈ(���� �� �ű�Ÿ� Init���� �Űܵ� �Ǵ� �ڵ�)
	glUniform3f(lightPos, lightPosx, lightPosy, lightPosz);

	//�ٶ󺸴� ����..?
	glUniform3f(viewPos, cameraPosx, cameraPosy, cameraPosz);

	//���⿡ �׸���

	glDrawArrays(GL_TRIANGLES, 0, vertices_sphere.size());

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glBindVertexArray(0);
	glUseProgram(0);
}