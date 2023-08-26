#pragma once
#include "skGameObject.h"

namespace sk
{
	class Animator;

	class DodgeEffect : public GameObject
	{
	public:
		DodgeEffect();
		virtual ~DodgeEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void PlayAnimation(eDir dir);

	private:
		Animator* _mAnimator;

	};

}

