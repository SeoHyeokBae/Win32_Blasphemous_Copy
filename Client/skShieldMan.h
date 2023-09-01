#pragma once
#include "skMonster.h"
#include "skAnimator.h"
#include "skRigidbody.h"
#include "skCollider.h"
#include "skTransform.h"

#define scale 100.f
namespace sk
{
	class ShieldMan : public Monster
	{
	public:
		enum class eState
		{
			IDLE,
			Ready,
			Attack,
			Patrol,
			Trace,
			Hit,
			Sturn,
			Dead,
			None,
		};

		ShieldMan();
		virtual ~ShieldMan();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		virtual eMonsType GetType() { return _mType; }
		virtual Info GetInfo() { return _mMonsInfo; }
		virtual void SetInfo(Info monsinfo) { _mMonsInfo = monsinfo; }

		virtual void SetIsHit(bool hit, int dmg) { _mIsHit = hit, _mHitDmg = dmg; }
		virtual bool GetIsHit() { return _mIsHit; }


		eDir GetDir() { return _mDir; }
		void Idle();
		void Ready();
		void Patrol();
		void Trace();
		void Attack();
		void Hit();
		void Sturn();
		void Dead();

		void UpdateInfo();
		void UpdateState();
		void UpdateAnimation();

	private:
		eMonsType _mType;
		eState _mCurState;
		eState _mPrvState;
		eDir _mDir;
		eDir _mPrvDir;
		Info _mMonsInfo;
		
		bool _mbSturn;
		bool _mIsHit;
		float _mPlayerDistance;
		float _mDelay;
		float _mAttDelay;
		int _mActionCount;
		int _mHitDmg;

		Animator* _mAnimator;
		Collider* _mCollider;
		Rigidbody* _mRigidbody;
		Transform* _mTransform;
		
	};
}

