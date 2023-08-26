#include "skWall.h"
#include "skPlayer.h"
#include "skCollider.h"
#include "skTransform.h"
#include "skMonster.h"

namespace sk
{
	Wall::Wall()
		: _mbRight(true)
	{
	}
	Wall::~Wall()
	{
	}
	void Wall::Initialize()
	{
	}
	void Wall::Update()
	{
		GameObject::Update();
	}
	void Wall::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Wall::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Monster* monster = dynamic_cast<Monster*>(other->GetOwner());

		if (player != nullptr)
		{
			Transform* tr = player->GetComponent<Transform>();

			float len = fabs(other->GetPosition().x - this->GetComponent<Collider>()->GetPosition().x);
			float scale = fabs(other->GetSize().x / 2.0f + this->GetComponent<Collider>()->GetSize().x / 2.0f);

			if (len < scale)	
			{
				Vector2 playerPos = tr->GetPosition();
				if (_mbRight)
				{
					playerPos.x += (scale - len) + 1.f;
				}
				else
				{
					playerPos.x -= (scale - len) + 1.f;
				}
				tr->SetPosition(playerPos);
			}
		}

		if (monster != nullptr)
		{
			Transform* tr = monster->GetComponent<Transform>();

			float len = fabs(other->GetPosition().x - this->GetComponent<Collider>()->GetPosition().x);
			float scale = fabs(other->GetSize().x / 2.0f + this->GetComponent<Collider>()->GetSize().x / 2.0f);

			if (len < scale)
			{
				Vector2 monpos = tr->GetPosition();
				if (_mbRight)
				{
					monpos.x += (scale - len) + 1.5f;
				}
				else
				{
					monpos.x -= (scale - len) + 1.5f;
				}
				tr->SetPosition(monpos);
			}
		}
	}
	void Wall::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Monster* monster = dynamic_cast<Monster*>(other->GetOwner());

		if (player != nullptr)
		{
			Transform* tr = player->GetComponent<Transform>();

			float len = fabs(other->GetPosition().x - this->GetComponent<Collider>()->GetPosition().x);
			float scale = fabs(other->GetSize().x / 2.0f + this->GetComponent<Collider>()->GetSize().x / 2.0f);

			if (len < scale)
			{
				Vector2 playerPos = tr->GetPosition();
				if (_mbRight)
				{
					playerPos.x += (scale - len) + 1.f;
				}
				else
				{
					playerPos.x -= (scale - len) + 1.f;
				}
				tr->SetPosition(playerPos);
			}
		}

		if (monster != nullptr)
		{
			Transform* tr = monster->GetComponent<Transform>();

			float len = fabs(other->GetPosition().x - this->GetComponent<Collider>()->GetPosition().x);
			float scale = fabs(other->GetSize().x / 2.0f + this->GetComponent<Collider>()->GetSize().x / 2.0f);

			if (len < scale)
			{
				Vector2 monpos = tr->GetPosition();
				if (_mbRight)
				{
					monpos.x += (scale - len) + 1.5f;
				}
				else
				{
					monpos.x -= (scale - len) + 1.5f;
				}
				tr->SetPosition(monpos);
			}
		}
	}
	void Wall::OnCollisionExit(Collider* other)
	{

	}
}