#include "skBossUI.h"
#include "skTransform.h"
#include "skMonster.h"
#include "skObject.h"
#include "skTimeMgr.h"
#include "skCamera.h"
#include "skResources.h"
#include "skSpriteRenderer.h"

namespace sk
{
	BossUI::BossUI() :
		 _mTime(0.f)
		,_mBoss(nullptr)
		,_mHp(nullptr)
		,_mName(nullptr)
		, _mbNameSet(false)
	{
	}
	BossUI::~BossUI()
	{
	}
	void BossUI::Initialize()
	{
		Texture* Boss_HpBar = Resources::Load<Texture>(L"boss_HpBar", L"..\\Resources\\image\\ui\\Boss_HpBarFrame.bmp");
		Texture* Boss_Hp = Resources::Load<Texture>(L"boss_Hp", L"..\\Resources\\image\\ui\\Boss_Hp2.bmp");
		Texture* elderbrother = Resources::Load<Texture>(L"elderbrother", L"..\\Resources\\image\\monster\\elderbrother\\elderbrother.bmp");		
		Texture* pietat = Resources::Load<Texture>(L"pietat", L"..\\Resources\\image\\monster\\pietat\\pietat.bmp");
		
		_mHp = AddComponent<SpriteRenderer>();
		_mHp->SetImage(Boss_Hp);
		_mHp->SetAffectCamera(false);
		_mHp->SetOffset(Vector2(640.f, 688.f));
		
		_mHpBar = AddComponent<SpriteRenderer>();
		_mHpBar->SetImage(Boss_HpBar);
		_mHpBar->SetAffectCamera(false);
		_mHpBar->SetOffset(Vector2(640.f, 685.f));

		_mName = AddComponent<SpriteRenderer>();
		_mName->SetAffectCamera(false);
		_mName->SetScale(Vector2(1.7f, 1.7f));
		_mName->SetOffset(Vector2(640.f, 640.f));
	}
	void BossUI::Update()
	{
		GameObject::Update();

		if (!(_mbNameSet))
		{
			_mbNameSet = true;
			Name();
		}

		Hp();
	}
	void BossUI::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BossUI::Hp()
	{
		float curhpratio = (float)(_mBoss->GetInfo().Hp / 150.f);
		_mHp->SetUIratio(curhpratio);
	}
	void BossUI::Name()
	{
		if (_mBoss->GetType() == Monster::eMonsType::ElderBrother)
		{
			_mName->SetImage(Resources::Find<Texture>(L"elderbrother"));
		}
		else if (_mBoss->GetType() == Monster::eMonsType::Pietat)
		{
			_mName->SetImage(Resources::Find<Texture>(L"pietat"));
		}
	}
}