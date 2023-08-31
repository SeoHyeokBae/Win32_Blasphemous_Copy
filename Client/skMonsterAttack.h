#pragma once
#include "skGameObject.h"
#include "skPlayer.h"
#include "skMonster.h"
#include "skShieldMan.h"
#include "skPietat.h"

namespace sk
{
	class Collider;

	class MonsterAttack : public GameObject
	{
	public:
		MonsterAttack();
		virtual ~MonsterAttack();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		__forceinline void SetMons(Monster* mons)
		{
			_mMonster = mons;
			_mDir = mons->GetDir();
			_mType = _mMonster->GetType();
		}
		__forceinline GameObject* GetOwner() { return _mPlayer; }
		void MonAttCollider();

		eDir GetDir() { return _mDir; }
		Monster::eMonsType GetMonsType() { return _mType; }
	private:
		Collider* _mCollider;
		Player* _mPlayer;
		Monster* _mMonster;

		Monster::eState _mState;
		Monster::eMonsType _mType;

		eDir  _mDir;
		float _mTime;
		bool _mIsHit;
	};

}