#pragma once
#include "skGameObject.h"
#include "skPlayer.h"

namespace sk
{
	class PlayerUI : public GameObject
	{
	public:
		PlayerUI();
		virtual ~PlayerUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		Player* _mPlayer;

		Player::eState _mState;
		Player::eAttState _mAttState;
		float _mTime;
	};

}