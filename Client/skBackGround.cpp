#include "skBackGround.h"
#include "skTransform.h"
#include "skTimeMgr.h"
#include "skInput.h"
#include "skSpriteRenderer.h"

namespace sk
{
	BackGround::BackGround()
	{
	}
	BackGround::~BackGround()
	{
	}
	void BackGround::Initialize()
	{
	}
	void BackGround::Update()
	{
		GameObject::Update();
		
		// 점점 투명
		//SpriteRenderer* sr = GetComponent<SpriteRenderer>();
		//float alpha = sr->GetAlpha();
		//alpha -= 0.2f * TimeMgr::DeltaTime();
		//sr->SetAlpha(alpha);
	}
	void BackGround::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}
