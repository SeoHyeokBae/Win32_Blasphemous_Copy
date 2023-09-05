#pragma once
#include "skScene.h"

namespace sk
{
	class BottonUI;
	class Sound;
	class UI;

	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void SceneEnter() override;
		virtual void SceneOut() override;
	private:
		BottonUI* _mStartbutton;
		BottonUI* _mExitbutton;
		UI* _mSelectEff;
	};

}


