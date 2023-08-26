#include "skGuideBotton.h"
#include "skTexture.h"
#include "skResources.h"
#include "skSpriteRenderer.h"
#include "skInput.h"
#include "skSceneMgr.h"

namespace sk
{
	GuideBotton::GuideBotton()
	{

	}
	GuideBotton::~GuideBotton()
	{
	}
	void GuideBotton::Initialize()
	{
		AddComponent<SpriteRenderer>();
		Texture* Press_F = Resources::Load<Texture>(L"press_f", L"..\\Resources\\image\\KB_F.bmp");
		Texture* Press_E = Resources::Load<Texture>(L"press_E", L"..\\Resources\\image\\KB_E.bmp");
		SpriteRenderer* sr = GetComponent<SpriteRenderer>();

		if (SceneMgr::GetActiveScene()->GetName() == L"PlayScene1")
		{
			sr->SetImage(Press_F);
		}
		if (SceneMgr::GetActiveScene()->GetName() == L"Scene04")
		{
			sr->SetImage(Press_E);
		}
		sr->SetScale(Vector2(2.f, 2.f));
	}
	void GuideBotton::Update()
	{
		GameObject::Update();
		
		// 나중에 조건
		if (Input::GetKeyDown(eKeyCode::F) || Input::GetKeyDown(eKeyCode::E))
		{
			Destroy(this);
		}

	}
	void GuideBotton::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}