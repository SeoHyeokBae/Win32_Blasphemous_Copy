#pragma once
#include "skGameObject.h"

namespace sk
{
	class BossUI : public GameObject
	{
	public:
		BossUI();
		virtual ~BossUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		float _mTime;
	};

}