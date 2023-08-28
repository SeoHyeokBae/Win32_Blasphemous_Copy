#pragma once
#include "skMonster.h"
#include "skAnimator.h"
#include "skRigidbody.h"
#include "skCollider.h"
#include "skTransform.h"

#define scale 100.f
namespace sk
{
	class Pietat : public Monster
	{
	public:
		enum class eState
		{
			IDLE,
			OneStep,
			TwoStep,
			Slash,
			Stomp,
			Ready,
			Attack,
			Trace,
			Hit,
			Dead,
			None,
		};

		Pietat();
		virtual ~Pietat();

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

		void SetDestroy(bool enable) { _mbCanDestroy = enable; }

		class  Texture* _mFloorTexture;

		static eDir GetDir() { return _mDir; }
		static eState GetMonState() { return _mCurState; }


		void Idle();
		void OneStep();
		void Slash();
		void Stomp();
		void Ready();
		void Attack();
		void Hit();
		void Dead();

		void ChangeOfDir();
		void UpdateState();
		void UpdateAnimation();

	private:
		static eState _mCurState;
		static eDir _mDir;
		eMonsType _mType;
		eState _mPrvState;
		eDir _mPrvDir;
		Info _mMonsInfo;

		Vector2 _mTargetPos;

		bool _mbCanAtt;
		bool _mIsHit;
		bool _mbDeadScene;
		bool _mbCanDestroy;
		float _mPlayerDistance;
		float _mDelay;
		float _mAttDelay;
		float _mDestroyTime;
		int _mActionCount;
		int _mHitDmg;

		Animator* _mAnimator;
		Collider* _mCollider;
		Rigidbody* _mRigidbody;
		Transform* _mTransform;

		// 패턴 점프1 어택1 
	};
}

