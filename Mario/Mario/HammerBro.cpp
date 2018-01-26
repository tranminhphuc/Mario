#include "HammerBro.h"
#include "Windows.h"

HammerBro::HammerBro(int xMinion, int yMinion)
{
	this->xMinion = xMinion;
	this->yMinion = yMinion;
}

HammerBro::~HammerBro()
{
}

void HammerBro::Update()
{
}

void HammerBro::Draw(sf::RenderWindow & window, Texture * texture)
{
	if(minionState != -2)
		texture->Draw(window, sf::Vector2f((float)xMinion + Window::GetMap()->GetX(), (float)yMinion - 18));
}

void HammerBro::MinionPhysics()
{
	if (jumpState != NhayLen)
	{
		if (!CheckCollisionLB(2, 2) && !CheckCollisionRB(-2, 2))
			PhysicsState2();
		else
			jumpState = TrenMatDat;
	}
}

void HammerBro::CollisionWithPlayer(bool top)
{
	if (Window::GetMap()->GetPlayer()->GetStarEffect() || top)
		SetMinionState(-2);
	else
		Window::GetMap()->PlayerDeath();
}
