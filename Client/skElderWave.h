#pragma once
#include "skGameObject.h"

namespace sk
{
	class Animator;
	class Rigidbody;
	class Collider;

	class ElderWave : public GameObject
	{
	public:
		ElderWave();
		virtual ~ElderWave();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		class  Texture* _mFloorTexture;

		void PixelCollision();
		void PlayAnimation();

	private:
		Animator* _mAnimator;
		Rigidbody* _mRigidbody;
		Collider* _mCollider;
	};
}
