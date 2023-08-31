#include "skSlash.h"
#include "skTransform.h"
#include "skCollider.h"
#include "skCollisionMgr.h"
#include "skMonster.h"
#include "skObject.h"
#include "skHitEffect.h"
#include "skTimeMgr.h"
#include "skCamera.h"
#include "skSound.h"
#include "skResources.h"
#include "skProjectile.h"

namespace sk
{
	Slash::Slash(Player* owner) :
		 _mPlayer(owner)
		, _mMonster(nullptr)
		, _mTime(0.f)
		, _mState(Player::eState::NONE)
		, _mIsHit(0)
	{
		_mState = _mPlayer->GetState();
		_mAttState = _mPlayer->GetAttState();
		Initialize();
	}
	Slash::Slash()
	{
	}
	Slash::~Slash()
	{
	}
	void Slash::Initialize()
	{
		_mCollider = AddComponent<Collider>();
		_mCollider->SetNotColColor(RGB(255, 255, 50));
		srand((unsigned)time(NULL));

		Resources::Load<Sound>(L"SLASH_AIR_1", L"..\\Resources\\sound\\PENITENT_SLASH_AIR_1.wav");
		Resources::Load<Sound>(L"SLASH_AIR_2", L"..\\Resources\\sound\\PENITENT_SLASH_AIR_2.wav");
		Resources::Load<Sound>(L"SLASH_AIR_3", L"..\\Resources\\sound\\PENITENT_SLASH_AIR_3.wav");
		Resources::Load<Sound>(L"SLASH_AIR_4", L"..\\Resources\\sound\\PENITENT_SLASH_AIR_4.wav");

		SlashCollider();
	}
	void Slash::Update()
	{
		GameObject::Update();

		// 시전후 colliderbox 삭제
		_mTime += TimeMgr::DeltaTime();
		if (_mState == Player::eState::ATTACK && _mTime >= 0.1f)
		{
			Destroy(this);
		}
		else if (_mState == Player::eState::CROUCH_ATT && _mTime >= 0.1f)
		{
			Destroy(this);
		}
		else if (_mState == Player::eState::JUMP_ATT && _mTime >= 0.13f)
		{
			Destroy(this);
		}
		else if (_mState == Player::eState::JUMP_ATT && _mTime >= 0.13f)
		{
			Destroy(this);
		}
		else if (_mState == Player::eState::CHARGEATT && _mTime >= 0.15f)
		{
			Destroy(this);
		}
	}
	void Slash::SlashCollider()
	{
		int num = rand() % 4;
		if (num == 0)
			Resources::Find<Sound>(L"SLASH_AIR_1")->Play(false);
		else if (num == 1)
			Resources::Find<Sound>(L"SLASH_AIR_2")->Play(false);
		else if (num == 2)
			Resources::Find<Sound>(L"SLASH_AIR_3")->Play(false);
		else if (num == 3)
			Resources::Find<Sound>(L"SLASH_AIR_4")->Play(false);

		if (_mState == Player::eState::ATTACK)
		{

			if (_mAttState == Player::eAttState::FIRST_SLASH)
			{
				if (_mPlayer->GetDir() == eDir::Right)
				{
					_mCollider->SetSize(Vector2(175.0f, 60.0f));
					_mCollider->SetOffset(Vector2(_mPlayer->GetPlayerPos().x+100, _mPlayer->GetPlayerPos().y+175));
				}
				else if (_mPlayer->GetDir() == eDir::Left)
				{
					_mCollider->SetSize(Vector2(175.0f, 60.0f));
					_mCollider->SetOffset(Vector2(_mPlayer->GetPlayerPos().x - 100, _mPlayer->GetPlayerPos().y + 175));
				}
			}
			else if (_mAttState == Player::eAttState::SECOND_SLASH)
			{
				if (_mPlayer->GetDir() == eDir::Right)
				{
					_mCollider->SetSize(Vector2(175.0f, 60.0f));
					_mCollider->SetOffset(Vector2(_mPlayer->GetPlayerPos().x + 100, _mPlayer->GetPlayerPos().y + 175));

				}
				else if (_mPlayer->GetDir() == eDir::Left)
				{
					_mCollider->SetSize(Vector2(175.0f, 60.0f));
					_mCollider->SetOffset(Vector2(_mPlayer->GetPlayerPos().x - 100, _mPlayer->GetPlayerPos().y + 175));

				}
			}
			else if (_mAttState == Player::eAttState::THIRD_SLASH)
			{
				if (_mPlayer->GetDir() == eDir::Right)
				{
					_mCollider->SetSize(Vector2(175.0f, 60.0f));
					_mCollider->SetOffset(Vector2(_mPlayer->GetPlayerPos().x + 100, _mPlayer->GetPlayerPos().y + 175));

				}
				else if (_mPlayer->GetDir() == eDir::Left)
				{
					_mCollider->SetSize(Vector2(175.0f, 60.0f));
					_mCollider->SetOffset(Vector2(_mPlayer->GetPlayerPos().x - 100, _mPlayer->GetPlayerPos().y + 175));

				}
			}
			else if (_mAttState == Player::eAttState::COUNTER_SLASH)
			{
				if (_mPlayer->GetDir() == eDir::Right)
				{
					_mCollider->SetSize(Vector2(175.0f, 60.0f));
					_mCollider->SetOffset(Vector2(_mPlayer->GetPlayerPos().x + 100, _mPlayer->GetPlayerPos().y + 175));
				}
				else if (_mPlayer->GetDir() == eDir::Left)
				{
					_mCollider->SetSize(Vector2(175.0f, 60.0f));
					_mCollider->SetOffset(Vector2(_mPlayer->GetPlayerPos().x - 100, _mPlayer->GetPlayerPos().y + 175));
				}
			}
		}

		if (_mState == Player::eState::JUMP_ATT)
		{
			if (_mAttState == Player::eAttState::JUMP_FIRST_SLASH)
			{
				if (_mPlayer->GetDir() == eDir::Right)
				{
					_mCollider->SetSize(Vector2(175.0f, 60.0f));
					_mCollider->SetOffset(Vector2(_mPlayer->GetPlayerPos().x + 100, _mPlayer->GetPlayerPos().y + 175));

				}
				else if (_mPlayer->GetDir() == eDir::Left)
				{
					_mCollider->SetSize(Vector2(175.0f, 60.0f));
					_mCollider->SetOffset(Vector2(_mPlayer->GetPlayerPos().x - 100, _mPlayer->GetPlayerPos().y + 175));
				}
			}
			else if (_mAttState == Player::eAttState::JUMP_SECOND_SLASH)
			{
				if (_mPlayer->GetDir() == eDir::Right)
				{
					_mCollider->SetSize(Vector2(175.0f, 60.0f));
					_mCollider->SetOffset(Vector2(_mPlayer->GetPlayerPos().x + 100, _mPlayer->GetPlayerPos().y + 175));

				}
				else if (_mPlayer->GetDir() == eDir::Left)
				{
					_mCollider->SetSize(Vector2(175.0f, 60.0f));
					_mCollider->SetOffset(Vector2(_mPlayer->GetPlayerPos().x - 100, _mPlayer->GetPlayerPos().y + 175));
				}
			}
		}

		if (_mAttState == Player::eAttState::CHARGE_SLASH)
		{
			if (_mPlayer->GetDir() == eDir::Right)
			{
				_mCollider->SetSize(Vector2(300.0f, 200.0f));
				_mCollider->SetOffset(Vector2(_mPlayer->GetPlayerPos().x + 25, _mPlayer->GetPlayerPos().y + 175));

			}
			else if (_mPlayer->GetDir() == eDir::Left)
			{
				_mCollider->SetSize(Vector2(300.0f, 200.0f));
				_mCollider->SetOffset(Vector2(_mPlayer->GetPlayerPos().x - 25, _mPlayer->GetPlayerPos().y + 175));
			}
		}

	}
	void Slash::IsHit()
	{
		if (_mPlayer->GetAttState() != Player::eAttState::CHARGE_SLASH)
		{
			Player::SetAttSuccess(true);
		}

		Monster::Info monsinfo = _mMonster->GetInfo();
		monsinfo.Hp -= _mPlayer->GetInfo().Dmg;
		_mMonster->SetInfo(monsinfo);
	}

