#pragma once
#include "skGameObject.h"

namespace sk
{
	class Animator;

	class ElderBroLandEff : public GameObject
	{
	public:
		ElderBroLandEff();
		virtual ~ElderBroLandEff();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;


		void PlayAnimation();
		static void SetPos(math::Vector2 pos) { _mPos = pos; }
	private:
		Animator* _mAnimator;
		static math::Vector2 _mPos;
	};
}