#pragma once
#include "SpriteObj.h"
#include <Candle/Candle.hpp>

using namespace candle;

class Blue :public SpriteObj
{
public:
	Blue();
	virtual ~Blue();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	void SetPortalDir(int side) { dir = side; }
	int GetPortalDir() { return dir; }
	void SetLightDir(int side);
protected:
	RectangleShape* hitbox;
	float projectilespeed=2000.f;
	int dir;
	RadialLight light;
	EdgeVector edges;


};

