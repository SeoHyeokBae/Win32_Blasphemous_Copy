#pragma once
#include "skGameObject.h"

namespace sk
{
	class Animator;
	class Rigidbody;
	class Collider;

	class Thorn : public GameObject
	{
	public:
		Thorn();
		virtual ~Thorn();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void PlayAnimation();

	private:
		Animator* _mAnimator;
		Collider* _mCollider;
	};
}
