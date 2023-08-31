#include "skThorn_Projectile.h"
#include "skTexture.h"
#include "skResources.h"
#include "skAnimator.h"
#include "skTransform.h"
#include "skElderBrother.h"
#include "skRigidbody.h"
#include "skCollider.h"
#include "skElderCorpseEff.h"
#include "skObject.h"
#include "skTransform.h"
#include "skElderWaveMgr.h"
#include "skPlayer.h"
#include "skPlayerHit.h"
#include "skFloor.h"
#include "skSlash.h"
#include "skSound.h"

namespace sk
{
	Thorn_Projectile::Thorn_Projectile() :
		_mAnimator(nullptr)
		, _mRigidbody(nullptr)
		, _mCollider(nullptr)
		, _mTransform(nullptr)
		, _mDir(eDir::None)
		, _mTarget(Vector2::Zero)
		, _mStartPos(Vector2::Zero)
		, _mThornInfo{}
		, _mbShootUp(true)
		, _mbDeathAnime(true)
		, _mbCanDeath(false)
		, _mbUnraveled(false)
	{
	}
	Thorn_Projectile::~Thorn_Projectile()
	{
	}
	void Thorn_Projectile::Initialize()
	{
		_mAnimator = AddComponent<Animator>();
		_mRigidbody = AddComponent<Rigidbody>();
		_mCollider = AddComponent<Collider>();
		_mTransform = GetComponent<Transform>();

		Texture* Thorn_Projectile = Resources::Load<Texture>(L"thorn_projectile"
			, L"..\\Resources\\image\\pietat\\thorn_projectile.png");
		Texture* Thorn_Unraveling = Resources::Load<Texture>(L"thorn_unraveling"
			, L"..\\Resources\\image\\pietat\\thorn_unraveling.bmp");
		Texture* Thorn_Projectile_Destroyed = Resources::Load<Texture>(L"thorn_destroyed"
			, L"..\\Resources\\image\\pietat\\thorn_destroyed.bmp");
		Texture* Thorn_Unraveling_Destroyed = Resources::Load<Texture>(L"thorn_unraveled_destroyed"
			, L"..\\Resources\\image\\pietat\\thorn_unraveled_destroyed.bmp");

		_mAnimator->CreateAnimation(L"thorn_projectile", Thorn_Projectile, Vector2(0.0f, 0.0f), Vector2(25.f, 25.f)
			, 10, Vector2(0.0f, 0.0f), 0.09f);
		_mAnimator->CreateAnimation(L"thorn_unraveling_right", Thorn_Unraveling, Vector2(0.0f, 0.0f), Vector2(70.f, 45.f)
			, 22, Vector2(0.0f, 0.0f), 0.09f);
		_mAnimator->CreateAnimation(L"thorn_unraveling_left", Thorn_Unraveling, Vector2(0.0f, 45.0f), Vector2(70.f, 45.f)
			, 22, Vector2(0.0f, 0.0f), 0.09f);
		_mAnimator->CreateAnimation(L"projectile_destroy_right", Thorn_Projectile_Destroyed, Vector2(0.0f, 0.0f), Vector2(50.f, 50.f)
			, 14, Vector2(0.0f, 0.0f), 0.05f);
		_mAnimator->CreateAnimation(L"projectile_destroy_left", Thorn_Projectile_Destroyed, Vector2(0.0f, 50.0f), Vector2(50.f, 50.f)
			, 14, Vector2(0.0f, 0.0f), 0.05f);
		_mAnimator->CreateAnimation(L"unraveled_destroyed_right", Thorn_Unraveling_Destroyed, Vector2(0.0f, 0.0f), Vector2(120.f, 120.f)
			, 22, Vector2(20.0f, -10.0f), 0.06f);
		_mAnimator->CreateAnimation(L"unraveled_destroyed_left", Thorn_Unraveling_Destroyed, Vector2(0.0f, 120.f), Vector2(120.f, 120.f)
			, 22, Vector2(-20.0f, -10.0f), 0.06f);

		Resources::Load<Sound>(L"SPIT_GROW", L"..\\Resources\\sound\\SPIT_GROW.wav");
		Resources::Load<Sound>(L"SPIT_EXPLOSION", L"..\\Resources\\sound\\SPIT_EXPLOSION.wav");
		Resources::Load<Sound>(L"SPIT_DESTROY", L"..\\Resources\\sound\\SPIT_DESTROY.wav");

		_mThornInfo = { 10,5 };

		_mCollider->SetColliderType(eColliderType::Elipse);
		_mCollider->SetRadius(25.0f);

		_mAnimator->SetScale(Vector2(2.0f, 2.0f));

		//_mRigidbody->SetGravity(Vector2(0.f, 1200.0f));

		_mAnimator->PlayAnimation(L"thorn_projectile");
	}
	void Thorn_Projectile::Update()
	{
		GameObject::Update();

		if (_mbCanDeath)
		{
			Death();
			return;
		}

		if (_mTarget != Vector2::Zero)
		{
			Move();
		}

		if (_mThornInfo.Hp <= 0 && _mbDeathAnime)
		{
			_mbDeathAnime = false;
			if (_mThornInfo.Hp < 0)
			{
				_mThornInfo.Hp = 0;
			}
			if (_mAnimator->GetActiveAnime() == _mAnimator->FindAnimation(L"thorn_projectile"))
			{
				if (_mDir == eDir::Right)
				{
					_mAnimator->PlayAnimation(L"projectile_destroy_right");
				}
				else if (_mDir == eDir::Left)
				{
					_mAnimator->PlayAnimation(L"projectile_destroy_left");
				}
			}
			else
			{
				if (_mDir == eDir::Right)
				{
					_mAnimator->PlayAnimation(L"unraveled_destroyed_right");
				}
				else if (_mDir == eDir::Left)
				{
					_mAnimator->PlayAnimation(L"unraveled_destroyed_left");

				}
			}
			_mbCanDeath = true;
		}


	}

