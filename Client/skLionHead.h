#pragma once
#include "skMonster.h"
#include "skAnimator.h"
#include "skRigidbody.h"
#include "skCollider.h"
#include "skTransform.h"

#define scale 100.f
namespace sk
{
	class LionHead : public Monster
	{
		enum class eState
		{
			IDLE,
			Ready,
			Attack,
			Patrol,
			Trace,
			Hit,
			Dead,
			BackMove,
			None,
		};
	public:
		LionHead();
		virtual ~LionHead();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		virtual eMonsType GetType() { return _mType; }
		virtual Info GetInfo() { return _mMonsInfo; }
		virtual void SetInfo(Info monsinfo) { _mMonsInfo = monsinfo; }

		eDir GetDir() { return _mDir; }
		void Idle();
		void Ready();
		void Patrol();
		void Trace();
		void Attack();
		void Hit();
		void Dead();
		void BackMove();

		void UpdateState();
		void UpdateAnimation();

	private:
		eMonsType _mType;
		eState _mCurState;
		eState _mPrvState;
		eDir _mDir;
		eDir _mPrvDir;
		Info _mMonsInfo;

		bool _mbCanAtt;
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

