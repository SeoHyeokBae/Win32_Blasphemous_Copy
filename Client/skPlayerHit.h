#pragma once
#pragma once
#include "skPlayerHit.h"
#include "skGameObject.h"

namespace sk
{
	class Animator;

	class PlayerHit : public GameObject
	{
	public:
		PlayerHit();
		virtual ~PlayerHit();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void PlayAnimation(eDir dir);

	private:
		Animator* _mAnimator;

	};

}

