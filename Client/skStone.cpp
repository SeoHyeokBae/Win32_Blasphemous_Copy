#include "skStone.h"
#include "skTexture.h"
#include "skResources.h"
#include "skAnimator.h"
#include "skTransform.h"
#include "skElderBrother.h"
#include"skRigidbody.h"
#include "skCollider.h"
#include "skElderCorpseEff.h"
#include "skObject.h"
#include "skTransform.h"
#include "skElderWaveMgr.h"
#include "skPlayer.h"
#include "skPlayerHit.h"

namespace sk
{
	Stone::Stone() :
		_mAnimator(nullptr)
		, _mRigidbody(nullptr)
		, _mCollider(nullptr)
		, _mTransform(nullptr)
		, _mDir(eDir::None)
		, _mTarget(Vector2::Zero)
		, _mStartPos(Vector2::Zero)
		, _mbShootUp(true)
	{
	}
	Stone::~Stone()
	{
	}
	void Stone::Initialize()
	{
		_mAnimator = AddComponent<Animator>();
		_mRigidbody = AddComponent<Rigidbody>();
		_mCollider = AddComponent<Collider>();
		_mTransform = GetComponent<Transform>();

		Texture* Stone = Resources::Load<Texture>(L"stone"
			, L"..\\Resources\\image\\stoner\\rock.png");

		_mAnimator->CreateAnimation(L"Stone", Stone, Vector2(0.0f, 0.0f), Vector2(16.f, 16.f)
			, 32, Vector2(0.0f, 0.0f), 0.09f);

		_mAnimator->SetScale(Vector2(2.0f, 2.0f));

		//_mRigidbody->SetGravity(Vector2(0.f, 1200.0f));

		_mAnimator->PlayAnimation(L"Stone");
	}
	void Stone::Update()
	{
		GameObject::Update();

		if (_mTarget != Vector2::Zero)
		{
			Move();
		}

		//if (_mAnimator->IsActiveAnimationComplete())
		//{
		//	Destroy(this);
		//}
	}

	void Stone::Move()
	{
		Vector2  pos = _mTransform->GetPosition();
		Vector2 velocity = _mRigidbody->GetVelocity();
		if (_mbShootUp)
		{
			if (_mTarget.y < _mStartPos.y - 300.f)
			{
				_mbShootUp = false;
				velocity.y = - 1300.0f;
			}
			else
			{
				_mbShootUp = false;
				velocity.y = -550.0f;
			}
		}



		if (_mDir == eDir::Right)
		{
			if (_mTarget.x <= _mStartPos.x + 350.f)
			{
				velocity.x = (fabs(_mTarget.x + 65.f - pos.x) + 50.f);
			}
			else
				velocity.x = (fabs(_mTarget.x+ 65.f - pos.x) + 300.f);
		}
		else if (_mDir == eDir::Left)
		{
			if (_mTarget.x >= _mStartPos.x - 350.f )
			{
				velocity.x = -(fabs(_mTarget.x - 65.f - pos.x) + 50.f);
			}
			else
				velocity.x = -(fabs(_mTarget.x- 65.f - pos.x) + 300.f);
		}
		_mRigidbody->SetVelocity(velocity);
	}

	void Stone::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Stone::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		Transform* tr = nullptr;
		if (player != nullptr)
		{
			tr = player->GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();

			if (player->GetState() != Player::eState::DODGE && player->GetState() != Player::eState::HIT)
			{
				PlayerHit* phiteffect = object::Instantiate<PlayerHit>(eLayerType::Effect, tr->GetPosition());

				if (player->GetDir() == eDir::Right)
				{
					pos.x -= 50.f;
					phiteffect->PlayAnimation(eDir::Right);
					player->GetComponent<Animator>()->PlayAnimation(L"PlayerHit_right", false);
					player->SetState(Player::eState::HIT);
				}
				else if (player->GetDir() == eDir::Left)
				{
					pos.x += 50.f;
					phiteffect->PlayAnimation(eDir::Left);
					player->GetComponent<Animator>()->PlayAnimation(L"PlayerHit_left", false);
					player->SetState(Player::eState::HIT);
				}
				tr->SetPosition(pos);
			}
		}
		//Destroy(this);
	}
	void Stone::OnCollisionStay(Collider* other)
	{
	}
	void Stone::OnCollisionExit(Collider* other)
	{
	}
}