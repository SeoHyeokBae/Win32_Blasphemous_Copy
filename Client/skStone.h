#pragma once
#include "skGameObject.h"
#include "skProjectile.h"

namespace sk
{
	class Animator;
	class Rigidbody;
	class Collider;
	class Transform;

	class Stone : public Projectile
	{
	public:
		Stone();
		virtual ~Stone();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Move();
		void Death();


		void SetDir(eDir dir) { _mDir = dir; }
		void SetTarget(math::Vector2 target) { _mTarget = target; }
		void SetStartPos(math::Vector2 pos) { _mStartPos = pos; }

	private:
		Animator* _mAnimator;
		Rigidbody* _mRigidbody;
		Collider* _mCollider;
		Transform* _mTransform;

		math::Vector2 _mTarget;
		math::Vector2 _mStartPos;
		eDir _mDir;
		bool _mbShootUp;
		bool _mbCanDeath;
		bool _mbUnGround;
		bool _mbIgnore;
	};
}