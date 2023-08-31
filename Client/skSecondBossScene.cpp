#include "skSecondBossScene.h"
#include "skObject.h"
#include "skResources.h"
#include "skCamera.h"
#include "skSpriteRenderer.h"
#include "skInput.h"
#include "skBackGround.h"
#include "skFrontBackGround.h"
#include "skFloor.h"
#include "skCollisionMgr.h"
#include "skCutSceneCollider.h"
#include "skWall.h"
#include "skTimeMgr.h"
#include "skPietatPrivateCutScene.h"
#include "skPietat.h"
#include "skSound.h"

namespace sk
{
	bool SecondBossScene::_mbCutSceneOn = false;
	bool SecondBossScene::_mbCanMakeBoss = false;

	SecondBossScene::SecondBossScene()
		: _mPlayer(nullptr)
		, _mBoss(nullptr)
		, _mLImitLeftX(0)
		, _mLimitRightX(1280)
	{
	}
	SecondBossScene::~SecondBossScene()
	{
	}
	void SecondBossScene::Initialize()
	{
		// backgorund
		Texture* BossStage0 = Resources::Load<Texture>(L"SecondBossSceneBack"
			, L"..\\Resources\\image\\SecondBossSceneBack.bmp");

		BackGround* BossStage0_bg = object::Instantiate<BackGround>(eLayerType::Background);
		SpriteRenderer* BossStage0_sr = BossStage0_bg->AddComponent<SpriteRenderer>();
		BossStage0_sr->SetImage(BossStage0);
		BossStage0_sr->SetScale(Vector2(2.f, 2.f));
		BossStage0_bg->GetComponent<Transform>()->SetPosition(Vector2(860.f, 360.f));
		BossStage0_sr->SetCameraRatio(Vector2(1.2f, 1.2f));

		Texture* BossStageMiddle1 = Resources::Load<Texture>(L"SecondBossSceneMiddle"
			, L"..\\Resources\\image\\SecondBossSceneMiddle.bmp");

		BackGround* BossStageMiddle_bg1 = object::Instantiate<BackGround>(eLayerType::Middleground);
		SpriteRenderer* BossStageMiddle_sr1 = BossStageMiddle_bg1->AddComponent<SpriteRenderer>();
		BossStageMiddle_sr1->SetImage(BossStageMiddle1);
		BossStageMiddle_sr1->SetScale(Vector2(2.f, 2.f));
		BossStageMiddle_bg1->GetComponent<Transform>()->SetPosition(Vector2(960.f, 360.f)); //440,515
		//BossStageMiddle_sr1->SetCameraRatio(Vector2(1.5f, 1.5f));

		// 타일 이미지
		Texture* BossStage2 = Resources::Load<Texture>(L"SecondBossSceneMap"
			, L"..\\Resources\\image\\SecondBossSceneMap.bmp");

		BackGround* BossStage2_bg = object::Instantiate<BackGround>(eLayerType::Middleground);
		SpriteRenderer* BossStage2_sr = BossStage2_bg->AddComponent<SpriteRenderer>();
		BossStage2_sr->SetImage(BossStage2);
		BossStage2_sr->SetScale(Vector2(2.f, 2.f));
		BossStage2_bg->GetComponent<Transform>()->SetPosition(Vector2(960.f, 360.f));

		//Front
		Texture* BossStagefront = Resources::Load<Texture>(L"SecondBossSceneFront"
			, L"..\\Resources\\image\\SecondBossSceneFront.bmp");

		FrontBackGround* BossStagefront_bg = object::Instantiate<FrontBackGround>(eLayerType::FrontBackground);
		SpriteRenderer* BossStagefront_sr = BossStagefront_bg->AddComponent<SpriteRenderer>();
		BossStagefront_sr->SetImage(BossStagefront);
		BossStagefront_sr->SetScale(Vector2(2.f, 2.f));
		BossStagefront_bg->GetComponent<Transform>()->SetPosition(Vector2(960.f, 360.f));

		// 카메라 제한거리
		_mLImitLeftX = BossStage2_bg->GetComponent<Transform>()->GetPosition().x - BossStage2->GetWidth();
		_mLimitRightX = BossStage2_bg->GetComponent<Transform>()->GetPosition().x + BossStage2->GetWidth();

		// Player
		Player* player = object::Instantiate<Player>(eLayerType::Player);
		Transform* tr = player->GetComponent<Transform>();
		tr->SetPosition(Vector2(130.0f, 376.0f));
		_mPlayer = player;

		// Floor
		Floor* floor1 = object::Instantiate<Floor>(eLayerType::Floor);
		Collider* colfloor1 = floor1->AddComponent<Collider>();
		colfloor1->SetSize(Vector2(1920.0f, 50.0f));
		Transform* floortr1 = floor1->GetComponent<Transform>();
		floortr1->SetPosition(Vector2(960.0f, 600.0f));

		// Wall
		Wall* wall_left = object::Instantiate<Wall>(eLayerType::Wall);
		Collider* colwallL = wall_left->AddComponent<Collider>();
		colwallL->SetSize(Vector2(50.0f, 600.0f));
		Transform* wltr = wall_left->GetComponent<Transform>();
		wltr->SetPosition(Vector2(_mLImitLeftX, 360.0f));

		Wall* wall_right = object::Instantiate<Wall>(eLayerType::Wall);
		Collider* colwallR = wall_right->AddComponent<Collider>();
		colwallR->SetSize(Vector2(50.0f, 600.0f));
		Transform* wrtr = wall_right->GetComponent<Transform>();
		wrtr->SetPosition(Vector2(_mLimitRightX, 360.0f));
		wall_right->SetRight(false);

		//CutScene Collider
		CutSceneCollider* CutScene = object::Instantiate<CutSceneCollider>(eLayerType::CutScene);
		Collider* CutSceneCol = CutScene->AddComponent<Collider>();
		CutSceneCol->SetNotColColor(RGB(50, 50, 255));
		CutSceneCol->SetSize(Vector2(70.0f, 350.0f));
		Transform* CutSceneTr = CutScene->GetComponent<Transform>();
		CutSceneTr->SetPosition(Vector2(800.0f, 400.0f));

		// CutScene Boss
		PietatPrivateCutScene* CutSceneBoss = object::Instantiate<PietatPrivateCutScene>(eLayerType::SecondBossCutScene);
		Transform* cbosstr = CutSceneBoss->GetComponent<Transform>();
		cbosstr->SetPosition(Vector2(1240.0f, 375.0f));

		Texture* statue_headless = Resources::Load<Texture>(L"statueheadless"
			, L"..\\Resources\\image\\pietat\\pietat_boss_statue_headless.bmp");

		// Sound
		Sound* sound = Resources::Load<Sound>(L"Pietat_Boss_Drone", L"..\\Resources\\sound\\Pietat_Boss_Drone.wav");
		sound->SetVolume(20.0f);
	}

