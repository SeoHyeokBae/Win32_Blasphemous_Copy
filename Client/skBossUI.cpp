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
	{
	}
	BossUI::~BossUI()
	{
	}
	void BossUI::Initialize()
	{
		Texture* Boss_HpBar = Resources::Load<Texture>(L"boss_HpBar"
			, L"..\\Resources\\image\\Boss_HpBarFrame.bmp");
		Texture* Boss_Hp = Resources::Load<Texture>(L"boss_Hp"
			, L"..\\Resources\\image\\Boss_Hp2.bmp");
		
		_mHp = AddComponent<SpriteRenderer>();
		_mHp->SetImage(Boss_Hp);
		_mHp->SetAffectCamera(false);
		_mHp->SetOffset(Vector2(640.f, 688.f));
		
		_mHpBar = AddComponent<SpriteRenderer>();
		_mHpBar->SetImage(Boss_HpBar);
		_mHpBar->SetAffectCamera(false);
		_mHpBar->SetOffset(Vector2(640.f, 685.f));
	}
	void BossUI::Update()
	{
		GameObject::Update();

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
}