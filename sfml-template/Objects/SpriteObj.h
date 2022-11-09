#pragma once
#include "Object.h"
#include "../FrameWork/Utils.h"
#include <string>

class SpriteObj : public Object
{
public:
	SpriteObj();
	virtual ~SpriteObj();

	void SetOrigin(Origins origin);
	virtual void SetPos(const Vector2f& pos);

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
public:
	void SetResourceTexture(String id);
	void SetUiTexture(String id);
	Sprite* GetSprite();
	void SetScale(Vector2f scale);
protected:
	Sprite sprite;
	float speed;
	float vecity;
	Vector2f direction;

	char id;
};

