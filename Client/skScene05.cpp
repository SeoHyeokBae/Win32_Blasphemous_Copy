#include "skScene05.h"
#include "skSpriteRenderer.h"
#include "skObject.h"
#include "skInput.h"
#include "skTexture.h"
#include "skTransform.h"
#include "skResources.h"
#include "skBackGround.h"
#include "skFrontBackGround.h"
#include "skFloor.h"
#include "skCollider.h"
#include "skCollisionMgr.h"
#include "skWall.h"
#include "skPortal.h"
#include "skSound.h"
#include "skCamera.h"
#include "skStoner.h"
#include "skPortal.h"


namespace sk
{
	Scene05::Scene05()
		: _mPlayer(nullptr)
		, _mLImitLeftX(0)
		, _mLimitRightX(1280)
		, _mStoner1(true)
		, _mStoner2(true)
	{
	}
	Scene05::~Scene05()
	{
	}
	void Scene05::Initialize()
	{
		//Texture* tutorialbackground = Resources::Load<Texture>(L"tutorialbackground"
		//	, L"..\\Resources\\image\\tutorialbackground.bmp");

		//BackGround* back_bg = object::Instantiate<BackGround>(eLayerType::Background);
		//SpriteRenderer* back_sr = back_bg->AddComponent<SpriteRenderer>();
		//back_sr->SetImage(tutorialbackground);
		//back_sr->SetScale(Vector2(2.f, 2.f));
		//back_bg->GetComponent<Transform>()->SetPosition(Vector2(1030.f, 360.f));
		//back_sr->SetCameraRatio(Vector2(2.5f, 2.5f));



		//Texture* tutorialMiddle2 = Resources::Load<Texture>(L"tutorialMiddle2"
		//	, L"..\\Resources\\image\\middle2.bmp");

		//BackGround* StageMiddle_bg1 = object::Instantiate<BackGround>(eLayerType::Background);
		//SpriteRenderer* StageMiddle_sr1 = StageMiddle_bg1->AddComponent<SpriteRenderer>();
		//StageMiddle_sr1->SetImage(tutorialMiddle2);
		//StageMiddle_sr1->SetScale(Vector2(2.f, 2.f));
		//StageMiddle_bg1->GetComponent<Transform>()->SetPosition(Vector2(1600.f, 360.f));
		//StageMiddle_sr1->SetCameraRatio(Vector2(1.1f, 1.1f));

		//Texture* tutorialMiddle1 = Resources::Load<Texture>(L"tutorialMiddle1"
		//	, L"..\\Resources\\image\\middle1.bmp");

		//BackGround* StageMiddle_bg = object::Instantiate<BackGround>(eLayerType::Background);
		//SpriteRenderer* StageMiddle_sr = StageMiddle_bg->AddComponent<SpriteRenderer>();
		//StageMiddle_sr->SetImage(tutorialMiddle1);
		//StageMiddle_sr->SetScale(Vector2(2.f, 2.f));
		//StageMiddle_bg->GetComponent<Transform>()->SetPosition(Vector2(1650.f, 360.f));
		//StageMiddle_sr->SetCameraRatio(Vector2(1.2f, 1.2f));

		// 타일 이미지
		Texture* Scene05MAp = Resources::Load<Texture>(L"Scene05map"
			, L"..\\Resources\\image\\scene05map.bmp");

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(Scene05MAp);
		bgsr->SetScale(Vector2(2.f, 2.f));
		bg->GetComponent<Transform>()->SetPosition(Vector2(1413.f, 360.f));
		//bgsr->SetAffectCamera(true);

		// 카메라 제한거리
		_mLImitLeftX = bg->GetComponent<Transform>()->GetPosition().x - Scene05MAp->GetWidth();
		_mLimitRightX = bg->GetComponent<Transform>()->GetPosition().x + Scene05MAp->GetWidth();

		// 앞 이미지
		Texture* Scene05Front = Resources::Load<Texture>(L"Scene05front"
			, L"..\\Resources\\image\\Scene05front.bmp");

		FrontBackGround* fbg = object::Instantiate<FrontBackGround>(eLayerType::FrontBackground);
		SpriteRenderer* fbgsr = fbg->AddComponent<SpriteRenderer>();
		fbgsr->SetImage(Scene05Front);
		fbgsr->SetScale(Vector2(2.f, 2.f));
		fbg->GetComponent<Transform>()->SetPosition(Vector2(1413.f, 360.f));
		//fbgsr->SetAffectCamera(true);

		// Player
		Player* player = object::Instantiate<Player>(eLayerType::Player);
		Transform* player_tr = player->GetComponent<Transform>();
		player_tr->SetPosition(Vector2(130.0f, 145.0f));
		//player->GetComponent<Animator>()->SetAffectedCamera(true);
		_mPlayer = player;



		////Floor
		Floor* floor1 = object::Instantiate<Floor>(eLayerType::Floor);
		Collider* colfloor1 = floor1->AddComponent<Collider>();
		colfloor1->SetSize(Vector2(540.0f, 50.0f));
		Transform* floortr1 = floor1->GetComponent<Transform>();
		floortr1->SetPosition(Vector2(270.0f, 450.0f));

		Floor* floor2 = object::Instantiate<Floor>(eLayerType::Floor);
		Collider* colfloor2 = floor2->AddComponent<Collider>();
		colfloor2->SetSize(Vector2(650.0f, 50.0f));
		Transform* floortr2 = floor2->GetComponent<Transform>();
		floortr2->SetPosition(Vector2(830.0f, 565.0f));

		Floor* floor3 = object::Instantiate<Floor>(eLayerType::Floor);
		Collider* colfloor3 = floor3->AddComponent<Collider>();
		colfloor3->SetSize(Vector2(150.0f, 50.0f));
		Transform* floortr3 = floor3->GetComponent<Transform>();
		floortr3->SetPosition(Vector2(1200.f, 695.0f));

		Floor* floor4 = object::Instantiate<Floor>(eLayerType::Floor);
		Collider* colfloor4 = floor4->AddComponent<Collider>();
		colfloor4->SetSize(Vector2(650.0f, 50.0f));
		Transform* floortr4 = floor4->GetComponent<Transform>();
		floortr4->SetPosition(Vector2(1590.f, 810.0f));

		Floor* floor5 = object::Instantiate<Floor>(eLayerType::Floor);
		Collider* colfloor5 = floor5->AddComponent<Collider>();
		colfloor5->SetSize(Vector2(200.0f, 25.0f));
		Transform* floortr5 = floor5->GetComponent<Transform>();
		floortr5->SetPosition(Vector2(1383.f, 552.0f));

		Floor* floor6 = object::Instantiate<Floor>(eLayerType::Floor);
		Collider* colfloor6 = floor6->AddComponent<Collider>();
		colfloor6->SetSize(Vector2(170.0f, 25.0f));
		Transform* floortr6 = floor6->GetComponent<Transform>();
		floortr6->SetPosition(Vector2(1649.f, 500.0f));

		Floor* floor7 = object::Instantiate<Floor>(eLayerType::Floor);
		Collider* colfloor7 = floor7->AddComponent<Collider>();
		colfloor7->SetSize(Vector2(210.0f, 25.0f));
		Transform* floortr7 = floor7->GetComponent<Transform>();
		floortr7->SetPosition(Vector2(1635.f, 310.0f));

		Floor* floor8 = object::Instantiate<Floor>(eLayerType::Floor);
		Collider* colfloor8 = floor8->AddComponent<Collider>();
		colfloor8->SetSize(Vector2(790.0f, 40.0f));
		Transform* floortr8 = floor8->GetComponent<Transform>();
		floortr8->SetPosition(Vector2(2215.f, 543.0f));

		Floor* floor9 = object::Instantiate<Floor>(eLayerType::Floor);
		Collider* colfloor9 = floor9->AddComponent<Collider>();
		colfloor9->SetSize(Vector2(210.0f, 40.0f));
		Transform* floortr9 = floor9->GetComponent<Transform>();
		floortr9->SetPosition(Vector2(2690.f, 442.0f));

		/////////////////// Wall
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

		Wall* wall1 = object::Instantiate<Wall>(eLayerType::Wall);
		Collider* colwall1 = wall1->AddComponent<Collider>();
		colwall1->SetSize(Vector2(50.0f, 170.0f));
		Transform*  tr = wall1->GetComponent<Transform>();
		tr->SetPosition(Vector2(520.f, 515.0f));

		Wall* wall2 = object::Instantiate<Wall>(eLayerType::Wall);
		Collider* colwall2 = wall2->AddComponent<Collider>();
		colwall2->SetSize(Vector2(50.0f, 170.0f));
		tr = wall2->GetComponent<Transform>();
		tr->SetPosition(Vector2(1133.f, 628.0f));

		Wall* wall3 = object::Instantiate<Wall>(eLayerType::Wall);
		Collider* colwall3 = wall3->AddComponent<Collider>();
		colwall3->SetSize(Vector2(50.0f, 170.0f));
		tr = wall3->GetComponent<Transform>();
		tr->SetPosition(Vector2(1255.f, 758.0f));

		Wall* wall4 = object::Instantiate<Wall>(eLayerType::Wall);
		Collider* colwall4 = wall4->AddComponent<Collider>();
		colwall4->SetSize(Vector2(50.0f, 150.0f));
		tr = wall4->GetComponent<Transform>();
		tr->SetPosition(Vector2(2606.f, 500.0f));
		wall4->SetRight(false);

		Wall* wall5 = object::Instantiate<Wall>(eLayerType::Wall);
		Collider* colwall5 = wall5->AddComponent<Collider>();
		colwall5->SetSize(Vector2(40.0f, 320.0f));
		tr = wall5->GetComponent<Transform>();
		tr->SetPosition(Vector2(1910.f, 690.0f));
		wall5->SetRight(false);

		// Portal
		Portal* portal2 = object::Instantiate<Portal>(eLayerType::Portal);
		Collider* colportal2 = portal2->AddComponent<Collider>();
		colportal2->SetNotColColor(RGB(50, 50, 255));
		colportal2->SetSize(Vector2(70.0f, 350.0f));
		tr = portal2->GetComponent<Transform>();
		colportal2->SetOffset(Vector2(0.f, -30.f));
		tr->SetPosition(Vector2(_mLimitRightX - 25.0f, 300.0f));

		// Sound
		//Sound* sound = Resources::Load<Sound>(L"bgm", L"..\\Resources\\sound\\Brotherhood_Ambient.wav");
		//sound->Play(true);

		// 충돌 체크
		CollisionMgr::CollisionLayerCheck(eLayerType::Projectile, eLayerType::Player, true);
		CollisionMgr::CollisionLayerCheck(eLayerType::Projectile, eLayerType::Floor, true);
		CollisionMgr::CollisionLayerCheck(eLayerType::Projectile, eLayerType::Wall, true);
		CollisionMgr::CollisionLayerCheck(eLayerType::Projectile, eLayerType::Attack, true);

		//Sound
		//Resources::Load<Sound>(L"tutorialSceneBgm", L"..\\Resources\\sound\\Brotherhood_Ambient.wav");

	}
	void Scene05::SceneEnter()
	{
		Camera::SetTarget(_mPlayer);

		Camera::SetCameraLimit_Left(_mLImitLeftX);
		Camera::SetCameraLimit_Right(_mLimitRightX);
		Camera::SetCameraLimit_Y(511.f);
		//Resources::Find<Sound>(L"tutorialSceneBgm")->Play(true);

	}
	void Scene05::SceneOut()
	{
		Camera::SetTarget(nullptr);
		//Resources::Find<Sound>(L"tutorialSceneBgm")->Stop(true);
	}
	void Scene05::Update()
	{
		Scene::Update();
		if (_mStoner1 && _mPlayer->GetComponent<Transform>()->GetPosition().x >=920.f)
		{
			_mStoner1 = false;
			// Monster
			Stoner* Stoner1 = object::Instantiate<Stoner>(eLayerType::Monster);
			Transform* St_tr1 = Stoner1->GetComponent<Transform>();
			St_tr1->SetPosition(Vector2(1620.f, 290.0f));
		}

		if (_mStoner2 && _mPlayer->GetComponent<Transform>()->GetPosition().x >= 1250.f )
		{
			_mStoner2 = false;
			// Monster
			Stoner* Stoner2 = object::Instantiate<Stoner>(eLayerType::Monster);
			Transform* St_tr2 = Stoner2->GetComponent<Transform>();
			St_tr2->SetPosition(Vector2(1560, 760.0f));
		}

		//// N키 누를시 씬 전환
		if (Input::GetKeyUp(eKeyCode::M))
		{
			SceneMgr::LoadScene(L"SecondBossScene");
		}

	}
	void Scene05::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

}
