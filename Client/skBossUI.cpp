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
	{
	}
	BossUI::~BossUI()
	{
	}
	void BossUI::Initialize()
	{
		Texture* Boss_HpBar = Resources::Load<Texture>(L"boss_HpBar"
			, L"..\\Resources\\image\\Boss_HpBarFrame.bmp");
		SpriteRenderer* sr = AddComponent<SpriteRenderer>();
		sr->SetImage(Boss_HpBar);
		//sr->SetScale(Vector2(2.0f, 2.0f));
		sr->SetAffectCamera(false);
		sr->SetOffset(Vector2(640.f, 685.f));
	}
	void BossUI::Update()
	{
		GameObject::Update();
	}
	void BossUI::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}