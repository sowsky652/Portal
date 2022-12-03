#pragma once
#include "SpriteObj.h"
#include <list>
using namespace std;

//class NumBox;

struct Wire
{
	VertexArray wire;
	int buttonNum;
	bool isConnected;
};

enum class Phase
{
	None = -1,
	CatcherSelect,
	TriggerSelect
};

class WireableObject : public SpriteObj
{
public:
	WireableObject();
	virtual ~WireableObject();

	virtual void Init();

	virtual void Update(float dt);
	virtual void Update(float dt, Vector2f mouse);
	virtual void Draw(RenderWindow& window);
public:
	virtual void SetWireCheckBox();
	virtual void WireModDraw(RenderWindow& window);
	void DrawWire(RenderWindow& window);

	//void AddNumBox(NumBox* nb);
	//void AddNumBox(int num);
	//void RemoveNumBox();

	list<int> GetWireListFromMapTool();

	//list<int>& GetWireNum() { return wireNum; }

	bool IsMouseIn() { return isMouseIn; }
	static void SetPhase(Phase p) { phase = p; }
	static Phase GetPhase() { return phase; }

protected:
	RectangleShape wireCheckBox;

	bool isMouseIn;
	//list<NumBox*> numbox;
	//list<int> wireNum;

	static Phase phase;

	list<Wire*> wires;

	Texture* orange;
	Texture* blue;

};