	void SecondBossScene::SceneEnter()
	{
		Camera::SetTarget(_mPlayer);
		Camera::SetPlayMode(true);
		Camera::SetCameraLimit_Left(_mLImitLeftX);
		Camera::SetCameraLimit_Right(_mLimitRightX);
		Resources::Find<Sound>(L"Pietat_Boss_Drone")->Play(true);

	}
	void SecondBossScene::SceneOut()
	{
		//if (_mBoss != nullptr)
		//{
		//	_mBoss->SetDestroy(true);
		//}
		Camera::SetTarget(nullptr);
		Camera::SetPlayMode(false);
		Resources::Find<Sound>(L"Pietat_Boss_Drone")->Stop(true);
	}

	void SecondBossScene::Update()
	{
		Scene::Update();

		if (!(_mbCutSceneOn))
		{
			Camera::SetTarget(_mPlayer);
		}

		if (_mbCanMakeBoss)
		{
			_mbCanMakeBoss = false;

			BackGround* statue = object::Instantiate<BackGround>(eLayerType::Middleground);
			SpriteRenderer* statue_sr = statue->AddComponent<SpriteRenderer>();
			statue_sr->SetImage(Resources::Find<Texture>(L"statueheadless"));
			statue_sr->SetScale(Vector2(2.0f, 2.0f));
			Transform* tr = statue->GetComponent<Transform>();
			tr->SetPosition(Vector2(1227.f,433.f ));

			//Boss
			_mBoss = object::Instantiate<Pietat>(eLayerType::Monster);
			Transform*	bosstr = _mBoss->GetComponent<Transform>();
			bosstr->SetPosition(Vector2(700.f, 350.0f)); // 1370
		}

	}
	void SecondBossScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

}