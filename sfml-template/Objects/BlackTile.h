#pragma once
#include "SpriteObj.h"
#include <box2d/box2d.h>
#include <array>

class BlackTile : public SpriteObj
{
public:
	BlackTile();
	virtual ~BlackTile();

	void SetOrigin(Origins origin);

	virtual SpriteObj* NewThis();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	virtual void Draw
	(RenderTexture& diffuse, Shader& nShader, RenderTexture& normal);
	void PhysicsUpdate();

	////////////////////////////////////////////////////////////////////////////
	BlackTile(b2World* world, const Vector2f& position, Vector2f dimensions/*bunch of wall size*/, Vector2f box2dposition, bool isEnd);
	b2Body* GetBody() { return body; }
	b2Fixture* GetFixture() { return fixture; }

	void DrawHitbox(RenderWindow& window);
		
	string GetRandTileTex64();
	
	void GetRandDiffuseAndNormal64();
	void SetActiveSideTiles(int pos, bool active);
	void SetActiveSideTiles(array<bool, 4> array);
	void SetSideTilesPosition(RenderWindow& window);
	void DrawSideTiles(RenderWindow& window);
protected:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;

	RectangleShape* hitbox;

	Texture* normal;
	RectangleShape backFace;
	Sprite frontFace;
	array<pair<bool, VertexArray>, 4> sideTiles;
	array<Texture*, 4> tileTextures;
};

