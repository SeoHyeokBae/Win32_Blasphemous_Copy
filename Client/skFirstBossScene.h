#pragma once
#include "skScene.h"
#include "skCamera.h"
#include "skPlayer.h"

namespace sk
{
	class Player;
	class ElderBrother;
	class SpriteRenderer;

	class FirstBossScene : public Scene
	{
	public:
		FirstBossScene();
		virtual ~FirstBossScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void SceneEnter() override;
		virtual void SceneOut() override;

		static bool _mbCutSceneOn;
		static bool _mbCanMakeBoss;
	private:
		Player* _mPlayer;
		ElderBrother* _mBoss;
		Camera* _mCamera;
		SpriteRenderer* _mSpriteRender;

		float _mLImitLeftX;
		float _mLimitRightX;
	};
}


