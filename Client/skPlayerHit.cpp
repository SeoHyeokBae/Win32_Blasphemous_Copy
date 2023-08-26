#include "skPlayerHit.h"
#include "skPlayer.h"
#include "skTexture.h"
#include "skResources.h"
#include "skAnimator.h"
#include "skObject.h"
#include "skTransform.h"

namespace sk
{
	PlayerHit::PlayerHit() :
		_mAnimator(nullptr)
	{
	}
	PlayerHit::~PlayerHit()
	{
	}
	void PlayerHit::Initialize()
	{
		_mAnimator = AddComponent<Animator>();

		Texture* hitspark = Resources::Load<Texture>(L"playerhitspark"
			, L"..\\Resources\\image\\playerhitspark.png");

		Transform* tr = GetComponent<Transform>();

		_mAnimator->CreateAnimation(L"hitspark_right", hitspark, Vector2(0.0f, 0.0f), Vector2(90.f, 90.0f)
			, 6, Vector2(0.f,175.f), 0.03f);
		_mAnimator->CreateAnimation(L"hitspark_left", hitspark, Vector2(0.0f, 90.0f), Vector2(90.f, 90.0f)
			, 6, Vector2(0.f, 175.f), 0.03f);

		_mAnimator->SetScale(Vector2(1.5f, 1.5f));

	}
	void PlayerHit::Update()
	{
		GameObject::Update();

		if (_mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	void PlayerHit::PlayAnimation(eDir dir)
	{
		if (dir == eDir::Right)
		{
			_mAnimator->PlayAnimation(L"hitspark_right", false);
		}
		else if (dir == eDir::Left)
		{
			_mAnimator->PlayAnimation(L"hitspark_left", false);
		}
	}

	void PlayerHit::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void PlayerHit::OnCollisionEnter(Collider* other)
	{
	}
	void PlayerHit::OnCollisionStay(Collider* other)
	{
	}
	void PlayerHit::OnCollisionExit(Collider* other)
	{
	}

}