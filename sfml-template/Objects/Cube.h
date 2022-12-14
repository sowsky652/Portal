#pragma once
#include "SpriteObj.h"
#include "box2d/box2d.h"
#include "../Shader/Wave.h"

enum class State
{
	None = -1,
	Normal,
	Destroy,
	Reproduction,
};

class Cube : public SpriteObj
{
public:
	Cube();
	virtual ~Cube();

	virtual SpriteObj* NewThis();
	bool GetGround() { return ground; }
	void SetGround(bool a) { ground = a; }
	FloatRect GethitboxGlobalBounds() { return hitbox->getGlobalBounds(); }
	void ChangeBodyTypeBetweenStaticAndDynamic(bool b);

	virtual void Update(float dt);
	void PhysicsUpdate();

	virtual void Draw(RenderWindow& window);
	virtual void Draw
	(RenderTexture& diffuse, Shader& nShader, RenderTexture& normal);
	void SetSide(bool s);
	bool GetSide() { return side; }
	void SetCubeBodyPos(Vector2f pos);
	void SetCubeBodyForce(b2Vec2 force);
	void MovetoStartpos();
	b2Vec2 GetCubeBodyForce() { return body->GetLinearVelocity(); }

	/////////////////////////////////////////////////////////////////////////
	Cube(b2World* world, const Vector2f& position, Vector2f dimensions);
	b2Body* GetBody() { return body; }
	b2Fixture* GetFixture() { return fixture; }	
	
	Vector2f GetRecentSpeed() { return maxspeed; }

	void SetGravity(int g) { body->SetGravityScale(g); }
	void Respawn();
	////////////////
	void SetNormalStateTex();
	void InitDestroy();
	void UpdateDestroyAnimation(float dt);
protected:
	bool ground = false;
	RectangleShape* hitbox;
	float verticalspeed = 0.f;
	float addspeed = 50;
	bool side=false; //false=left true=right
	bool grab = false;
	Vector2f startpos;

	float speedtX = 0.f;
	float speedtY = 0.f;
	float maximumspeed = 18.f;

	Vector2f maxspeed;
	///////////////////////////////////////////////////////////////////////
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;

	VertexArrayObj sideFaces;
	Sprite frontFace;
	Vector2f frontSize;
	Texture* normal;


	Wave shader;
	Texture* destroy;
	State cubeState = State::Normal;
	int cubeTransp = 255;
};

