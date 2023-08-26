#include "skLadder.h"
#include "skPlayer.h"
#include "skCollider.h"
#include "skRigidbody.h"
#include "skTransform.h"
#include "skSceneMgr.h"
#include "skTimeMgr.h"
#include "skCamera.h"
#include "skInput.h"

namespace sk
{
	Ladder::Ladder()
	{
	}
	Ladder::~Ladder()
	{
	}
	void Ladder::Initialize()
	{
	}
	void Ladder::Update()
	{
		GameObject::Update();
	}
	void Ladder::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


	void Ladder::OnCollisionEnter(Collider* other)
	{
	}
	void Ladder::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		Transform* tr = nullptr;
		Rigidbody* rb = nullptr;

		if (player != nullptr)
		{
			Transform* tr = player->GetComponent<Transform>();
			Rigidbody* rb = player->GetComponent<Rigidbody>();

			float len = fabs(other->GetPosition().x - this->GetComponent<Collider>()->GetPosition().x);
			float scale = fabs(other->GetSize().x / 2.0f + this->GetComponent<Collider>()->GetSize().x / 2.0f);

			player->SetCanClimb(true);

			if (len < scale)
			{
				if (Input::GetKeyDown(eKeyCode::W)|| Input::GetKeyDown(eKeyCode::S))
				{
					tr->SetPosition(Vector2(GetComponent<Collider>()->GetPosition().x, tr->GetPosition().y));
				}

				if (Input::GetKey(eKeyCode::W))
				{
					rb->SetVelocity(Vector2(0.0f, 0.0f));
					rb->SetGround(true);
					tr->SetPosition(Vector2(GetComponent<Collider>()->GetPosition().x, tr->GetPosition().y));
				}
			}
		}
	}
	void Ladder::OnCollisionExit(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Rigidbody* rb = player->GetComponent<Rigidbody>();
		if (player->GetState() == Player::eState::CLIMB)
		{
			player->SetState(Player::eState::IDLE);
			rb->SetGround(false);
		}
		player->SetCanClimb(false);
	}
}