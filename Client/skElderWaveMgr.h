#pragma once
#include "skGameObject.h"

#define xlength 100.f

namespace sk
{
	class Animator;
	class Rigidbody;
	class Collider;

	class ElderWaveMgr : public GameObject
	{
	public:
		ElderWaveMgr();
		virtual ~ElderWaveMgr();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void PlayAnimation(int cnt);

		void SetPos(math::Vector2 pos) { _mPos = pos; }
		void SetLeft(bool left) { _mLeft = left; }

	private:
		math::Vector2 _mPos;
		bool _mLeft;
		int _mCount ;
		float _mTime;
	};
}
