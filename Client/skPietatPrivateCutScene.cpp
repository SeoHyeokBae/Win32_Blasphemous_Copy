#include "skPietatPrivateCutScene.h"
#include "skTexture.h"
#include "skResources.h"
#include "skAnimator.h"
#include "skTimeMgr.h"
#include "skTransform.h"
#include "skRigidbody.h"
#include "skFirstBossScene.h"
#include "skSound.h"
#include "skSpriteRenderer.h"
#include "skSecondBossScene.h"

namespace sk
{
	bool PietatPrivateCutScene::_mbCanPlay = false;

	PietatPrivateCutScene::PietatPrivateCutScene() :
		_mAnimator(nullptr)
		, _mRigidbody(nullptr)
		, _mTime(0.f)
		, _mCount(0)
	{
	}
	PietatPrivateCutScene::~PietatPrivateCutScene()
	{
	}
	void PietatPrivateCutScene::Initialize()
	{
		_mAnimator = AddComponent<Animator>();

		Texture* Cutscene_pietat0 = Resources::Load<Texture>(L"Cutscene_pietat0", L"..\\Resources\\image\\pietat\\pietat_boss_cutscene0.bmp");
		Texture* Cutscene_pietat1 = Resources::Load<Texture>(L"Cutscene_pietat1", L"..\\Resources\\image\\pietat\\pietat_boss_cutscene1.bmp");
		Texture* Cutscene_pietat2 = Resources::Load<Texture>(L"Cutscene_pietat2", L"..\\Resources\\image\\pietat\\pietat_boss_cutscene2.bmp");
		Texture* Cutscene_pietat3 = Resources::Load<Texture>(L"Cutscene_pietat3", L"..\\Resources\\image\\pietat\\pietat_boss_cutscene3.bmp");

		_mAnimator->CreateAnimation(L"Cut_pietat0", Cutscene_pietat0, Vector2(0.0f, 0.0f), Vector2(260.f, 286.0f), 1, Vector2(0.0f, -35.0f), 0.1f);
		_mAnimator->CreateAnimation(L"Cut_pietat1", Cutscene_pietat1, Vector2(0.0f, 0.0f), Vector2(260.f, 286.0f), 48, Vector2(30.0f, -35.0f), 0.14f);
		_mAnimator->CreateAnimation(L"Cut_pietat2", Cutscene_pietat2, Vector2(0.0f, 0.0f), Vector2(475.f, 290.f), 28, Vector2(69.0f, -43.0f), 0.12f);
		_mAnimator->CreateAnimation(L"Cut_pietat3", Cutscene_pietat3, Vector2(0.0f, 0.0f), Vector2(450.f, 270.0f), 11, Vector2(-66.0f, -21.0f), 0.14f);
		_mAnimator->SetScale(Vector2(2.0f, 2.0f));

		_mAnimator->PlayAnimation(L"Cut_pietat0", false);
		//Resources::Load<Sound>(L"Elder_Attack", L"..\\Resources\\sound\\ELDER_BROTHER_ATTACK.wav");
	}

	void PietatPrivateCutScene::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (_mbCanPlay)
		{
			_mTime += TimeMgr::DeltaTime();
			if (_mTime > 1.5f && _mAnimator->IsActiveAnimationComplete())
			{
				if (_mCount == 0)
				{
					_mCount++;
					_mAnimator->PlayAnimation(L"Cut_pietat1", false);
				}
				else if (_mCount ==1)
				{
					_mCount++;
					_mAnimator->PlayAnimation(L"Cut_pietat2", false);
				}
				else if (_mCount == 2)
				{
					_mCount++;
					_mAnimator->PlayAnimation(L"Cut_pietat3", false);
				}
				
			}
		}

		if (_mAnimator->IsActiveAnimationComplete())
		{
			if (_mAnimator->GetActiveAnime() == _mAnimator->FindAnimation(L"Cut_pietat3"))
			{
				//TODO
				Camera::SetCutSceneMode(false);
				SecondBossScene::_mbCutSceneOn = false;
				SecondBossScene::_mbCanMakeBoss = true;
				Destroy(this);
			}
		}
	}
	void PietatPrivateCutScene::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}