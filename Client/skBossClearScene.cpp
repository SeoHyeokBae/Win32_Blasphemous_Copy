#include "skBossClearScene.h"
#include "skTexture.h"
#include "skResources.h"
#include "skTimeMgr.h"
#include "skTransform.h"
#include "skRigidbody.h"
#include "skFirstBossScene.h"
#include "skSpriteRenderer.h"
#include "skSound.h"

namespace sk
{
	BossClearScene::BossClearScene() :
		_mPlayer(nullptr)
		, _mBlackBackgroundSr(nullptr)
		, _mClearLogoSr(nullptr)
		, _mCount(0)
		, _mTime(0.f)
		, _mbFadeIn(true)
	{
	}
	BossClearScene::~BossClearScene()
	{
	}
	void BossClearScene::Initialize()
	{
		Texture* BlackBackground = Resources::Load<Texture>(L"BlackBackground", L"..\\Resources\\image\\BlackBackground.bmp");
		Texture* ClearLogo = Resources::Load<Texture>(L"ClearLogo", L"..\\Resources\\image\\boss-defeated-screen-title.bmp");
		Resources::Load<Sound>(L"Fight_Ending", L"..\\Resources\\sound\\Boss_Fight_Ending.wav");

		_mBlackBackgroundSr = AddComponent<SpriteRenderer>();
		_mClearLogoSr = AddComponent<SpriteRenderer>();
		
		_mBlackBackgroundSr->SetAffectCamera(false);
		_mBlackBackgroundSr->SetOffset(Vector2(640.f,360.f));
		_mBlackBackgroundSr->SetAlpha(0.0f);
		_mBlackBackgroundSr->SetImage(BlackBackground);

		_mClearLogoSr->SetAffectCamera(false);
		_mClearLogoSr->SetScale(Vector2(2.0f, 2.0f));
		_mClearLogoSr->SetOffset(Vector2(640.f, 360.f));
		_mClearLogoSr->SetAlpha(0.0f);
		_mClearLogoSr->SetImage(ClearLogo);

		Resources::Find<Sound>(L"Fight_Ending")->Play(false);
	}

	void BossClearScene::Update()
	{
		if (_mbFadeIn)
		{
			FadeIn();
		}

		if (!(_mbFadeIn))
		{
			_mTime += TimeMgr::DeltaTime();
			if (_mTime >4.0f)
			{
				FadeOut();
			}
		}
	}

	void BossClearScene::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BossClearScene::FadeIn()
	{
		float alpha = _mBlackBackgroundSr->GetAlpha();
		alpha += 0.5f * TimeMgr::DeltaTime();
		_mBlackBackgroundSr->SetAlpha(alpha);

		float alpha1 = _mClearLogoSr->GetAlpha();
		alpha1 += 1.0f*TimeMgr::DeltaTime();
		_mClearLogoSr->SetAlpha(alpha1);

		if (alpha1 >= 1.0f)
		{
			alpha1 = 1.0f;
			_mClearLogoSr->SetAlpha(alpha1);

			_mbFadeIn = false;
		}
	}

	void BossClearScene::FadeOut()
	{
		float alpha = _mBlackBackgroundSr->GetAlpha();
		alpha -= 0.25f * TimeMgr::DeltaTime();
		_mBlackBackgroundSr->SetAlpha(alpha);

		float alpha1 = _mClearLogoSr->GetAlpha();
		alpha1 -= 0.5f * TimeMgr::DeltaTime();
		_mClearLogoSr->SetAlpha(alpha1);

		if (alpha == 0)
		{
			alpha1 = 0.0f;
			Destroy(this);
		}
	}

}