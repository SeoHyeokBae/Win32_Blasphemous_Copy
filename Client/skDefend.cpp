#include "skDefend.h"
#include "skTransform.h"
#include "skCollider.h"
#include "skCollisionMgr.h"
#include "skMonster.h"
#include "skObject.h"
#include "skHitEffect.h"
#include "skTimeMgr.h"
#include "skCamera.h"
#include "skMonsterAttack.h"

namespace sk
{
	Defend::Defend() :
		_mPlayer(nullptr)
		, _mMonster(nullptr)
		, _mTime(0.f)
		, _mState(Player::eState::NONE)
		, _mIsHit(false)
	{
	}
	Defend::~Defend()
	{
	}
	void Defend::Initialize()
	{
		_mCollider = AddComponent<Collider>();
		_mCollider->SetNotColColor(RGB(255, 255, 50));
	}
	void Defend::Update()
	{
		GameObject::Update();

		// 시전후 colliderbox 삭제
		_mTime += TimeMgr::DeltaTime();
		if (_mTime >= 0.15f)
		{
			Destroy(this);
		}
	}
	void Defend::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}
	void Defend::DefendCollider()
	{

		if (_mPlayer->GetDir() == eDir::Right)
		{
			_mCollider->SetSize(Vector2(70.0f, 25.0f));
			_mCollider->SetOffset(Vector2(25.0f, 165.0f));
		}
		else if (_mPlayer->GetDir() == eDir::Left)
		{
			_mCollider->SetSize(Vector2(70.0f, 25.0f));
			_mCollider->SetOffset(Vector2(-25.0f, 165.0f));
		}

	}
	void Defend::OnCollisionEnter(Collider* other)
	{
		//MonsterAttack* monatt = dynamic_cast<MonsterAttack*>(other->GetOwner());


		//if (monatt != nullptr)
		//{
		//	_mPlayer->SetDefendOn(true);
		//	
		//	Transform* tr = _mPlayer->GetComponent<Transform>();
		//	Vector2 playerpos = tr->GetPosition();
		//	if (_mPlayer->GetDir() == eDir::Right)
		//	{
		//		_mPlayer->GetComponent<Animator>()->PlayAnimation(L"ParrySuccess_right"); 
		//		playerpos.x -= 10.f;
		//	}
		//	else if (_mPlayer->GetDir() == eDir::Left)
		//	{
		//		_mPlayer->GetComponent<Animator>()->PlayAnimation(L"ParrySuccess_left");
		//		playerpos.x += 10.f;
		//	}
		//	tr->SetPosition(playerpos);

		//	Destroy(this);
		//}

	}
	void Defend::OnCollisionStay(Collider* other)
	{
	}
	void Defend::OnCollisionExit(Collider* other)
	{
	}
}