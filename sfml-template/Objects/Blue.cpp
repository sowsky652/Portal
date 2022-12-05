#include "Blue.h"
#include "../FrameWork/Const.h"
#include "../Manager/ResourceMgr.h"

Blue::Blue()
{
	SetResourceTexture("Graphics/blue.png");
	Utils::SetOrigin(sprite, Origins::MC);

	SetPos({ -1000,-1000 });
	hitbox = new RectangleShape;
	hitbox->setFillColor(Color::Red);

	light.setRange(6);
	light.setColor(Color(37, 255, 254));
	//light.setBeamAngle(90);
	light.setBeamWidth(1.5f);
	light.setIntensity(0.3f);
	light.rotate(0);
	light.setScale(Utils::GetSpriteSize(sprite));
	light.castLight(edges.begin(), edges.end());

	edges.emplace_back(sprite.getPosition(),sprite.getPosition());

	////////////////
	portalArray.setPrimitiveType(Quads);
	portalArray.resize(4);

	blueTex = RESOURCEMGR->GetTexture("Graphics/blueportal.png");	

	Vector2f texSize = (Vector2f)blueTex->getSize();

	portalArray[0].texCoords = { 0,0 };
	portalArray[1].texCoords = { texSize.x,0 };
	portalArray[2].texCoords = { texSize.x,texSize.y };
	portalArray[3].texCoords = { 0,texSize.y };
}

Blue::~Blue()
{
	delete hitbox;

}

void Blue::Update(float dt)
{
	Utils::SetOrigin(*hitbox, Origins::BC);
	light.setPosition(sprite.getPosition());
	hitbox->setSize({ sprite.getGlobalBounds().width - 10,sprite.getGlobalBounds().height });
	hitbox->setPosition(sprite.getPosition());

	Translate(direction *dt* projectilespeed);

	hitbox->setPosition(sprite.getPosition());

}

void Blue::Draw(RenderWindow& window)
{
	//SpriteObj::Draw(window);
	DrawPortalArray(window);
	window.draw(light);	
}

void Blue::SetLightDir(int side, bool texdir)
{
	light.setRotation(side);
	texStand = texdir;
}
void Blue::DrawPortalArray(RenderWindow& window)
{
	Vector2f vanishingPoint = window.getView().getCenter();

	frontFace.setPosition(
		sprite.getPosition() - (vanishingPoint - sprite.getPosition()) * (1.f - DEPTH)
	);

	backFace.setPosition(
		sprite.getPosition() + (vanishingPoint - sprite.getPosition()) * (1.f - DEPTH)
	);

	if (dir == 1 || dir == 3)
	{
		portalArray[0].position = backFace.getTransform().transformPoint(backFace.getPoint(0));
		portalArray[1].position = frontFace.getTransform().transformPoint(frontFace.getPoint(1));
		portalArray[2].position = frontFace.getTransform().transformPoint(frontFace.getPoint(2));
		portalArray[3].position = backFace.getTransform().transformPoint(backFace.getPoint(3));
	}

	if (dir == 0 || dir == 2)
	{
		portalArray[0].position = backFace.getTransform().transformPoint(backFace.getPoint(3));
		portalArray[1].position = frontFace.getTransform().transformPoint(frontFace.getPoint(0));
		portalArray[2].position = frontFace.getTransform().transformPoint(frontFace.getPoint(1));
		portalArray[3].position = backFace.getTransform().transformPoint(backFace.getPoint(2));
	}	

	window.draw(portalArray, blueTex);
	//window.draw(backFace);
	//window.draw(frontFace);
}

void Blue::SetSize(Vector2f size)
{
	SpriteObj::SetSize(size);

	float dp = DEPTH * 2 - 1.f;
	if (texStand)
	{
		frontFace.setSize({ 0.1f, size.y / DEPTH });
		backFace.setSize({ 0.1f, size.y * dp });
	}
	else
	{
		frontFace.setSize({ size.x / DEPTH, 0.1f, });
		backFace.setSize({ size.x * dp, 0.1f, });
	}

	Utils::SetOrigin(frontFace, Origins::MC);
	Utils::SetOrigin(backFace, Origins::MC);
}
