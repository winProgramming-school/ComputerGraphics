#include "stdafx.h"
#include "GameFramework.h"
GameFramework::GameFramework()
{

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
	curScene = new gameScene;	
	nowscene = MENU;
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

float GameFramework::GetTick()
{
	return (float)(curFrameTime - prevFrameTime) / 1000;
}