#pragma once
#include "skScene.h"
#include "skPlayer.h"

namespace sk
{
	class Scene05 : public Scene
	{
	public:
		Scene05();
		virtual ~Scene05();

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
