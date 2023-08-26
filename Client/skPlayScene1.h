#pragma once
#include "skScene.h"
#include "skPlayer.h"
#include "skTexture.h"
#include "skCamera.h"

namespace sk
{
	class PlayScene1 : public Scene
	{
	public:
		PlayScene1();
		virtual ~PlayScene1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void SceneEnter() override;
		virtual void SceneOut() override;


	private:
		Player* _mPlayer;
		Texture* _mTexture;
		Camera* _mCamera;

		float _mLimitLeftX;
		float _mLimitRightX;
	};

}