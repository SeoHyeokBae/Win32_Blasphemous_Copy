#pragma once
#include "skNpc.h"

namespace sk
{
	class Animator;

	class NpcPrayerTable : public Npc
	{
	public:
		NpcPrayerTable();
		virtual ~NpcPrayerTable();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		Animator* _mAnimator;
	};
}
