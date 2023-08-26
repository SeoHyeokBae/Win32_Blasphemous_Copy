#include "skGuideBotton.h"
#include "skTexture.h"
#include "skResources.h"
#include "skSpriteRenderer.h"
#include "skInput.h"

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
		SpriteRenderer* sr = GetComponent<SpriteRenderer>();
		sr->SetImage(Press_F);
		sr->SetScale(Vector2(2.f, 2.f));
	}
	void GuideBotton::Update()
	{
		GameObject::Update();

		if (Input::GetKeyDown(eKeyCode::F))
		{
			Destroy(this);
		}

	}
	void GuideBotton::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}