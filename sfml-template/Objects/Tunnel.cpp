#include "Tunnel.h"
#include "../FrameWork/stdafx.h"
#include "../FrameWork/InputMgr.h"

Tunnel::Tunnel()
{
	SetResourceTexture("Graphics/temp/tunneltool.png");
	id = 't';

	objSize = ObjectSize::Normal;

	type = ObjectType::Catcher;

}

Tunnel::Tunnel(const Vector2f& position, int dir, vector<int> buttonlist, bool Isblue, bool active, int connected)
	:IsBlue(Isblue), dir(dir), active(active), connected(connected)
{
	if (Isblue)
		tuns.setFillColor(Color(BLUE, 50));
	else {
		tuns.setFillColor(Color(ORANGE, 50));
	}
	Utils::SetOrigin(start, Origins::MC);
	start.setFillColor(Color(0, 255, 0, 255));

	buttonid = buttonlist;

	if (dir == 0 || dir == 2) {
		if (dir == 0) {
			Utils::SetOrigin(tuns, Origins::TC);
			startpos = { position.x, position.y - GRIDSIZE / 2 };
			tuns.setPosition(startpos);
		}
		else if (dir == 2) {
			Utils::SetOrigin(tuns, Origins::BC);
			startpos = { position.x,position.y + GRIDSIZE / 2 };
			tuns.setPosition(startpos);
		}
		tuns.setSize({ 50,0 });
		start.setSize({ 50,10 });
	}
	else {
		if (dir == 1) {
			Utils::SetOrigin(tuns, Origins::MR);
			startpos = { position.x + GRIDSIZE / 2,position.y };
			tuns.setPosition(startpos);
		}
		else if (dir == 3) {
			Utils::SetOrigin(tuns, Origins::ML);
			startpos = { position.x - GRIDSIZE / 2 ,position.y };
			tuns.setPosition(startpos);

		}
		tuns.setSize({ 0,50 });
		start.setSize({ 10,50 });

	}
	start.setPosition(startpos);

	particles.setPrimitiveType(Points);
	switch (this->dir)
	{
	case 0:
		particleDir = { 0.f, 1.f };
		break;
	case 1:
		particleDir = { -1.f, 0.f };
		break;
	case 2:
		particleDir = { 0.f, -1.f };
		break;
	case 3:
		particleDir = { 1.f, 0.f };
		break;
	}
}

Tunnel::~Tunnel()
{
	/*for (auto v : button) {
		delete v;
	}*/
	button.clear();
}


void Tunnel::Update(float dt)
{
	Utils::SetOrigin(start, Origins::MC);

	active = true;

	for (auto b : button) {
		if (!b->GetPressed()) {
			active = false;
			destiny.setPosition(startpos);
			return;
		}
	}
	//active door

	if (!active) {
		if (dir == 0 || dir == 2) {
			if (dir == 0) {
				Utils::SetOrigin(tuns, Origins::TC);
				tuns.setPosition(startpos);
			}
			else if (dir == 2) {
				Utils::SetOrigin(tuns, Origins::BC);
				tuns.setPosition(startpos);
			}
			tuns.setSize({ 50,0 });
		}
		else {
			if (dir == 1) {
				Utils::SetOrigin(tuns, Origins::MR);
				tuns.setPosition(startpos);
			}
			else if (dir == 3) {
				Utils::SetOrigin(tuns, Origins::ML);
				tuns.setPosition(startpos);

			}
			tuns.setSize({ 0,50 });
		}
		hitbox.setSize(tuns.getSize());
		hitwall = false;

		return;
	}

	if (!hitwall) {
		if (dir == 0 || dir == 2) {
			tuns.setSize({ tuns.getSize().x,tuns.getSize().y + 100 });
			if (dir == 0) {
				Utils::SetOrigin(tuns, Origins::TC);
			}
			else if (dir == 2) {
				Utils::SetOrigin(tuns, Origins::BC);

			}
		}
		else {
			tuns.setSize({ tuns.getSize().x + 100,tuns.getSize().y });
			if (dir == 1) {
				Utils::SetOrigin(tuns, Origins::MR);

			}
			else if (dir == 3) {
				Utils::SetOrigin(tuns, Origins::ML);
			}

		}
		AddParticle();
	}
	else if (hitwall && whohitwall != nullptr) {
		if (dir == 0) {
			tuns.setSize({ tuns.getSize().x,whohitwall->GetGlobalBounds().top - tuns.getPosition().y });
		}
		else if (dir == 2) {
			Utils::SetOrigin(tuns, Origins::BC);
			tuns.setSize({ tuns.getSize().x,tuns.getPosition().y - (whohitwall->GetGlobalBounds().top + whohitwall->GetGlobalBounds().height) });

		}
		else if (dir == 1) {
			Utils::SetOrigin(tuns, Origins::MR);

			tuns.setSize({ tuns.getPosition().x - (whohitwall->GetGlobalBounds().left + whohitwall->GetGlobalBounds().width),tuns.getSize().y });

		}
		else if (dir == 3) {
			Utils::SetOrigin(tuns, Origins::ML);

			tuns.setSize({ (whohitwall->GetGlobalBounds().left) - tuns.getPosition().x,tuns.getSize().y });

		}

		Utils::SetOrigin(destiny, Origins::MC);
		if (dir == 0 || dir == 2) {
			destiny.setSize({ tuns.getSize().x,10 });
			if (dir == 0)
				endpos = { tuns.getPosition().x,tuns.getPosition().y + tuns.getSize().y };
			else if (dir == 2)
				endpos = { tuns.getPosition().x,tuns.getPosition().y - tuns.getSize().y };
		}
		else if (dir == 1 || dir == 3) {
			destiny.setSize({ 10,tuns.getSize().y });
			if (dir == 1)
				endpos = { tuns.getPosition().x - tuns.getSize().x ,tuns.getPosition().y, };
			else if(dir==3)
				endpos={ tuns.getPosition().x + tuns.getSize().x ,tuns.getPosition().y, };

		}
	}

	destiny.setPosition(endpos);
	tuns.setPosition(startpos);
	hitbox.setSize(tuns.getSize());
	hitbox.setOrigin(tuns.getOrigin());
	hitbox.setPosition(tuns.getPosition());

	if ((hitwall && whohitwall != nullptr) && active)
	{
		SetParticlePos();
		TransParticles(dt);
	}
}

