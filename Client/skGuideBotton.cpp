#include "skGuideBotton.h"
#include "skTexture.h"
#include "skResources.h"
#include "skSpriteRenderer.h"
#include "skInput.h"
#include "skSceneMgr.h"
#include "skTimeMgr.h"

namespace sk
{
	GuideBotton::GuideBotton() :
		_mSpriteRender(nullptr)
		, _mbFadeIn(false)
		, _mbScene04(false)
	{

	}
	GuideBotton::~GuideBotton()
	{
	}
	void GuideBotton::Initialize()
	{
		_mSpriteRender = AddComponent<SpriteRenderer>();
		Texture* Press_F = Resources::Load<Texture>(L"press_f", L"..\\Resources\\image\\KB_F.bmp");
		Texture* Press_E = Resources::Load<Texture>(L"press_E", L"..\\Resources\\image\\KB_E.bmp");
		Texture* Press_K = Resources::Load<Texture>(L"press_K", L"..\\Resources\\image\\KB_K.bmp");

		if (SceneMgr::GetActiveScene()->GetName() == L"PlayScene1")
		{
			_mSpriteRender->SetImage(Press_F);
			_mSpriteRender->SetAlpha(0.f);
			_mbFadeIn = true;
		}

		if (SceneMgr::GetActiveScene()->GetName() == L"TutorialScene")
		{
			_mSpriteRender->SetImage(Press_K);
			_mSpriteRender->SetAlpha(0.2f);
			_mbFadeIn = true;
		}

		if (SceneMgr::GetActiveScene()->GetName() == L"Scene04")
		{
			_mSpriteRender->SetImage(Press_E);
			_mSpriteRender->SetAlpha(0.f);
			_mbFadeIn = true;
		}
		_mSpriteRender->SetScale(Vector2(2.f, 2.f));

	}
	void GuideBotton::Update()
	{
		GameObject::Update();

		if (_mbFadeIn)
		{
			float alpha = _mSpriteRender->GetAlpha();
			alpha += 0.5f * TimeMgr::DeltaTime();
			_mSpriteRender->SetAlpha(alpha);

			if (alpha >= 1.0f)
			{
				alpha = 1.0f;
				_mSpriteRender->SetAlpha(alpha);

				_mbFadeIn = false;
			}
		}
		
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

	void GuideBotton::Death()
	{
		Destroy(this);
	}
}