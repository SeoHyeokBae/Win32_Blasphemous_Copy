#include "skBloodEff.h"
#include "skPlayer.h"
#include "skTexture.h"
#include "skResources.h"
#include "skAnimator.h"
#include "skObject.h"
#include "skTransform.h"

namespace sk
{
	BloodEff::BloodEff() :
		_mAnimator(nullptr)
		, _mCollider(nullptr)
		, _mActionNum(1)
	{
	}
	BloodEff::~BloodEff()
	{
	}
	void BloodEff::Initialize()
	{
		_mAnimator = AddComponent<Animator>();

		Texture* blood1 = Resources::Load<Texture>(L"blood1", L"..\\Resources\\image\\effect\\blood1.png");
		Texture* blood2 = Resources::Load<Texture>(L"blood2", L"..\\Resources\\image\\effect\\blood2.png");
		Texture* blood3 = Resources::Load<Texture>(L"blood3", L"..\\Resources\\image\\effect\\blood3.png");

		Transform* tr = GetComponent<Transform>();

		_mAnimator->CreateAnimation(L"blood1_right", blood1, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f)
			, 8, Vector2(100.f, -50.f), 0.07f);
		_mAnimator->CreateAnimation(L"blood1_left", blood1, Vector2(0.0f, 64.0f), Vector2(64.0f, 64.0f)
			, 8, Vector2(-100.f, -50.f), 0.07f);

		_mAnimator->CreateAnimation(L"blood2_right", blood2, Vector2(0.0f, 0.0f), Vector2(128.0f, 128.0f)
			, 6, Vector2(160.f, -110.f), 0.07f);
		_mAnimator->CreateAnimation(L"blood2_left", blood2, Vector2(0.0f, 128.0f), Vector2(128.0f, 128.0f)
			, 6, Vector2(-160.f, -110.f), 0.07f);

		_mAnimator->CreateAnimation(L"blood3_right", blood3, Vector2(0.0f, 0.0f), Vector2(128.0f, 128.0f)
			, 7, Vector2(160.f, -110.f), 0.07f);
		_mAnimator->CreateAnimation(L"blood3_left", blood3, Vector2(0.0f, 128.0f), Vector2(128.0f, 128.0f)
			, 7, Vector2(-160.f, -110.f), 0.07f);


		_mAnimator->SetScale(Vector2(2.0f, 2.0f));

	}
	void BloodEff::Update()
	{
		GameObject::Update();

		if (_mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	void BloodEff::PlayAnimation(eDir dir, bool charge)
	{
		if (charge)
		{
			if (dir == eDir::Right)
			{
				_mAnimator->PlayAnimation(L"blood3_right", false);
			}
			else if (dir == eDir::Left)
			{
				_mAnimator->PlayAnimation(L"blood3_left", false);
			}
		}
		else if (_mActionNum == 1)
		{
			if (dir == eDir::Right)
			{
				_mAnimator->PlayAnimation(L"blood1_right", false);
			}
			else if (dir == eDir::Left)
			{
				_mAnimator->PlayAnimation(L"blood1_left", false);
			}
		}
		else if (_mActionNum == 2)
		{
			if (dir == eDir::Right)
			{
				_mAnimator->PlayAnimation(L"blood2_right", false);
			}
			else if (dir == eDir::Left)
			{
				_mAnimator->PlayAnimation(L"blood2_left", false);
			}
		}
		else if (_mActionNum == 3)
		{
			if (dir == eDir::Right)
			{
				_mAnimator->PlayAnimation(L"blood3_right", false);
			}
			else if (dir == eDir::Left)
			{
				_mAnimator->PlayAnimation(L"blood3_left", false);
			}
		}

	}

	void BloodEff::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BloodEff::OnCollisionEnter(Collider* other)
	{
	}
	void BloodEff::OnCollisionStay(Collider* other)
	{
	}
	void BloodEff::OnCollisionExit(Collider* other)
	{
	}
}