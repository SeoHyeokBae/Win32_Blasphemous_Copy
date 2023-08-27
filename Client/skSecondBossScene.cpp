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

namespace sk
{
	bool SecondBossScene::_mbCutSceneOn = false;
	bool SecondBossScene::_mbCanMakeBoss = false;

	SecondBossScene::SecondBossScene()
		: _mPlayer(nullptr)
		//, _mBoss(nullptr)
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
		BossStage0_bg->GetComponent<Transform>()->SetPosition(Vector2(960.f, 360.f));

		Texture* BossStageMiddle1 = Resources::Load<Texture>(L"SecondBossSceneMiddle"
			, L"..\\Resources\\image\\SecondBossSceneMiddle.bmp");

		BackGround* BossStageMiddle_bg1 = object::Instantiate<BackGround>(eLayerType::Middleground);
		SpriteRenderer* BossStageMiddle_sr1 = BossStageMiddle_bg1->AddComponent<SpriteRenderer>();
		BossStageMiddle_sr1->SetImage(BossStageMiddle1);
		BossStageMiddle_sr1->SetScale(Vector2(2.f, 2.f));
		BossStageMiddle_bg1->GetComponent<Transform>()->SetPosition(Vector2(960.f, 360.f)); //440,515

		//BossStageMiddle_sr1->SetAffectCamera(false);
		//BossStageMiddle_sr1->SetCameraRatio(Vector2(0.9f, 0.9f));

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

		//// Player
		//Player* player = object::Instantiate<Player>(eLayerType::Player);
		//Transform* tr = player->GetComponent<Transform>();
		//tr->SetPosition(Vector2(130.0f, 376.0f));
		////player->GetComponent<Animator>()->SetAffectedCamera(true);
		//_mPlayer = player;



		// Floor

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
		//CutSceneCollider* CutScene = object::Instantiate<CutSceneCollider>(eLayerType::CutScene);
		//Collider* CutSceneCol = CutScene->AddComponent<Collider>();
		//CutSceneCol->SetNotColColor(RGB(50, 50, 255));
		//CutSceneCol->SetSize(Vector2(70.0f, 350.0f));
		//Transform* CutSceneTr = CutScene->GetComponent<Transform>();
		//CutSceneTr->SetPosition(Vector2(1175.0f, 370.0f));

		// CutScene Boss
		//ElderBroPrivateCutScene* CutSceneBoss = object::Instantiate<ElderBroPrivateCutScene>(eLayerType::FirstBossCutScene);
		//Transform* cbosstr = CutSceneBoss->GetComponent<Transform>();
		//cbosstr->SetPosition(Vector2(1700.0f, 500.0f));

		//CutScene->_mElderBroCutScene = CutSceneBoss;
		//CollisionMgr::CollisionLayerCheck(eLayerType::Player, eLayerType::CutScene, true);
	}

	void SecondBossScene::SceneEnter()
	{
		//Camera::SetTarget(_mPlayer);
		//Camera::SetPlayMode(true);
		//Camera::SetCameraLimit_Left(_mLImitLeftX);
		//Camera::SetCameraLimit_Right(_mLimitRightX);

	}
	void SecondBossScene::SceneOut()
	{
		//if (_mBoss != nullptr)
		//{
		//	_mBoss->SetDestroy(true);
		//}
		Camera::SetTarget(nullptr);
		Camera::SetPlayMode(false);
	}

	void SecondBossScene::Update()
	{
		Scene::Update();

		//if (!(_mbCutSceneOn))
		//{
		//	Camera::SetTarget(_mPlayer);
		//}

		//if (_mbCanMakeBoss)
		//{
		//	_mbCanMakeBoss = false;

		//	//Boss
		//	ElderBrother* boss = object::Instantiate<ElderBrother>(eLayerType::Monster);
		//	Transform* bosstr = boss->GetComponent<Transform>();
		//	boss->_mFloorTexture = Resources::Find<Texture>(L"bossfloor");
		//	bosstr->SetPosition(Vector2(Player::GetPlayerPos().x, -500.0f));
		//	_mBoss = boss;
		//}
	}
	void SecondBossScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

}