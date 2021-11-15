#pragma once
#include "scene.h"

class menuScene : public scene {

public:
	virtual ~menuScene() override;

	virtual void init() override;

	virtual void processKey(unsigned char key, int x, int y) override;

	virtual void Update(int value) override;

	virtual void Render(HDC hdc) override;
};