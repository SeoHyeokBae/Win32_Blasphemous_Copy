#pragma once
#include "skGameObject.h"

namespace sk
{
	class Animator;
	class Rigidbody;

	class ElderBroPrivateCutScene : public GameObject
	{
	public:
		ElderBroPrivateCutScene();
		virtual ~ElderBroPrivateCutScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		static void SetCanPlay(bool enable) { _mbCanPlay = enable; }
	private:
		Animator* _mAnimator;
		Rigidbody* _mRigidbody;
		float _mTime;
		int _mCount;
		bool _mbJump;

		static bool _mbCanPlay;
	};

}

