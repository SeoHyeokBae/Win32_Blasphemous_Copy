#pragma once
#include "skGameObject.h"
#include "skTexture.h"

namespace sk
{
	class Monster : public GameObject
	{
	public:


		enum class eMonsType
		{
			Shieldman,
			LionHead,
			ElderBrother,
			Pietat,
			Stoner,
			None,
		};

		struct Info
		{
			int Hp;
			int Dmg;
		};

		Monster();
		virtual ~Monster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		virtual void UpdateState();
		virtual void UpdateAnimation();

		virtual void SetInfo(Info monsinfo) { _mMonsterInfo = monsinfo; }
		virtual Info GetInfo() { return _mMonsterInfo; }
		virtual eDir GetDir() { return _mDir; }

		virtual eMonsType GetType() { return _mType; }
	private:
		eMonsType _mType;
		eDir _mDir;
		Info _mMonsterInfo;
		int _mHitDmg;
	};
}


