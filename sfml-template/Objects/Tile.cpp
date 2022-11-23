#include "Tile.h"
#include "../FrameWork/Const.h"
#include "../FrameWork/Framework.h"
#include "../Manager/ResourceMgr.h"
#include "../FrameWork/InputMgr.h"

bool Tile::isPlayingGame = false;

Tile::Tile()	
{
	SetResourceTexture(GetRandTileTex());
	id = '1';
	type = ObjectType::Tile;	
	objSize = ObjectSize::Big;
	attatchedPos = Rotate::Down;
}

Tile::~Tile()
{
	//delete fixture;
	delete hitbox;

}

void Tile::SetOrigin(Origins origin)
{
	SpriteObj::SetOrigin(origin);
	Utils::SetOrigin(backFace, origin);
}

SpriteObj* Tile::NewThis()
{
	return new Tile;
}

void Tile::Update(float dt)
{
	Utils::SetOrigin(*hitbox, Origins::MC);
	sprite.setRotation(body->GetAngle());
	//sprite.setPosition({ body->GetPosition().x,body->GetPosition().y*-1 });
	SetPos({ body->GetPosition().x,body->GetPosition().y * -1 });
	float globalboundcenterx = sprite.getGlobalBounds().left + (sprite.getGlobalBounds().width / 2);
	float globalboundcentery = sprite.getGlobalBounds().top + (sprite.getGlobalBounds().height / 2);

	hitbox->setSize({ sprite.getGlobalBounds().width,sprite.getGlobalBounds().height });
	hitbox->setPosition({ globalboundcenterx,globalboundcentery });
}

void Tile::Draw(RenderWindow& window)
{
	DrawSideTiles(window);
	//window.draw(backFace);
	SpriteObj::Draw(window);
	//window.draw(*hitbox);
}

void Tile::PhysicsUpdate()
{
}

Tile::Tile(b2World* world, const Vector2f& position, Vector2f dimensions)
{
	SetResourceTexture(GetRandTileTex());
	id = '1';

	Utils::SetOrigin(sprite, Origins::MC);

	hitbox = new RectangleShape;
	//hitbox->setFillColor(Color::Red);
	Utils::SetOrigin(*hitbox, Origins::MC);
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y * -1);
	body = world->CreateBody(&bodyDef);

	hitbox->setPosition({ bodyDef.position.x,bodyDef.position.y });
	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x / 2.0f, dimensions.x / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.f;
	fixture = body->CreateFixture(&fixtureDef);

	sprite.setPosition({ body->GetPosition().x, body->GetPosition().y * -1 });
	hitbox->setPosition({ body->GetPosition().x, body->GetPosition().y * -1 });

	type = ObjectType::Tile;

	backFace.setSize({ GRIDSIZE * DEPTH, GRIDSIZE * DEPTH });
	Utils::SetOrigin(backFace, Origins::MC);

	Vector2u texSize = sprite.getTexture()->getSize();

	for (int i = 0; i < sideTiles.size(); i++)
	{
		tileTextures[i] = RESOURCEMGR->GetTexture(GetRandTileTex());
		sideTiles[i].first = true;
		sideTiles[i].second.setPrimitiveType(Quads);
		sideTiles[i].second.resize(4);
		sideTiles[i].second[0].texCoords = { 0.f, 0.f };
		sideTiles[i].second[1].texCoords = { (float)texSize.x, 0.f };
		sideTiles[i].second[2].texCoords = (Vector2f)texSize;
		sideTiles[i].second[3].texCoords = { 0.f, (float)texSize.y };
	}
	backFace.setFillColor(Color::Red);	
}

string Tile::GetRandTileTex()
{
	String str;
	int rand = Utils::RandomRange(0, 5);
	switch (rand)
	{
	case 0:
		str = "Graphics/Tile/tile.png";
		break;
	case 1:
		str = "Graphics/Tile/tile2.png";
		break;
	case 2:
		str = "Graphics/Tile/tile3.png";
		break;
	case 3:
		str = "Graphics/Tile/tile4.png";
		break;
	case 4:
		str = "Graphics/Tile/tile5.png";
		break;
	}

	return str;
}

void Tile::SetActiveSideTiles(int pos, bool active)
{
	sideTiles[pos].first = active;
}

void Tile::SetSideTilesPosition(RenderWindow& window)
{
	//Vector2f vanishingPoint = FRAMEWORK->GetWindow().getView().getCenter();
	Vector2f vanishingPoint = { WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2 };
	backFace.setPosition(
		sprite.getPosition() + (vanishingPoint - sprite.getPosition()) * (1.f - DEPTH)
	);

	FloatRect backRect = backFace.getGlobalBounds();
	FloatRect frontRect = sprite.getGlobalBounds();

	if (sideTiles[0].first)
	{
		sideTiles[0].second[0].position = { backRect.left, backRect.top };
		sideTiles[0].second[1].position = { backRect.left + backRect.width, backRect.top };
		sideTiles[0].second[2].position = { frontRect.left + frontRect.width, frontRect.top };
		sideTiles[0].second[3].position = { frontRect.left, frontRect.top };
	}

	if (sideTiles[1].first)
	{
		sideTiles[1].second[0].position = { frontRect.left + frontRect.width, frontRect.top };
		sideTiles[1].second[1].position = { backRect.left + backRect.width, backRect.top };
		sideTiles[1].second[2].position = { backRect.left + backRect.width, backRect.top + backRect.height };
		sideTiles[1].second[3].position = { frontRect.left + frontRect.width, frontRect.top + frontRect.height };
	}

	if (sideTiles[2].first)
	{
		sideTiles[2].second[0].position = { backRect.left, backRect.top + backRect.height };
		sideTiles[2].second[1].position = { backRect.left + backRect.width, backRect.top + backRect.height };
		sideTiles[2].second[2].position = { frontRect.left + frontRect.width, frontRect.top + frontRect.height };
		sideTiles[2].second[3].position = { frontRect.left , frontRect.top + frontRect.height };
	}

	if (sideTiles[3].first)
	{
		sideTiles[3].second[0].position = { frontRect.left, frontRect.top };
		sideTiles[3].second[1].position = { backRect.left, backRect.top };
		sideTiles[3].second[2].position = { backRect.left, backRect.top + backRect.height };
		sideTiles[3].second[3].position = { frontRect.left , frontRect.top + frontRect.height };
	}
}

void Tile::DrawSideTiles(RenderWindow& window)
{
	SetSideTilesPosition(window);

	for (int i = 0; i < sideTiles.size(); i++)
	{
		if (sideTiles[i].first)
			window.draw(sideTiles[i].second, tileTextures[i]);
	}
}
