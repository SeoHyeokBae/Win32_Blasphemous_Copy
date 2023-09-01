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
#include "skBloodEff.h"

namespace sk
{
	Slash::Slash(Player* owner) :
		 _mPlayer(owner)
		, _mMonster(nullptr)
		, _mTime(0.f)
		, _mState(Player::eState::NONE)
		, _mIsHit(0)
		, _mbCounter(false)
		, _mbCharge(false)
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
		Resources::Load<Sound>(L"HEAVY_SLASH", L"..\\Resources\\sound\\PENITENT_HEAVY_SLASH.wav");
		Resources::Load<Sound>(L"ENEMY_HIT_1", L"..\\Resources\\sound\\PENITENT_ENEMY_HIT_1.wav");
		Resources::Load<Sound>(L"ENEMY_HIT_2", L"..\\Resources\\sound\\PENITENT_ENEMY_HIT_2.wav");
		Resources::Load<Sound>(L"ENEMY_HIT_3", L"..\\Resources\\sound\\PENITENT_ENEMY_HIT_3.wav");
		Resources::Load<Sound>(L"ENEMY_HIT_4", L"..\\Resources\\sound\\PENITENT_ENEMY_HIT_4.wav");
		Resources::Load<Sound>(L"HEAVY_ENEMY_HIT", L"..\\Resources\\sound\\PENITENT_HEAVY_ENEMY_HIT.wav");
		Resources::Load<Sound>(L"LOADED_CHARGED_ATTACK", L"..\\Resources\\sound\\LOADED_CHARGED_ATTACK.wav");

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

		if (_mState == Player::eState::ATTACK)
		{
			int num = rand() % 4;
			if (num == 0)
			{
				Resources::Find<Sound>(L"SLASH_AIR_1")->Play(false);
				Resources::Find<Sound>(L"SLASH_AIR_1")->SetVolume(30.f);
			}
			else if (num == 1)
			{
				Resources::Find<Sound>(L"SLASH_AIR_2")->Play(false);
				Resources::Find<Sound>(L"SLASH_AIR_2")->SetVolume(30.f);
			}
			else if (num == 2)
			{
				Resources::Find<Sound>(L"SLASH_AIR_3")->Play(false);
				Resources::Find<Sound>(L"SLASH_AIR_3")->SetVolume(30.f);
			}
			else if (num == 3)
			{
				Resources::Find<Sound>(L"SLASH_AIR_4")->Play(false);
				Resources::Find<Sound>(L"SLASH_AIR_4")->SetVolume(30.f);
			}

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
				_mbCounter = true;
				Resources::Find<Sound>(L"HEAVY_SLASH")->Play(false);
				Resources::Find<Sound>(L"HEAVY_SLASH")-> SetVolume(30.f);
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
			_mbCharge = true;
			Resources::Find<Sound>(L"LOADED_CHARGED_ATTACK")->Play(false);
			Resources::Find<Sound>(L"LOADED_CHARGED_ATTACK")->SetVolume(30.f);
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
		if (_mPlayer->GetAttState() != Player::eAttState::CHARGE_SLASH && _mPlayer->GetAttState() != Player::eAttState::COUNTER_SLASH)
		{
			Player::SetAttSuccess(true);
		}
		if (_mbCharge)
		{
			Monster::Info monsinfo = _mMonster->GetInfo();
			monsinfo.Hp -= 25;
			_mMonster->SetInfo(monsinfo);
		}
		else
		{
			Monster::Info monsinfo = _mMonster->GetInfo();
			monsinfo.Hp -= _mPlayer->GetInfo().Dmg;
			_mMonster->SetInfo(monsinfo);
		}


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
			if (_mPlayer->GetAttState() == Player::eAttState::CHARGE_SLASH || _mPlayer->GetAttState() == Player::eAttState::COUNTER_SLASH)
			{
				Resources::Find<Sound>(L"HEAVY_ENEMY_HIT")->Play(false);
				Resources::Find<Sound>(L"HEAVY_ENEMY_HIT")->SetVolume(30.f);
			}
			else
			{
				int num = rand() % 4;
				if (num == 0)
				{
					Resources::Find<Sound>(L"ENEMY_HIT_1")->Play(false);
					Resources::Find<Sound>(L"ENEMY_HIT_1")->SetVolume(30.f);
				}
				else if (num == 1)
				{
					Resources::Find<Sound>(L"ENEMY_HIT_2")->Play(false);
					Resources::Find<Sound>(L"ENEMY_HIT_2")->SetVolume(30.f);
				}
				else if (num == 2)
				{
					Resources::Find<Sound>(L"ENEMY_HIT_3")->Play(false);
					Resources::Find<Sound>(L"ENEMY_HIT_3")->SetVolume(30.f);
				}
				else if (num == 3)
				{
					Resources::Find<Sound>(L"ENEMY_HIT_4")->Play(false);
					Resources::Find<Sound>(L"ENEMY_HIT_4")->SetVolume(30.f);
				}
			}
			tr = _mMonster->GetComponent<Transform>();

			HitEffect* hiteffect = object::Instantiate<HitEffect>(eLayerType::Effect,Vector2(_mCollider->GetPosition().x, _mCollider->GetPosition().y)); // 몬스터위치에 히트 이펙트
			BloodEff* bloodeffect = object::Instantiate<BloodEff>(eLayerType::Effect, Vector2(tr->GetPosition().x, _mCollider->GetPosition().y)); // 몬스터위치에 히트 이펙트
			if (_mPlayer->GetAttState() == Player::eAttState::FIRST_SLASH)
			{
				hiteffect->SetActionNum(1);
				bloodeffect->SetActionNum(1);
			}
			else if (_mPlayer->GetAttState() == Player::eAttState::SECOND_SLASH)
			{
				hiteffect->SetActionNum(2);
				bloodeffect->SetActionNum(2);
			}
			else if (_mPlayer->GetAttState() == Player::eAttState::THIRD_SLASH)
			{
				hiteffect->SetActionNum(3);
				bloodeffect->SetActionNum(3);
			}

			if (_mPlayer->GetAttState() == Player::eAttState::CHARGE_SLASH)
			{

				if (_mPlayer->GetDir() == eDir::Right)
				{
					hiteffect->PlayAnimation(eDir::Right, true);
					bloodeffect->PlayAnimation(eDir::Right, true);
				}
				else if (_mPlayer->GetDir() == eDir::Left)
				{
					hiteffect->PlayAnimation(eDir::Left, true);
					bloodeffect->PlayAnimation(eDir::Left, true);
				}
			}
			else
			{
				if (_mPlayer->GetDir() == eDir::Right)
				{
					hiteffect->PlayAnimation(eDir::Right);
					bloodeffect->PlayAnimation(eDir::Right);
				}
				else if (_mPlayer->GetDir() == eDir::Left)
				{
					hiteffect->PlayAnimation(eDir::Left);
					bloodeffect->PlayAnimation(eDir::Left);
				}
			}
			IsHit();
		}

