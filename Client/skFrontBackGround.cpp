#include "skFrontBackGround.h"
#include "skTransform.h"
#include "skTimeMgr.h"
#include "skInput.h"
#include "skSpriteRenderer.h"

namespace sk
{
	FrontBackGround::FrontBackGround()
	{
	}
	FrontBackGround::~FrontBackGround()
	{
	}
	void FrontBackGround::Initialize()
	{
	}
	void FrontBackGround::Update()
	{
		GameObject::Update();

		// 점점 투명
		//SpriteRenderer* sr = GetComponent<SpriteRenderer>();
		//float alpha = sr->GetAlpha();
		//alpha -= 0.2f * TimeMgr::DeltaTime();
		//sr->SetAlpha(alpha);
	}
	void FrontBackGround::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}
