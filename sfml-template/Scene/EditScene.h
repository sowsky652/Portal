#pragma once
#include "SFML/Graphics.hpp"
#include "Scene.h"
#include "../FrameWork/Utils.h"
#include <vector>
#include <array>

class SpriteObj;
class EditScene : public Scene
{
public:
	EditScene();
	~EditScene();

	virtual void Init();	// ����
	virtual void Release();		// ����

	virtual void Enter();
	virtual void Exit();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	
public:
	void InitTool();	
	void SetToolPos();
	void SetToolSize();
	void Input(float dt);
	void DrawOutLine(RenderWindow& window);

	void InitUiTool();
	void SetUiToolPos(Vector2f pos);
private:	
	int rowNum;
	int colNum;
	Vector2f startPos;

	array<array<list<SpriteObj*>, 100>, 100> mapArray;

	RectangleShape topLine;
	RectangleShape leftLine;
	RectangleShape rightLine;
	RectangleShape bottomLine;	
	
	array<array<pair<SpriteObj*, Sprite>, 4>, 8> uiTool;
	Sprite uiOutLine;
	RectangleShape uiBackGround;
	Sprite uiMove;

	bool isScenePlay;

	int zoomCount;	

	bool isUiMoving;
};

