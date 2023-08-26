#pragma once
#include "skGameObject.h"
#include "skPlayer.h"

namespace sk
{
	class SpriteRenderer;

	class BossClearScene : public GameObject
	{
	public:
		BossClearScene();
		virtual ~BossClearScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void FadeIn();
		void FadeOut();


	private:
		Player* _mPlayer;
		SpriteRenderer* _mBlackBackgroundSr;
		SpriteRenderer* _mClearLogoSr;

		int _mCount;
		float _mTime;
		bool _mbFadeIn;
	};

}
