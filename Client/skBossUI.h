#pragma once
#include "skGameObject.h"
#include "skMonster.h"

namespace sk
{
	class SpriteRenderer;

	class BossUI : public GameObject
	{
	public:
		BossUI();
		virtual ~BossUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		__forceinline void SetBoss(Monster* monster)
		{
			_mBoss = monster;
		}

		void Hp();

	private:
		float _mTime;
		SpriteRenderer* _mHpBar;
		SpriteRenderer* _mHp;
		Monster* _mBoss;
	};

}