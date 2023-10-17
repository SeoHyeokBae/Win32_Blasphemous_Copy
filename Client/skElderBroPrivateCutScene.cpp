#include "skElderBroPrivateCutScene.h"
#include "skTexture.h"
#include "skResources.h"
#include "skAnimator.h"
#include "skTimeMgr.h"
#include "skTransform.h"
#include "skRigidbody.h"
#include "skFirstBossScene.h"
#include "skSound.h"

namespace sk
{
	bool ElderBroPrivateCutScene::_mbCanPlay = false;

	ElderBroPrivateCutScene::ElderBroPrivateCutScene() :
		_mAnimator(nullptr)
		,_mRigidbody(nullptr)
		,_mTime(0.f)
		,_mCount(0)
		,_mbJump(false)
		,_mbSound(true)
		,_mbSound2(true)
	{
	}
	ElderBroPrivateCutScene::~ElderBroPrivateCutScene()
	{
	}
	void ElderBroPrivateCutScene::Initialize()
	{
		_mAnimator = AddComponent<Animator>();
		_mRigidbody = AddComponent<Rigidbody>();
		
		Texture* CutScene_Attack = Resources::Load<Texture>(L"Cutscene_Attack", L"..\\Resources\\image\\monster\\elderbrother\\eldershade.bmp");
		Texture* CutScene_Idle = Resources::Load<Texture>(L"Cutscene_Idle", L"..\\Resources\\image\\monster\\elderbrother\\eldershade2.bmp");
		Texture* CutScene_Jump = Resources::Load<Texture>(L"Cutscene_Jump", L"..\\Resources\\image\\monster\\elderbrother\\eldershade3.bmp");

		_mAnimator->CreateAnimation(L"Cutscene_Attack", CutScene_Attack, Vector2(0.0f, 0.0f), Vector2(350.f, 250.0f), 24, Vector2(-150.0f, -100.0f), 0.07f);
		_mAnimator->CreateAnimation(L"Cutscene_Idle", CutScene_Idle, Vector2(0.0f, 0.0f), Vector2(170.f, 170.f), 10, Vector2(-92.0f, -45.0f), 0.2f);
		_mAnimator->CreateAnimation(L"Cutscene_Jump", CutScene_Jump, Vector2(0.0f, 0.0f), Vector2(225.f, 210.0f), 11, Vector2(-85.0f, -70.0f), 0.1f);
		_mAnimator->SetScale(Vector2(1.7f, 1.7f));

		Resources::Load<Sound>(L"Elder_Attack", L"..\\Resources\\sound\\ELDER_BROTHER_ATTACK.wav");
		Resources::Load<Sound>(L"ELDER_BROTHER_ATTACK_HIT", L"..\\Resources\\sound\\ELDER_BROTHER_ATTACK_HIT.wav");
		Resources::Load<Sound>(L"ELDER_BROTHER_JUMP_VOICE", L"..\\Resources\\sound\\ELDER_BROTHER_JUMP_VOICE.wav");


		_mAnimator->PlayAnimation(L"Cutscene_Idle", true);

		_mRigidbody->SetGround(true);
	}

	void ElderBroPrivateCutScene::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		GameObject::Update();

		if (_mbCanPlay)
		{
			_mTime += TimeMgr::DeltaTime();
			if (_mTime > 1.5f)
			{
				if (_mAnimator->GetActiveAnime() == _mAnimator->FindAnimation(L"Cutscene_Idle") && _mCount == 0)
				{
					_mAnimator->PlayAnimation(L"Cutscene_Attack", false);
				}
				else if (_mAnimator->GetActiveAnime() == _mAnimator->FindAnimation(L"Cutscene_Idle") && _mCount == 2) // 두번찍기->대기->점프
				{
					Resources::Find<Sound>(L"ELDER_BROTHER_JUMP_VOICE")->Play(false);
					Resources::Find<Sound>(L"ELDER_BROTHER_JUMP_VOICE")->SetVolume(30.f);
					_mAnimator->PlayAnimation(L"Cutscene_Jump", false);

					_mbJump = true;
				}


				if (_mbSound &&_mAnimator->GetActiveAnime()->GetIndex() == 18)
				{
					_mbSound = false;
						Resources::Find<Sound>(L"Elder_Attack")->Play(false);
						Resources::Find<Sound>(L"Elder_Attack")->SetVolume(15.0f);
				}

				if (_mbSound2 && (_mAnimator->GetActiveAnime()->GetIndex() == 21))
				{
					_mbSound2 = false;
						Resources::Find<Sound>(L"ELDER_BROTHER_ATTACK_HIT")->Play(false);
						Resources::Find<Sound>(L"ELDER_BROTHER_ATTACK_HIT")->SetVolume(15.0f);

				}

				if (_mAnimator->IsActiveAnimationComplete() && _mCount < 2)
				{
					_mbSound = true;
					_mbSound2 = true;
					_mCount++;
					if (_mCount == 2 )
					{
						_mTime = 0.f;
						_mAnimator->PlayAnimation(L"Cutscene_Idle", false);
					}
					else
					{
						_mAnimator->PlayAnimation(L"Cutscene_Attack", false);
					}
				}
			}

			if (_mbJump)
			{
				if (_mAnimator->GetActiveAnime()->GetIndex() >= 9)
				{
					_mRigidbody->SetGround(false);

					Vector2 velocity = _mRigidbody->GetVelocity();
					velocity.y = -1500.0f;
					velocity.x = -250.0f;
					_mRigidbody->SetVelocity(velocity);
				}
			}
			
		}

		// 화면 위로 나가면 제거
		if (pos.y <0.0f /*- size*/)
		{
			Camera::SetCutSceneMode(false);
			FirstBossScene::_mbCutSceneOn = false;
			FirstBossScene::_mbCanMakeBoss = true;
			Destroy(this);
		}
	}
	void ElderBroPrivateCutScene::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}