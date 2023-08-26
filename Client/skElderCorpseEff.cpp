#include "skElderCorpseEff.h"
#include "skTexture.h"
#include "skResources.h"
#include "skAnimator.h"
#include "skTransform.h"
#include "skElderBrother.h"
#include "skRigidbody.h"

namespace sk
{
	ElderCorpseEff::ElderCorpseEff() :
		_mAnimator(nullptr)
		,_mRigidbody(nullptr)
	{
	}
	ElderCorpseEff::~ElderCorpseEff()
	{
	}
	void ElderCorpseEff::Initialize()
	{
		_mAnimator = AddComponent<Animator>();
		_mRigidbody = AddComponent<Rigidbody>();

		Texture* Corpse = Resources::Load<Texture>(L"Corpse"
			, L"..\\Resources\\image\\elderBrother_corpse.bmp");

		_mAnimator->CreateAnimation(L"corpse_right", Corpse, Vector2(0.0f, 0.0f), Vector2(128.f, 128.f)
			, 12, Vector2(0.0f, 0.0f), 0.1f);
		_mAnimator->CreateAnimation(L"corpse_left", Corpse, Vector2(0.0f, 128.0f), Vector2(128.f, 128.f)
			, 12, Vector2(0.0f, 0.0f), 0.1f);

		_mAnimator->SetScale(Vector2(2.0f, 2.0f));

		Vector2 velocity = _mRigidbody->GetVelocity();
		velocity.y = -550.0f;
		_mRigidbody->SetVelocity(velocity);
	}
	void ElderCorpseEff::Update()
	{
		GameObject::Update();

		if (_mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	void ElderCorpseEff::PlayAnimation(bool Left)
	{
		if (!(Left))
			_mAnimator->PlayAnimation(L"corpse_right");

		if (Left)
			_mAnimator->PlayAnimation(L"corpse_left");

	}

	void ElderCorpseEff::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}