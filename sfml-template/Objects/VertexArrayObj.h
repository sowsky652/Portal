#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <string>

using namespace std;
using namespace sf;

enum class Origins;
class VertexArrayObj
{
public:	
	VertexArrayObj(Sprite& front, Sprite& pivot);

	void SetRotatable(bool rot);
	void SetDepth(float dp);
	void SetAllSidesTex(string id);	
	void SetSidesTex(string id, int rot);
	void SetBackFaceOrigin(Origins origin);
	void SetBackFaceOrigin(Vector2f o);
	void SetBackFaceSize(Vector2f size);	
	
	void ChageCoords(Vector2u texSize);
	void ReturnPrevCoords();
	void SetTransparent(int color);

	void Update();
	void Draw(RenderWindow& window);
	void DrawHalf(RenderWindow& window);
	void DrawRenderStates(RenderWindow& window);
	void SetActiveSides(int rot, bool active);
	RectangleShape& GetBackFace() { return backFace; }
	RenderStates* GetRenderStates() { return &state; }
private:
	array<pair<bool, VertexArray>, 4> sides;
	array<Texture*, 4> tileTextures;

	RectangleShape backFace;
	Sprite& frontFace;
	Sprite& pivotSprite;
	Vector2u texSize;

	array<Vector2f, 4> frtEdgePoses;
	array<Vector2f, 4> backEdgePoses;
	RenderStates state;


	bool rotatable = true;
	float depth;
};

