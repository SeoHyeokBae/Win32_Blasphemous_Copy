#include "skHitEffect.h"
#include "skPlayer.h"
#include "skTexture.h"
#include "skResources.h"
#include "skAnimator.h"
#include "skObject.h"
#include "skTransform.h"

namespace sk
{
	HitEffect::HitEffect() :
		_mAnimator(nullptr)
		, _mCollider(nullptr)
		, _mActionNum(1)
	{
	}
	HitEffect::~HitEffect()
	{
	}
	void HitEffect::Initialize()
	{
		_mAnimator = AddComponent<Animator>();

		Texture* attackspark1 = Resources::Load<Texture>(L"attackspark", L"..\\Resources\\image\\effect\\attackspark1.png");
		Texture* attackspark2 = Resources::Load<Texture>(L"attackspark2", L"..\\Resources\\image\\effect\\attackspark2.png");
		Texture* attackspark3 = Resources::Load<Texture>(L"attackspark3", L"..\\Resources\\image\\effect\\attackspark3.png");

		Texture* chargespark = Resources::Load<Texture>(L"chargespark", L"..\\Resources\\image\\effect\\charge_hit_eff.png");

		Transform* tr = GetComponent<Transform>();

		_mAnimator->CreateAnimation(L"attackspark1_right", attackspark1, Vector2(0.0f, 0.0f), Vector2(150.f, 90.0f)
			, 6, Vector2(90.f, -45.f), 0.065f);
		_mAnimator->CreateAnimation(L"attackspark1_left", attackspark1, Vector2(0.0f, 90.0f), Vector2(150.f, 90.0f)
			, 6, Vector2(-90.f, -45.f), 0.065f);

		_mAnimator->CreateAnimation(L"attackspark2_right", attackspark2, Vector2(0.0f, 0.0f), Vector2(130.f, 90.0f)
			, 6, Vector2(90.f,  -10.f), 0.065f);
		_mAnimator->CreateAnimation(L"attackspark2_left", attackspark2, Vector2(0.0f, 90.0f), Vector2(130.f, 90.0f)
			, 6, Vector2(-90.f,  -10.f), 0.065f);

		_mAnimator->CreateAnimation(L"attackspark3_right", attackspark3, Vector2(0.0f, 0.0f), Vector2(140.f, 110.0f)
			, 5, Vector2(90.f, -10.f), 0.065f);
		_mAnimator->CreateAnimation(L"attackspark3_left", attackspark3, Vector2(0.0f, 110.0f), Vector2(140.f, 110.0f)
			, 5, Vector2(-90.f, -10.f), 0.065f);

		_mAnimator->CreateAnimation(L"chargespark_right", chargespark, Vector2(0.0f, 0.0f), Vector2(120.0f, 120.0f)
			, 9, Vector2(90.f,  -20.f), 0.08f);
		_mAnimator->CreateAnimation(L"chargespark_left", chargespark, Vector2(0.0f, 120.0f), Vector2(120.0f, 120.0f)
			, 9, Vector2(-90.f, - 20.f), 0.08f);

		_mAnimator->SetScale(Vector2(2.0f, 2.0f));

	}
	void HitEffect::Update()
	{
		GameObject::Update();

		if (_mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	void HitEffect::PlayAnimation(eDir dir , bool charge )
	{
		if (charge)
		{
			if (dir == eDir::Right)
			{
				_mAnimator->PlayAnimation(L"chargespark_right", false);
			}
			else if (dir == eDir::Left)
			{
				_mAnimator->PlayAnimation(L"chargespark_left", false);
			}
		}
		else if(_mActionNum ==1)
		{
			if (dir == eDir::Right)
			{
				_mAnimator->PlayAnimation(L"attackspark1_right", false);
			}
			else if (dir == eDir::Left)
			{
				_mAnimator->PlayAnimation(L"attackspark1_left", false);
			}
		}
		else if (_mActionNum == 2)
		{
			if (dir == eDir::Right)
			{
				_mAnimator->PlayAnimation(L"attackspark2_right", false);
			}
			else if (dir == eDir::Left)
			{
				_mAnimator->PlayAnimation(L"attackspark2_left", false);
			}
		}
		else if (_mActionNum == 3)
		{
			if (dir == eDir::Right)
			{
				_mAnimator->PlayAnimation(L"attackspark3_right", false);
			}
			else if (dir == eDir::Left)
			{
				_mAnimator->PlayAnimation(L"attackspark3_left", false);
			}
		}

	}

	void HitEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void HitEffect::OnCollisionEnter(Collider* other)
	{

	}
	void HitEffect::OnCollisionStay(Collider* other)
	{
	}
	void HitEffect::OnCollisionExit(Collider* other)
	{
	}
}