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
	//프로그램 끝낼 때 현재 씬도 delete 해주기
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
	//여기서 현재 씬 업데이트
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