#include "skLandDust.h"
#include "skPlayer.h"
#include "skTexture.h"
#include "skResources.h"
#include "skAnimator.h"
#include "skObject.h"
#include "skTransform.h"

namespace sk
{
	LandDust::LandDust() :
		_mAnimator(nullptr)
	{
	}
	LandDust::~LandDust()
	{
	}
	void LandDust::Initialize()
	{
		_mAnimator = AddComponent<Animator>();

		Texture* DodgeDust = Resources::Load<Texture>(L"land_dust", L"..\\Resources\\image\\monster\\pietat\\land_dust.png");

		_mAnimator->CreateAnimation(L"land_dust_right", DodgeDust, Vector2(0.0f, 0.0f), Vector2(100.f, 50.f)
			, 7, Vector2(-60.0f, 0.0f), 0.06f);
		_mAnimator->CreateAnimation(L"land_dust_left", DodgeDust, Vector2(0.0f, 50.0f), Vector2(100.f, 50.f)
			, 7, Vector2(60.0f, 0.0f), 0.06f);

		_mAnimator->SetScale(Vector2(2.0f, 2.0f));

	}
	void LandDust::Update()
	{
		GameObject::Update();

		if (_mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	void LandDust::PlayAnimation(eDir dir)
	{
		if (dir == eDir::Right)
		{
			_mAnimator->PlayAnimation(L"land_dust_right", false);
		}
		else if (dir == eDir::Left)
		{
			_mAnimator->PlayAnimation(L"land_dust_left", false);
		}
	}

	void LandDust::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}