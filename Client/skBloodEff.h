#pragma once
#include "skGameObject.h"

namespace sk
{
	class Animator;
	class Collider;

	class BloodEff : public GameObject
	{
	public:
		BloodEff();
		virtual ~BloodEff();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void PlayAnimation(eDir dir, bool charge = false);
		void SetActionNum(int num) { _mActionNum = num; }
	private:
		Animator* _mAnimator;
		Collider* _mCollider;
		int _mActionNum;
	};

}


