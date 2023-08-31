#include "skFirstBossScene.h"
#include "skObject.h"
#include "skResources.h"
#include "skCamera.h"
#include "skSpriteRenderer.h"
#include "skInput.h"
#include "skBackGround.h"
#include "skFrontBackGround.h"
#include "skFloor.h"
#include "skElderBrother.h"
#include "skCollisionMgr.h"
#include "skCutSceneCollider.h"
#include "skWall.h"
#include "skElderBroPrivateCutScene.h"
#include "skTimeMgr.h"

namespace sk
{
	bool FirstBossScene::_mbCutSceneOn = false;
	bool FirstBossScene::_mbCanMakeBoss = false;

	FirstBossScene::FirstBossScene()
		: _mPlayer(nullptr)
		, _mBoss(nullptr)
		, _mLImitLeftX(0)
		, _mLimitRightX(1280)
	{
	}
	FirstBossScene::~FirstBossScene()
	{
	}
	void FirstBossScene::Initialize()
	{
		// backgorund
		//Texture* BossStage0 = Resources::Load<Texture>(L"bossStagebg0"
		//	, L"..\\Resources\\image\\bossstagebackground1.bmp");

		//BackGround* BossStage0_bg = object::Instantiate<BackGround>(eLayerType::Background);
		//SpriteRenderer* BossStage0_sr = BossStage0_bg->AddComponent<SpriteRenderer>();
		//BossStage0_sr->SetImage(BossStage0);
		//BossStage0_sr->SetScale(Vector2(2.f, 2.f));
		//BossStage0_bg->GetComponent<Transform>()->SetPosition(Vector2(0.f, 360.f));
		//BossStage0_sr->SetOffset(Vector2(250.f, 0.f));

		////middle ground
		//Texture* BossStageMiddle = Resources::Load<Texture>(L"bossStageMiddle"
		//	, L"..\\Resources\\image\\middleground.bmp");

		//BackGround* BossStageMiddle_bg = object::Instantiate<BackGround>(eLayerType::Background);
		//SpriteRenderer* BossStageMiddle_sr = BossStageMiddle_bg->AddComponent<SpriteRenderer>();
		//BossStageMiddle_sr->SetImage(BossStageMiddle);
		//BossStageMiddle_sr->SetScale(Vector2(2.f, 2.f));
		//BossStageMiddle_bg->GetComponent<Transform>()->SetPosition(Vector2(1232.f, 360.f));
		//BossStageMiddle_sr->SetOffset(Vector2(250.f, 0.f));

		Texture* BossStageMiddle1 = Resources::Load<Texture>(L"bossStageMiddle1"
			, L"..\\Resources\\image\\bossstagemiddleground2.1.bmp");

		BackGround* BossStageMiddle_bg1 = object::Instantiate<BackGround>(eLayerType::Middleground);
		SpriteRenderer* BossStageMiddle_sr1 = BossStageMiddle_bg1->AddComponent<SpriteRenderer>();
		BossStageMiddle_sr1->SetImage(BossStageMiddle1);
		BossStageMiddle_sr1->SetScale(Vector2(2.f, 2.f));
		BossStageMiddle_bg1->GetComponent<Transform>()->SetPosition(Vector2(740.f, 480.f)); //440,515
		BossStageMiddle_sr1->SetOffset(Vector2(500.f, 0.f));

		//BossStageMiddle_sr1->SetAffectCamera(false);
		BossStageMiddle_sr1->SetCameraRatio(Vector2(0.9f, 0.9f));

		// 타일 이미지
		//Texture* BossStage1 = Resources::Load<Texture>(L"bossStagebg1"
		//	, L"..\\Resources\\image\\BossStage1.bmp");
		Texture* BossStage1 = Resources::Load<Texture>(L"bossStagebg1"
			, L"..\\Resources\\image\\BossStage1.1.bmp");

		BackGround* BossStage1_bg = object::Instantiate<BackGround>(eLayerType::Middleground);
		SpriteRenderer* BossStage1_sr = BossStage1_bg->AddComponent<SpriteRenderer>();
		BossStage1_sr->SetImage(BossStage1);
		BossStage1_sr->SetScale(Vector2(2.f, 2.f));
		BossStage1_bg->GetComponent<Transform>()->SetPosition(Vector2(1275.f, 360.f));

		// 카메라 제한거리
		_mLImitLeftX = BossStage1_bg->GetComponent<Transform>()->GetPosition().x - BossStage1->GetWidth();
		_mLimitRightX = BossStage1_bg->GetComponent<Transform>()->GetPosition().x + BossStage1->GetWidth();

		// 앞 이미지
		Texture* frontBackground = Resources::Load<Texture>(L"bossStagefrontbg1"
			, L"..\\Resources\\image\\BossStagef1.1.bmp");

		FrontBackGround* fbg = object::Instantiate<FrontBackGround>(eLayerType::FrontBackground);
		SpriteRenderer* fbgsr = fbg->AddComponent<SpriteRenderer>();
		fbgsr->SetImage(frontBackground);
		fbgsr->SetScale(Vector2(2.f, 2.f));
		fbg->GetComponent<Transform>()->SetPosition(Vector2(1275, 360.f));

		// Player
		Player* player = object::Instantiate<Player>(eLayerType::Player);
		Transform* tr = player->GetComponent<Transform>();
		tr->SetPosition(Vector2(130.0f, 376.0f));
		//player->GetComponent<Animator>()->SetAffectedCamera(true);
		_mPlayer = player;



		// Floor ( Pixel )
		Texture* floorb2 = Resources::Load<Texture>(L"bossfloor"
			, L"..\\Resources\\Image\\BossStage1floor.bmp");
		_mPlayer->_mFloorTexture = floorb2;


		Floor* floor2 = object::Instantiate<Floor>(eLayerType::Floor);
		SpriteRenderer* floorsr2 = floor2->AddComponent<SpriteRenderer>();
		floorsr2->SetImage(floorb2);
		floorsr2->SetAlpha(0.0f);
		tr = floor2->GetComponent<Transform>();
		tr->SetPosition(Vector2(1275, 360.0f));

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

		// CutScene Collider
		CutSceneCollider* CutScene = object::Instantiate<CutSceneCollider>(eLayerType::CutScene);
		Collider* CutSceneCol = CutScene->AddComponent<Collider>();
		CutSceneCol->SetNotColColor(RGB(50, 50, 255));
		CutSceneCol->SetSize(Vector2(70.0f, 350.0f));
		Transform* CutSceneTr = CutScene->GetComponent<Transform>();
		CutSceneTr->SetPosition(Vector2(1175.0f, 370.0f));

		// CutScene Boss
		ElderBroPrivateCutScene* CutSceneBoss = object::Instantiate<ElderBroPrivateCutScene>(eLayerType::FirstBossCutScene);
		Transform* cbosstr = CutSceneBoss->GetComponent<Transform>();
		cbosstr->SetPosition(Vector2(1700.0f,500.0f));

		CollisionMgr::CollisionLayerCheck(eLayerType::Player, eLayerType::CutScene, true);
	}

