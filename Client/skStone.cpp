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
#include "skFloor.h"
#include "skSound.h"
#include "skSlash.h"

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
		, _mbCanDeath(false)
		, _mbUnGround(true)
		, _mbIgnore(false)
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
		Texture* Destroy = Resources::Load<Texture>(L"rock_landing"
			, L"..\\Resources\\image\\stoner\\rock_landing.bmp");

		_mAnimator->CreateAnimation(L"Stone", Stone, Vector2(0.0f, 0.0f), Vector2(16.f, 16.f)
			, 32, Vector2(0.0f, 0.0f), 0.09f);

		_mAnimator->CreateAnimation(L"rock_landing_right", Destroy, Vector2(0.0f, 0.0f), Vector2(70.f, 70.f)
			, 13, Vector2(0.0f, 0.0f), 0.055f);
		_mAnimator->CreateAnimation(L"rock_landing_left", Destroy, Vector2(0.0f, 70.f), Vector2(70.f, 70.f)
			, 13, Vector2(0.0f, 0.0f), 0.055f);

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

		if (_mbCanDeath)
		{
			Death();
		}
	}

	void Stone::Move()
	{
		Vector2  pos = _mTransform->GetPosition();
		Vector2 velocity = _mRigidbody->GetVelocity();
		if (_mRigidbody->GetGround())
		{
			velocity.x = 0.f;
			return;
		}

		if (_mbCanDeath)
		{
			Death();
		}

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

	void Stone::Death()
	{
		if (_mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	void Stone::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Floor* floor = dynamic_cast<Floor*>(other->GetOwner());

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
					pos.y -= 25.f;
					phiteffect->PlayAnimation(eDir::Right);
					player->GetComponent<Animator>()->PlayAnimation(L"PlayerHit_right", false);
					player->SetState(Player::eState::HIT);

				}
				else if (player->GetDir() == eDir::Left)
				{
					pos.x += 50.f;
					pos.y -= 25.f;
					phiteffect->PlayAnimation(eDir::Left);
					player->GetComponent<Animator>()->PlayAnimation(L"PlayerHit_left", false);
					player->SetState(Player::eState::HIT);
				}

				if (!(_mbCanDeath))
				{
					Resources::Find<Sound>(L"STONE LANDING")->Play(false);
					Resources::Find<Sound>(L"STONE LANDING")->SetVolume(20);
					_mbCanDeath = true;
					if (_mDir == eDir::Right)
					{
						_mRigidbody->SetGround(true);
						_mRigidbody->SetVelocity(Vector2(50.f, 50.f));
						_mAnimator->PlayAnimation(L"rock_landing_left", false);
					}
					else
					{
						_mRigidbody->SetGround(true);
						_mRigidbody->SetVelocity(Vector2(-50.f,50.f));
						_mAnimator->PlayAnimation(L"rock_landing_right", false);
					}
				}
				tr->SetPosition(pos);
			}
		}

		Slash* slash = dynamic_cast<Slash*>(other->GetOwner());

		if (slash != nullptr)
		{
			if (!(_mbCanDeath))
			{
				Resources::Find<Sound>(L"STONE LANDING")->Play(false);
				Resources::Find<Sound>(L"STONE LANDING")->SetVolume(20);
				_mbCanDeath = true;
				if (_mDir == eDir::Right)
				{
					_mRigidbody->SetGround(true);
					_mRigidbody->SetVelocity(Vector2(50.f, 50.f));
					_mAnimator->PlayAnimation(L"rock_landing_left", false);
				}
				else
				{
					_mRigidbody->SetGround(true);
					_mRigidbody->SetVelocity(Vector2(-50.f, 50.f));
					_mAnimator->PlayAnimation(L"rock_landing_right", false);
				}
			}
		}



		if (floor != nullptr)
		{
			Transform* tr = floor->GetComponent<Transform>();

			if (this->GetComponent<Collider>()->GetPosition().y > tr->GetPosition().y)
			{
				_mbIgnore = true;
			}

			if (_mbIgnore)
			{
				return;
			}


			_mbUnGround = false;
			if (!(_mbCanDeath))
			{
				Resources::Find<Sound>(L"STONE LANDING")->Play(false);
				Resources::Find<Sound>(L"STONE LANDING")->SetVolume(20);
				_mbCanDeath = true;
				if (_mDir == eDir::Right)
				{
					_mRigidbody->SetVelocity(Vector2::Zero);
					_mAnimator->PlayAnimation(L"rock_landing_left", false);
				}
				else
				{
					_mRigidbody->SetVelocity(Vector2::Zero);
					_mAnimator->PlayAnimation(L"rock_landing_right", false);
				}
			}

		}

	}
	void Stone::OnCollisionStay(Collider* other)
	{
	}
	void Stone::OnCollisionExit(Collider* other)
	{
		if (_mbIgnore)
		{
			_mbIgnore = false;
		}
	}
}