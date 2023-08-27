#pragma once
#include "skNpc.h"

namespace sk
{
	class Player;
	class NpcDeosgracias : public Npc
	{
	public:
		NpcDeosgracias();
		virtual ~NpcDeosgracias();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		static void SetCanActive(bool enable) { _mCanActive = enable; }
	private:
		static bool _mCanActive;
		Player* _mPlayer;
	};
}