	void FirstBossScene::SceneEnter()
	{
		Camera::SetTarget(_mPlayer);
		Camera::SetPlayMode(true);
		Camera::SetCameraLimit_Left(_mLImitLeftX);
		Camera::SetCameraLimit_Right(_mLimitRightX);

	}
	void FirstBossScene::SceneOut()
	{
		if (_mBoss != nullptr)
		{
			_mBoss->SetDestroy(true);
		}
		Camera::SetTarget(nullptr);
		Camera::SetPlayMode(false);
	}

	void FirstBossScene::Update()
	{
		Scene::Update();

		if (!(_mbCutSceneOn))
		{
			Camera::SetTarget(_mPlayer);
		}

		if (_mbCanMakeBoss)
		{
			_mbCanMakeBoss = false;

			//Boss
			ElderBrother* boss = object::Instantiate<ElderBrother>(eLayerType::Monster);
			Transform* bosstr = boss->GetComponent<Transform>();
			boss->_mFloorTexture = Resources::Find<Texture>(L"bossfloor");
			bosstr->SetPosition(Vector2(Player::GetPlayerPos().x, -500.0f));
			_mBoss = boss;
		}

		if (Input::GetKeyUp(eKeyCode::N))
		{
			SceneMgr::LoadScene(L"FirstBossScene");
		}

		if (Input::GetKeyUp(eKeyCode::M))
		{
			SceneMgr::LoadScene(L"Scene04");
		}

	}
	void FirstBossScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

}