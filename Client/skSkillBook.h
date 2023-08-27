#pragma once
#include "skGameObject.h"

namespace sk
{
	class SkillBook : public GameObject
	{
	public:
		SkillBook();
		virtual ~SkillBook();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		int _mCount;
	};
}

