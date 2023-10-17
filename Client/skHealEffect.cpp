#include "skHealEffect.h"
#include "skPlayer.h"
#include "skTexture.h"
#include "skResources.h"
#include "skAnimator.h"
#include "skObject.h"
#include "skTransform.h"

namespace sk
{
	HealEffect::HealEffect() :
		_mAnimator(nullptr)
	{
	}
	HealEffect::~HealEffect()
	{
	}
	void HealEffect::Initialize()
	{
		_mAnimator = AddComponent<Animator>();

		Texture* HealEff = Resources::Load<Texture>(L"HealEff", L"..\\Resources\\image\\effect\\healeff.png");

		_mAnimator->CreateAnimation(L"HealEff_right", HealEff, Vector2(0.0f, 0.0f), Vector2(100.f, 135.f)
			, 23, Vector2(0.0f, 130.0f), 0.07f);
		_mAnimator->CreateAnimation(L"HealEff_left", HealEff, Vector2(0.0f, 135.0f), Vector2(100.f, 135.f)
			, 23, Vector2(10.0f, 130.0f), 0.07f);

		_mAnimator->SetScale(Vector2(2.0f, 2.0f));
	}
	void HealEffect::Update()
	{
		GameObject::Update();

		if (_mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	void HealEffect::PlayAnimation(eDir dir)
	{
		if (dir == eDir::Right)
		{
			_mAnimator->PlayAnimation(L"HealEff_right", false);
		}
		else if (dir == eDir::Left)
		{
			_mAnimator->PlayAnimation(L"HealEff_left", false);
		}
	}

	void HealEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}