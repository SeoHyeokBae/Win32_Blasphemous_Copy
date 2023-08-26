#pragma once
#include "skGameObject.h"
#include "skPlayer.h"

namespace sk
{
	class SpriteRenderer;
	class PlayerUI : public GameObject
	{
	public:
		PlayerUI();
		virtual ~PlayerUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		__forceinline void SetPlayer(Player* player)
		{
			_mPlayer = player;
		}
	private:
		Player* _mPlayer;
		SpriteRenderer* _mHpBar;
		SpriteRenderer* _mFlask1;
		SpriteRenderer* _mFlask2;
		Player::eState _mState;
		Player::eAttState _mAttState;
		float _mTime;
		int _mFlask;
	};

}