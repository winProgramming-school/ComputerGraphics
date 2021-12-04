#include "stdafx.h"
#include "GameFramework.h"
GameFramework::GameFramework()
{
	curScene = new menuScene;
	nowscene = MENU;
	prevFrameTime = 0.0f;
	curFrameTime = 0.0f; 
}

GameFramework::~GameFramework()
{

}

void GameFramework::Reset()
{

}

void GameFramework::Clear()
{
	//���α׷� ���� �� ���� ���� delete ���ֱ�
	scene* scene = curScene;
	delete scene;
}

void GameFramework::Create()
{

	curScene->init();
}

void GameFramework::OnDraw()
{
	curScene->Render();
}

void GameFramework::OnUpdate(const float frameTime)
{
	curScene->Update(frameTime);
	//���⼭ ���� �� ������Ʈ
}

void GameFramework::KeyBoard(unsigned char key, int x, int y)
{
	curScene->processKey(key, x, y);
}
void GameFramework::Mouse(int button, int state, int x, int y)
{
	curScene->Mouse(button, state, x, y);
}
void GameFramework::MouseMotion(int x, int y)
{
	curScene->MouseMotion(x, y);
}
float GameFramework::GetTick()
{
	return (float)(curFrameTime - prevFrameTime) / 1000;
}