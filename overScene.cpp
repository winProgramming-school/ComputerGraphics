#include "stdafx.h"
#include "overScene.h"
#include "stb_image.h"
extern GameFramework GameManager;

overScene::~overScene()
{
    //메모리 해제
    vertices_back.clear();
    vertices_back.shrink_to_fit();
    uvs_back.clear();
    uvs_back.shrink_to_fit();
    normals_back.clear();
    normals_back.shrink_to_fit();

    glDeleteShader(ourShader2.ID);
}

void overScene::InitTexture() {
    ourShader2.use();
    int width;
    int height;
    int numberOfChannel;
    //glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, GL_TEXTURE0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    unsigned char* data1 = stbi_load("over.bmp", &width, &height, &numberOfChannel, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data1);
    glUseProgram(0);

}

void overScene::init()
{
    loadOBJ("wall.obj", vertices_back, uvs_back, normals_back);

 
    ourShader2.InitShader("vertex2.glsl", "fragment2.glsl");      // 텍스처용쉐이더 생성
    ourShader2.use();

    glGenVertexArrays(1, &VAO_back);
    glGenBuffers(2, VBO_back_position);

    //wall 정점버퍼
    glBindVertexArray(VAO_back);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_back_position[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices_back.size() * sizeof(glm::vec3), &vertices_back[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    //wall uv버퍼
    glBindBuffer(GL_ARRAY_BUFFER, VBO_back_position[1]);
    glBufferData(GL_ARRAY_BUFFER, uvs_back.size() * sizeof(glm::vec2), &uvs_back[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(1);

    InitTexture();

    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void overScene::processKey(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':
        glutLeaveMainLoop();
        break;
    case 's':
        if (stage == 1) {
            scene* scene = GameManager.curScene;   ////현재 씬을 tmp에 넣고 지워줌
            GameManager.curScene = new gameScene;
            GameManager.curScene->stage = 1;
            GameManager.curScene->init();
            GameManager.nowscene = GAME; //다시시작
            delete scene;

        }
        else {
            scene* scene = GameManager.curScene;   ////현재 씬을 tmp에 넣고 지워줌
            GameManager.curScene = new gameScene;
            GameManager.curScene->stage = 2;
            GameManager.curScene->init();
            GameManager.nowscene = GAME; //다시시작
            delete scene;
        }

        break;
    }
}

void overScene::Mouse(int button, int state, int x, int y)
{

}
void overScene::MouseMotion(int x, int y)
{

}
void overScene::Update(const float frameTime)
{
   
}

void overScene::Render()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ourShader2.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, GL_TEXTURE0);
    int tLocation1 = glGetUniformLocation(ourShader2.ID, "texture1");
    glUniform1i(tLocation1, 0);
    glBindVertexArray(VAO_back);
    glDrawArrays(GL_TRIANGLES, 0, vertices_back.size());

    glBindVertexArray(0);
    glUseProgram(0);
}