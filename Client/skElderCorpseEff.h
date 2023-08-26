#pragma once
#include "skGameObject.h"

namespace sk
{
	class Animator;
	class Rigidbody;

	class ElderCorpseEff : public GameObject
	{
	public:
		ElderCorpseEff();
		virtual ~ElderCorpseEff();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;


		void PlayAnimation(bool Left = false);

	private:
		Animator* _mAnimator;
		Rigidbody* _mRigidbody;
	};
}