	void Thorn_Projectile::Move()
	{
		Vector2  pos = _mTransform->GetPosition();
		Vector2 velocity = _mRigidbody->GetVelocity();
		srand(GetTickCount64());
		int rand_num = rand() % 300;

		if (_mRigidbody->GetGround())
		{
			velocity.x = 0.f;
			return;
		}

		if (_mbShootUp)
		{
			_mbShootUp = false;
			velocity.y = -550.0f;
		}

		//velocity.y = -450.0f;

		if (_mDir == eDir::Right)
		{
				velocity.x = (fabs(_mTarget.x + 65.f - pos.x ) + rand_num);
		}
		else if (_mDir == eDir::Left)
		{
				velocity.x = -(fabs(_mTarget.x - 65.f - pos.x) + rand_num);
		}
		_mRigidbody->SetVelocity(velocity);
	}

	void Thorn_Projectile::Death()
	{
		if (_mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	void Thorn_Projectile::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Thorn_Projectile::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Floor* floor = dynamic_cast<Floor*>(other->GetOwner());
		Slash* slash = dynamic_cast<Slash*>(other->GetOwner());

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

				if (!(_mbCanDeath) && !(_mbUnraveled))
				{
					Resources::Find<Sound>(L"SPIT_EXPLOSION")->Play(false);

					_mbCanDeath = true;
					if (player->GetDir() == eDir::Right)
					{
						_mRigidbody->SetGround(true);
						_mRigidbody->SetVelocity(Vector2::Zero);
						_mAnimator->PlayAnimation(L"projectile_destroy_right", false);
						_mbCanDeath = true;
					}
					else
					{
						_mRigidbody->SetGround(true);
						_mRigidbody->SetVelocity(Vector2::Zero);
						_mAnimator->PlayAnimation(L"projectile_destroy_left", false);
						_mbCanDeath = true;
					}
				}
				tr->SetPosition(pos);
			}
		}

		if (floor != nullptr)
		{
			_mbUnraveled = true;
			if (_mbCanDeath && _mbUnraveled)
			{
				_mbCanDeath = false;
				if (_mDir == eDir::Right)
				{
					Resources::Find<Sound>(L"SPIT_DESTROY")->Play(false);
					_mAnimator->PlayAnimation(L"unraveled_destroyed_right", false);
				}
				else if (_mDir == eDir::Left)
				{
					Resources::Find<Sound>(L"SPIT_DESTROY")->Play(false);
					_mAnimator->PlayAnimation(L"unraveled_destroyed_left", false);
				}
			}

			if (_mDir == eDir::Right)
			{
				Resources::Find<Sound>(L"SPIT_GROW")->Play(false);
				_mAnimator->PlayAnimation(L"thorn_unraveling_right", false);
			}
			else if (_mDir == eDir::Left)
			{
				Resources::Find<Sound>(L"SPIT_GROW")->Play(false);
				_mAnimator->PlayAnimation(L"thorn_unraveling_left", false);
			}

			_mCollider->SetColliderType(eColliderType::Rectangle);
			_mCollider->SetSize(Vector2(70.f, 70.f));

			Vector2 pos = _mTransform->GetPosition();
		}

		if (slash != nullptr)
		{
			// slash로 옮겨줘야함
			_mThornInfo.Hp -= 5;
		}

	}
	void Thorn_Projectile::OnCollisionStay(Collider* other)
	{
	}
	void Thorn_Projectile::OnCollisionExit(Collider* other)
	{
	}
}