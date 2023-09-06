#pragma once
#include "skGameObject.h"
#include "skTexture.h"

namespace sk
{
	class SpriteRenderer;
	class GuideBotton : public GameObject
	{
	public:

		GuideBotton();
		virtual ~GuideBotton();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void Death();

	private:
		SpriteRenderer* _mSpriteRender;
		bool _mbFadeIn;
		bool _mbScene04;
	};
}