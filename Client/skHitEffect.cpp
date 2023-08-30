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
	{
	}
	HitEffect::~HitEffect()
	{
	}
	void HitEffect::Initialize()
	{
		_mAnimator = AddComponent<Animator>();

		Texture* attackspark1 = Resources::Load<Texture>(L"attackspark"
			, L"..\\Resources\\image\\attackspark1.png");

		Texture* chargespark = Resources::Load<Texture>(L"chargespark"
			, L"..\\Resources\\image\\charge_hit_eff.png");

		Transform* tr = GetComponent<Transform>();

		_mAnimator->CreateAnimation(L"attackspark1_right", attackspark1, Vector2(0.0f, 0.0f), Vector2(150.f, 90.0f)
			, 6, Vector2(tr->GetPosition().x, tr->GetPosition().y -45.f), 0.065f);
		_mAnimator->CreateAnimation(L"attackspark1_left", attackspark1, Vector2(0.0f, 90.0f), Vector2(150.f, 90.0f)
			, 6, Vector2(tr->GetPosition().x, tr->GetPosition().y -45.f), 0.065f);

		_mAnimator->CreateAnimation(L"chargespark_right", chargespark, Vector2(0.0f, 0.0f), Vector2(120.0f, 120.0f)
			, 9, Vector2(tr->GetPosition().x-50.f, tr->GetPosition().y - 45.f), 0.08f);
		_mAnimator->CreateAnimation(L"chargespark_left", chargespark, Vector2(0.0f, 120.0f), Vector2(120.0f, 120.0f)
			, 9, Vector2(tr->GetPosition().x+50.f, tr->GetPosition().y - 45.f), 0.08f);

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
		else
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