		if (projectile != nullptr)
		{
			if (_mPlayer->GetAttState() != Player::eAttState::CHARGE_SLASH)
			{
				int num = rand() % 4;
				if (num == 0)
				{
					Resources::Find<Sound>(L"ENEMY_HIT_1")->Play(false);
					Resources::Find<Sound>(L"ENEMY_HIT_1")->SetVolume(30.f);
				}
				else if (num == 1)
				{
					Resources::Find<Sound>(L"ENEMY_HIT_2")->Play(false);
					Resources::Find<Sound>(L"ENEMY_HIT_2")->SetVolume(30.f);
				}
				else if (num == 2)
				{
					Resources::Find<Sound>(L"ENEMY_HIT_3")->Play(false);
					Resources::Find<Sound>(L"ENEMY_HIT_3")->SetVolume(30.f);
				}
				else if (num == 3)
				{
					Resources::Find<Sound>(L"ENEMY_HIT_4")->Play(false);
					Resources::Find<Sound>(L"ENEMY_HIT_4")->SetVolume(30.f);
				}
			}

			tr = projectile->GetComponent<Transform>();

			HitEffect* hiteffect = object::Instantiate<HitEffect>(eLayerType::Effect, Vector2(tr->GetPosition().x, tr->GetPosition().y)); // 몬스터위치에 히트 이펙트
			if (_mPlayer->GetAttState() == Player::eAttState::FIRST_SLASH)
			{
				hiteffect->SetActionNum(1);
			}
			else if (_mPlayer->GetAttState() == Player::eAttState::SECOND_SLASH)
			{
				hiteffect->SetActionNum(2);
			}
			else if (_mPlayer->GetAttState() == Player::eAttState::THIRD_SLASH)
			{
				hiteffect->SetActionNum(3);
			}
			if (_mPlayer->GetAttState() == Player::eAttState::CHARGE_SLASH)
			{
				Resources::Find<Sound>(L"HEAVY_ENEMY_HIT")->Play(false);
				Resources::Find<Sound>(L"HEAVY_ENEMY_HIT")->SetVolume(30.f);

				if (_mPlayer->GetDir() == eDir::Right)
				{
					hiteffect->PlayAnimation(eDir::Right, true);
				}
				else if (_mPlayer->GetDir() == eDir::Left)
				{
					hiteffect->PlayAnimation(eDir::Left, true);
				}
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