	void Slash::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Slash::OnCollisionEnter(Collider* other)
	{
		_mMonster = dynamic_cast<Monster*>(other->GetOwner());
		Projectile* projectile = dynamic_cast<Projectile*>(other->GetOwner());

		Transform* tr = nullptr;
		if (_mMonster != nullptr)
		{
			tr = _mMonster->GetComponent<Transform>();

			HitEffect* hiteffect = object::Instantiate<HitEffect>(eLayerType::Effect, tr->GetPosition()); // 몬스터위치에 히트 이펙트
			if (_mPlayer->GetAttState() == Player::eAttState::CHARGE_SLASH)
			{
				//tr->SetPosition(Vector2())
				if (_mPlayer->GetDir() == eDir::Right)
					hiteffect->PlayAnimation(eDir::Right,true);
				else if (_mPlayer->GetDir() == eDir::Left)
					hiteffect->PlayAnimation(eDir::Left,true);
			}
			else
			{
				if (_mPlayer->GetDir() == eDir::Right)
				{
					hiteffect->PlayAnimation(eDir::Right);
				}
				else if (_mPlayer->GetDir() == eDir::Left)
				{
					hiteffect->PlayAnimation(eDir::Left);
				}
			}
			IsHit();
		}

		if (projectile != nullptr)
		{
			tr = projectile->GetComponent<Transform>();

			HitEffect* hiteffect = object::Instantiate<HitEffect>(eLayerType::Effect, tr->GetPosition()); // 몬스터위치에 히트 이펙트
			if (_mPlayer->GetAttState() == Player::eAttState::CHARGE_SLASH)
			{
				//tr->SetPosition(Vector2())
				if (_mPlayer->GetDir() == eDir::Right)
					hiteffect->PlayAnimation(eDir::Right, true);
				else if (_mPlayer->GetDir() == eDir::Left)
					hiteffect->PlayAnimation(eDir::Left, true);
			}
			else
			{
				if (_mPlayer->GetDir() == eDir::Right)
				{
					hiteffect->PlayAnimation(eDir::Right);
				}
				else if (_mPlayer->GetDir() == eDir::Left)
				{
					hiteffect->PlayAnimation(eDir::Left);
				}
			}
			Player::SetAttSuccess(true);
		}


	}
	void Slash::OnCollisionStay(Collider* other)
	{
	}
	void Slash::OnCollisionExit(Collider* other)
	{
	}
}