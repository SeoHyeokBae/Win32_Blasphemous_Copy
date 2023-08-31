#include "skThorn.h"
#include "skTexture.h"
#include "skResources.h"
#include "skAnimator.h"
#include "skTransform.h"
#include "skRigidbody.h"
#include "skCollider.h"
#include "skObject.h"
#include "skTransform.h"
#include "skPlayer.h"
#include "skPlayerHit.h"

namespace sk
{
	Thorn::Thorn() :
		_mAnimator(nullptr)
		, _mCollider(nullptr)
	{
	}
	Thorn::~Thorn()
	{
	}
	void Thorn::Initialize()
	{
		_mAnimator = AddComponent<Animator>();
		_mCollider = AddComponent<Collider>();

		Texture* Thorns = Resources::Load<Texture>(L"thorns_tower"
			, L"..\\Resources\\image\\pietat\\thorns_tower.bmp");

		_mAnimator->CreateAnimation(L"Thorns_Tower", Thorns, Vector2(0.0f, 0.0f), Vector2(64.f, 128.f)
			, 43, Vector2(0.0f, 0.0f), 0.05f);

		_mAnimator->SetScale(Vector2(2.0f, 2.0f));
		_mCollider->SetOffset(Vector2(0.f, 30.f));


		PlayAnimation();
	}
	void Thorn::Update()
	{
		GameObject::Update();

		if (_mAnimator->GetActiveAnime()->GetIndex() == 25)
		{
			_mCollider->SetSize(Vector2(64.f, 170.f));
		}
		if (_mAnimator->GetActiveAnime()->GetIndex() == 37)
		{
			_mCollider->SetSize(Vector2(0.f, 0.f));
		}

		if (_mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	void Thorn::PlayAnimation()
	{
		_mAnimator->PlayAnimation(L"Thorns_Tower");
	}

	void Thorn::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Thorn::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		Transform* tr = nullptr;

		if (player != nullptr)
		{
			Rigidbody* Player_RB = player->GetComponent<Rigidbody>();
			Vector2 velocity = Player_RB->GetVelocity();

			tr = player->GetComponent<Transform>();

			if (player->GetState() != Player::eState::DODGE && player->GetState() != Player::eState::HIT)
			{
				player->GetComponent<Rigidbody>()->SetGround(false);
				PlayerHit* phiteffect = object::Instantiate<PlayerHit>(eLayerType::Effect, tr->GetPosition());

				if (player->GetDir() == eDir::Right)
				{
					velocity.x = -350.0f;
					velocity.y = -350.0f;
					Player_RB->SetVelocity(velocity);
					phiteffect->PlayAnimation(eDir::Right);
					player->GetComponent<Animator>()->PlayAnimation(L"PlayerHit_right", false);
					player->SetState(Player::eState::HIT);
				}
				else if (player->GetDir() == eDir::Left)
				{
					velocity.x = 350.0f;
					velocity.y = -350.0f;
					Player_RB->SetVelocity(velocity);
					phiteffect->PlayAnimation(eDir::Left);
					player->GetComponent<Animator>()->PlayAnimation(L"PlayerHit_left", false);
					player->SetState(Player::eState::HIT);
				}
			}

		}
	}
	void Thorn::OnCollisionStay(Collider* other)
	{
	}
	void Thorn::OnCollisionExit(Collider* other)
	{
	}
}