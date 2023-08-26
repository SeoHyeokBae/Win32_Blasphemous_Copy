#pragma once
#include "skScene.h"
#include "skPlayer.h"

namespace sk
{
	class TutorialScene : public Scene
	{
	public:
		TutorialScene();
		virtual ~TutorialScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void SceneEnter() override;
		virtual void SceneOut() override;

	private:
		Player* _mPlayer;

		float _mLImitLeftX;
		float _mLimitRightX;

	};

}
