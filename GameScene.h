#pragma once
#include "scene.h"
class gameScene : public scene {

public:
	virtual ~gameScene() override;

	virtual void init() override;

	virtual void processKey(unsigned char key, int x, int y) override;

	virtual void Update(int value) override;

	virtual void Render() override;
};