void Tunnel::Draw(RenderWindow& window)
{
	if (active)
		window.draw(tuns);

	if (!isPlayingGame)
		WireableObject::Draw(window);
	//window.draw(hitbox);
	window.draw(destiny);
	if (active)
		window.draw(particles);
}

void Tunnel::ChangeDir()
{
	if (dir == 0)
		dir = 2;
	else if (dir == 1)
		dir = 3;
	else if (dir == 2)
		dir = 0;
	else if (dir == 3)
		dir = 1;
}

void Tunnel::ChangeColor()
{
	IsBlue = !IsBlue;
	if (IsBlue)
	{
		tuns.setFillColor(Color(0, 255, 0, 128));
	}
	else {
		tuns.setFillColor(Color(255, 255, 0, 128));
	}
}

void Tunnel::TurnOn()
{
	for (auto b : button) {
		if (!b->GetPressed()) {
			active = false;
		}
	}

	//active door
	active = true;
}

void Tunnel::SetButtonlist(vector<Button*>& button)
{
	for (auto b : button) {
		for (int i = 0; i < buttonid.size(); i++) {
			if (b->GetButtonId() == buttonid[i]) {
				this->button.push_back(b);
			}
		}
	}
}

void Tunnel::AddParticle()
{
	particleNum += 200;
}

void Tunnel::SetParticlePos()
{
	if (isPtcSetted)
		return;

	isPtcSetted = true;

	particles.resize(particleNum);

	for (int i = 0; i < particles.getVertexCount(); i++)
	{
		particles[i].color = IsBlue ? Color(BLUE) : Color(ORANGE);
	}

	FloatRect rect = tuns.getGlobalBounds();

	for (int i = 0; i < particleNum; i++)
	{
		float xpos = Utils::RandomRange(rect.left, rect.left + rect.width);
		float ypos = Utils::RandomRange(rect.top, rect.top + rect.height);

		particles[i].position = { xpos , ypos };
	}
}

void Tunnel::TransParticles(float dt)
{
	for (int i = 0; i < particleNum; i++)
	{
		particles[i].position = particles[i].position + dt * 10 * particleDir;
		if (!tuns.getGlobalBounds().contains(particles[i].position))
		{
			switch (dir)
			{
			case 0:
				particles[i].position.y = startpos.y;
				break;
			case 1:
				particles[i].position.x = startpos.x;
				break;
			case 2:
				particles[i].position.y = startpos.y;
				break;
			case 3:
				particles[i].position.x = startpos.x;
				break;
			}
		}
	}
}
