#include "skDodgeEffect.h"
#include "skPlayer.h"
#include "skTexture.h"
#include "skResources.h"
#include "skAnimator.h"
#include "skObject.h"
#include "skTransform.h"

namespace sk
{
	DodgeEffect::DodgeEffect():
		 _mAnimator(nullptr)
	{
	}
	DodgeEffect::~DodgeEffect()
	{
	}
	void DodgeEffect::Initialize()
	{
		_mAnimator = AddComponent<Animator>();

		Texture* DodgeDust = Resources::Load<Texture>(L"DodgeDust", L"..\\Resources\\image\\effect\\DodgeDust.png");
		//Texture* DodgeDustStop = Resources::Load<Texture>(L"DodgeDustStop"
		//	, L"..\\Resources\\image\\DodgeDustStop.png");

		_mAnimator->CreateAnimation(L"DodgeDust_right", DodgeDust, Vector2(0.0f, 0.0f), Vector2(80.f, 35.f), 11, Vector2(-60.0f, 220.0f), 0.06f);
		_mAnimator->CreateAnimation(L"DodgeDust_left", DodgeDust, Vector2(0.0f, 35.0f), Vector2(80.f, 35.f), 11, Vector2(60.0f, 220.0f), 0.06f);
		//_mAnimator->CreateAnimation(L"DodgeDustStop_right", DodgeDustStop, Vector2(0.0f, 0.0f), Vector2(45.f, 40.f)
		//	, 11, Vector2(-60.0f, 220.0f), 0.06f);
		//_mAnimator->CreateAnimation(L"DodgeDustStop_left", DodgeDustStop, Vector2(0.0f, 40.0f), Vector2(45.f, 40.f)
		//	, 11, Vector2(60.0f, 220.0f), 0.06f);
		
		_mAnimator->SetScale(Vector2(2.0f,2.0f));
		
	}
	void DodgeEffect::Update()
	{
		GameObject::Update();

		if (_mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	void DodgeEffect::PlayAnimation(eDir dir)
	{
		if (dir == eDir::Right)
		{
			_mAnimator->PlayAnimation(L"DodgeDust_right", false);
		}
		else if (dir == eDir::Left)
		{
			_mAnimator->PlayAnimation(L"DodgeDust_left", false);
		}
	}

	void DodgeEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}