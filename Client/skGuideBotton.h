#pragma once
#include "skGameObject.h"
#include "skTexture.h"

namespace sk
{
	class GuideBotton : public GameObject
	{
	public:

		GuideBotton();
		virtual ~GuideBotton();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
	};
}