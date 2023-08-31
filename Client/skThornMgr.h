#pragma once
#include "skGameObject.h"

#define Thorn_length 128.f

namespace sk
{
	class Animator;
	class Rigidbody;
	class Collider; 

	class ThornMgr : public GameObject
	{
	public:
		enum class eAttType
		{
			Stomp,
			Smash,
			None,
		};
		ThornMgr();
		virtual ~ThornMgr();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void PlayAnimation(int cnt);
		void Stomp();
		void Smash();


		void SetPos(math::Vector2 pos) { _mPos = pos; }
		void SetLeft(bool left) { _mLeft = left; }
		void SetPhase2(bool enable) { _mbPhase2 = enable; }
		void SetAttType(eAttType type) { _mType = type; }

	private:
		math::Vector2 _mPos;
		bool _mLeft;
		int _mCount;
		float _mTime;
		bool _mbPhase2;

		eAttType _mType;
	};
}
