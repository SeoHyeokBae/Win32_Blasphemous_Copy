#include "skElderWave.h"
#include "skTexture.h"
#include "skResources.h"
#include "skAnimator.h"
#include "skTransform.h"
#include "skElderBrother.h"
#include"skRigidbody.h"
#include "skCollider.h"
#include "skElderCorpseEff.h"
#include "skObject.h"
#include "skTransform.h"
#include "skElderWaveMgr.h"
#include "skPlayer.h"
#include "skPlayerHit.h"
#include "skCamera.h"
#include "skTimeMgr.h"

namespace sk
{
	ElderWave::ElderWave() :
		_mAnimator(nullptr)
		, _mRigidbody(nullptr)
		, _mCollider(nullptr)
	{
	}
	ElderWave::~ElderWave()
	{
	}
	void ElderWave::Initialize()
	{
		_mAnimator = AddComponent<Animator>();
		_mRigidbody = AddComponent<Rigidbody>();
		_mCollider = AddComponent<Collider>();

		Texture* Wave = Resources::Load<Texture>(L"Elder_Wave", L"..\\Resources\\image\\monster\\elderbrother\\burntFace_rayBeam_impact.bmp");

		_mAnimator->CreateAnimation(L"Elder_Wave", Wave, Vector2(0.0f, 0.0f), Vector2(128.f, 128.f)
			, 20, Vector2(0.0f, -100.0f), 0.04f);

		_mAnimator->SetScale(Vector2(2.0f, 2.0f));

		_mCollider->SetSize(Vector2(50.f, 40.f));
		_mRigidbody->SetGravity(Vector2(0.f, 2000.0f));

		PlayAnimation();
	}
	void ElderWave::Update()
	{
		GameObject::Update();

		PixelCollision();

		if (_mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	void ElderWave::PlayAnimation()
	{
		_mAnimator->PlayAnimation(L"Elder_Wave");
	}

	//pixel Ãæµ¹
	void ElderWave::PixelCollision()
	{
		Transform* tr = GetComponent<Transform>();
		if (_mFloorTexture != nullptr)
		{
			Vector2 ColPos = _mCollider->GetPosition();
			Vector2 ColSize = _mCollider->GetSize();
			Vector2 Bottom = Vector2(ColPos.x, ColPos.y + (ColSize.y / 2.0f));

			COLORREF BottomColor = _mFloorTexture->GetTexturePixel((int)Bottom.x, (int)Bottom.y);
			Rigidbody* rb = GetComponent<Rigidbody>();

			if (BottomColor == RGB(255, 0, 255))
			{
				Vector2 pos = tr->GetPosition();
				tr->SetPosition(pos);

				_mRigidbody->SetGround(true);
			}

			if (!(BottomColor == RGB(255, 0, 255)))
			{
				_mRigidbody->SetGround(false);
			}
		}
	}

	void ElderWave::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void ElderWave::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Rigidbody* Player_RB = player->GetComponent<Rigidbody>();
		Vector2 velocity = Player_RB->GetVelocity();

		Transform* tr = nullptr;
		player->GetComponent<Rigidbody>()->SetGround(false);

		if (player != nullptr)
		{
			tr = player->GetComponent<Transform>();

			if (player->GetState() != Player::eState::DODGE && player->GetState() != Player::eState::HIT)
			{
				PlayerHit* phiteffect = object::Instantiate<PlayerHit>(eLayerType::Effect, tr->GetPosition());

				if (player->GetDir() == eDir::Right)
				{
					velocity.x = -350.0f;
					velocity.y = -350.0f;
					Player_RB->SetVelocity(velocity);
					phiteffect->PlayAnimation(eDir::Right);
					player->GetComponent<Animator>()->PlayAnimation(L"PlayerHit_right", false);
					player->SetState(Player::eState::HIT);
				}
				else if (player->GetDir() == eDir::Left)
				{
					velocity.x = 350.0f;
					velocity.y = -350.0f;
					Player_RB->SetVelocity(velocity);
					phiteffect->PlayAnimation(eDir::Left);
					player->GetComponent<Animator>()->PlayAnimation(L"PlayerHit_left", false);
					player->SetState(Player::eState::HIT);
				}
				Camera::Shake(0.2f, 0.6f);
				TimeMgr::Delay();
			}

		}
	}
	void ElderWave::OnCollisionStay(Collider* other)
	{
	}
	void ElderWave::OnCollisionExit(Collider* other)
	{
	}
}