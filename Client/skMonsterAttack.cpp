#include "skMonsterAttack.h"
#include "skPlayer.h"
#include "skTransform.h"
#include "skCollider.h"
#include "skCollisionMgr.h"
#include "skMonster.h"
#include "skObject.h"
#include "skHitEffect.h"
#include "skTimeMgr.h"
#include "skCamera.h"

namespace sk
{
	MonsterAttack::MonsterAttack() :
		_mPlayer(nullptr)
		, _mMonster(nullptr)
		, _mTime(0.f)
		, _mIsHit(false)
		, _mDir(eDir::None)
		, _mType(Monster::eMonsType::None)
	{
	}
	MonsterAttack::~MonsterAttack()
	{
	}
	void MonsterAttack::Initialize()
	{
		_mCollider = AddComponent<Collider>();
		_mCollider->SetNotColColor(RGB(255, 255, 50));
	}
	void MonsterAttack::Update()
	{
		GameObject::Update();

		// 시전후 colliderbox 삭제
		_mTime += TimeMgr::DeltaTime();
		if (_mTime >= 0.15f)
		{
			Destroy(this);
		}
	}
	void MonsterAttack::MonAttCollider()
	{
		switch (_mMonster->GetType())
		{
		case Monster::eMonsType::Shieldman:
			if (_mDir == eDir::Right)
			{
				_mCollider->SetSize(Vector2(110.0f, 100.0f));
				_mCollider->SetOffset(Vector2(55.0f, 0.0f));
			}
			else if (_mDir == eDir::Left)
			{
				_mCollider->SetSize(Vector2(110.0f, 100.0f));
				_mCollider->SetOffset(Vector2(-55.0f, 0.0f));
			}
			break;
		case Monster::eMonsType::LionHead:
			if (_mDir == eDir::Right)
			{
				_mCollider->SetSize(Vector2(120.0f, 200.0f));
				_mCollider->SetOffset(Vector2(235.0f, 50.0f));
			}
			else if (_mDir == eDir::Left)
			{
				_mCollider->SetSize(Vector2(120.0f, 200.0f));
				_mCollider->SetOffset(Vector2(-235.0f, 50.0f));
			}
			break;
		case Monster::eMonsType::ElderBrother:
			if (_mDir == eDir::Right)
			{
				_mCollider->SetSize(Vector2(250.0f, 150.0f));
				_mCollider->SetOffset(Vector2(0.0f, 50.0f));
			}
			else if (_mDir == eDir::Left)
			{
				_mCollider->SetSize(Vector2(250.0f, 150.0f));
				_mCollider->SetOffset(Vector2(0.0f, 50.0f));
			}
			break;
		}


	}

	void MonsterAttack::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void MonsterAttack::OnCollisionEnter(Collider* other)
	{
	}
	void MonsterAttack::OnCollisionStay(Collider* other)
	{
	}
	void MonsterAttack::OnCollisionExit(Collider* other)
	{
	}
}