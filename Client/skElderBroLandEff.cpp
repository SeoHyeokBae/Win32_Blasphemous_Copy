#include "skElderBroLandEff.h"
#include "skTexture.h"
#include "skResources.h"
#include "skAnimator.h"
#include "skTransform.h"
#include "skElderBrother.h"
#include "skElderCorpseEff.h"
#include "skObject.h"

namespace sk
{
	Vector2 ElderBroLandEff::_mPos = Vector2::Zero;
	ElderBroLandEff::ElderBroLandEff() :
		_mAnimator(nullptr)
	{
	}
	ElderBroLandEff::~ElderBroLandEff()
	{
	}
	void ElderBroLandEff::Initialize()
	{
		_mAnimator = AddComponent<Animator>();

		Texture* HardLand = Resources::Load<Texture>(L"HardLand", L"..\\Resources\\image\\monster\\elderbrother\\hardland.png");

		_mAnimator->CreateAnimation(L"MonsHardLand_right", HardLand, Vector2(0.0f, 0.0f), Vector2(120.f, 92.f)
			, 11, Vector2(40.0f, 30.0f), 0.1f);
		_mAnimator->CreateAnimation(L"MonsHardLand_left", HardLand, Vector2(0.0f, 0.0f), Vector2(120.f, 92.f)
			, 11, Vector2(-40.0f, 30.0f), 0.1f);
		_mAnimator->CreateAnimation(L"Jump_right", HardLand, Vector2(0.0f, 0.0f), Vector2(120.f, 92.f)
			, 11, Vector2(-20.0f, 30.0f), 0.06f);
		_mAnimator->CreateAnimation(L"Jump_left", HardLand, Vector2(0.0f, 0.0f), Vector2(120.f, 92.f)
			, 11, Vector2(20.0f, 30.0f), 0.06f);

		_mAnimator->SetScale(Vector2(2.0f, 2.0f));
		PlayAnimation();
	}
	void ElderBroLandEff::Update()
	{
		GameObject::Update();

		if (_mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	void ElderBroLandEff::PlayAnimation()
	{
		if (ElderBrother::GetMonState() == ElderBrother::eState::Jump)
		{
			if (ElderBrother::static_GetDir() == eDir::Right)
			{
				_mAnimator->PlayAnimation(L"Jump_right");
			}
			else if (ElderBrother::static_GetDir() == eDir::Left)
			{
				_mAnimator->PlayAnimation(L"Jump_left");
			}
		}
		else 
		{
			ElderCorpseEff* CorpseEff = object::Instantiate<ElderCorpseEff>(eLayerType::Effect, Vector2(_mPos.x - 125, _mPos.y + 100));
			CorpseEff->PlayAnimation();
			ElderCorpseEff* CorpseEff1 = object::Instantiate<ElderCorpseEff>(eLayerType::Effect, Vector2(_mPos.x + 130,_mPos.y + 30));
			CorpseEff1->PlayAnimation(true);
			ElderCorpseEff* CorpseEff2 = object::Instantiate<ElderCorpseEff>(eLayerType::Effect, Vector2(_mPos.x - 50, _mPos.y + 65));
			CorpseEff2->PlayAnimation();
			ElderCorpseEff* CorpseEff3 = object::Instantiate<ElderCorpseEff>(eLayerType::Effect, Vector2(_mPos.x + 50, _mPos.y + 0));
			CorpseEff3->PlayAnimation(true);

			if (ElderBrother::static_GetDir() == eDir::Right)
			{
				_mAnimator->PlayAnimation(L"MonsHardLand_right");

			}
			else if (ElderBrother::static_GetDir() == eDir::Left)
			{
				_mAnimator->PlayAnimation(L"MonsHardLand_left");
			}


		}
	}

	void ElderBroLandEff::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}