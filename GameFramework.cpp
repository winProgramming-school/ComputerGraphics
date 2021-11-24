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
	//프로그램 끝낼 때 현재 씬도 delete 해주기
	scene* scene = curScene;
	delete scene;
}

void GameFramework::Create()
{
	curScene = new menuScene;	
	nowscene = MENU;
	curScene->init();
}

void GameFramework::OnDraw()
{
	curScene->Render();
}

void GameFramework::OnUpdate(int value)
{
	curScene->Update(value);
	//여기서 현재 씬 업데이트
}

void GameFramework::KeyBoard(unsigned char key, int x, int y)
{
	curScene->processKey(key, x, y);
}

float GameFramework::GetTick()
{
	return (float)(curFrameTime - prevFrameTime) / 1000;
}