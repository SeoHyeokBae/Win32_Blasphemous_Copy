#include "skPlayScene1.h"
#include "skSpriteRenderer.h"
#include "skObject.h"
#include "skInput.h"
#include "skTransform.h"
#include "skResources.h"
#include "skCamera.h"
#include "skAnimator.h"
#include "skBackGround.h"
#include "skFrontBackGround.h"
#include "skCollider.h"
#include "skCollisionMgr.h"
#include "skRigidbody.h"
#include "skFloor.h"
#include "skMonster.h"
#include "skPortal.h"
#include "skWall.h"
#include "skGuideBotton.h"
#include "skSound.h"

namespace sk
{
	PlayScene1::PlayScene1()
		: _mPlayer(nullptr)
		, _mTexture(nullptr)
		, _mLimitLeftX(0)
		, _mLimitRightX(1280)
	{
	}
	PlayScene1::~PlayScene1()
	{
	}
	void PlayScene1::Initialize()
	{
		// background
		Texture* fbackground = Resources::Load<Texture>(L"firstscenebg"
				, L"..\\Resources\\Image\\playscenebackground.bmp");

		BackGround* firstscenebg_bg = object::Instantiate<BackGround>(eLayerType::Background);
		firstscenebg_bg->GetComponent<Transform>()->SetPosition(Vector2(800.0f, 300.0f));
		SpriteRenderer* firstscenebg_sr = firstscenebg_bg->AddComponent<SpriteRenderer>();
		firstscenebg_sr->SetImage(fbackground);
		firstscenebg_sr->SetScale(Vector2(2.0f, 2.0f));
		firstscenebg_sr->SetCameraRatio(Vector2(3.5f, 3.5f));


		//// middle
		Texture* middleimg = Resources::Load<Texture>(L"Middleimage"
			, L"..\\Resources\\Image\\playscenemiddleground.bmp");

		BackGround* middleimg_bg = object::Instantiate<BackGround>(eLayerType::Background);
		middleimg_bg->GetComponent<Transform>()->SetPosition(Vector2(1250.0f, 600.0f));
		SpriteRenderer* middleimg_sr = middleimg_bg->AddComponent<SpriteRenderer>();
		middleimg_sr->SetImage(middleimg);
		middleimg_sr->SetScale(Vector2(2.0f, 2.0f));
		middleimg_sr->SetCameraRatio(Vector2(1.5f, 1.5f));

		///////////////////////////////////////////////////////////////////////////
		// front tile
		Texture* bgimg1 = Resources::Load<Texture>(L"BackGroundImage1"
			, L"..\\Resources\\Image\\background.bmp");


		BackGround* Bg1 = object::Instantiate<BackGround>(eLayerType::Background);
		Bg1->GetComponent<Transform>()->SetPosition(Vector2(1700.0f, 869.0f));
		SpriteRenderer* Bgsr1 = Bg1->AddComponent<SpriteRenderer>();
		Bgsr1->SetImage(bgimg1);
		Bgsr1->SetScale(Vector2(2.0f,2.0f));
		//Bgsr1->SetAffectCamera(true);
		
		// 카메라 제한거리
		_mLimitLeftX = Bg1->GetComponent<Transform>()->GetPosition().x - bgimg1->GetWidth();
		_mLimitRightX = Bg1->GetComponent<Transform>()->GetPosition().x + bgimg1->GetWidth();

		///////////////////////////////////////////////////////////////////////////////
		// front
		Texture* bgfimg = Resources::Load<Texture>(L"BackGroundImage"
			, L"..\\Resources\\Image\\front.bmp");

		FrontBackGround* Bgfront = object::Instantiate<FrontBackGround>(eLayerType::FrontBackground);
		Bgfront->GetComponent<Transform>()->SetPosition(Vector2(1700.0f, 1261.0f));
		SpriteRenderer* Bgsr = Bgfront->AddComponent<SpriteRenderer>();
		Bgsr->SetImage(bgfimg);
		Bgsr->SetScale(Vector2(2.0f, 2.0f));
		//Bgsr->SetAffectCamera(false);


		// Player
		_mPlayer = object::Instantiate<Player>(eLayerType::Player);
		Transform* tr = _mPlayer->GetComponent<Transform>();
		tr->SetPosition(Vector2(990.0f, 630.0f));
		_mPlayer->GetComponent<Animator>()->SetAffectedCamera(true);

		Texture* start = Resources::Load<Texture>(L"IsDown", L"..\\Resources\\image\\IsDown.bmp");
		Animator* startanime = _mPlayer->GetComponent<Animator>();
		startanime->SetScale(Vector2(2.0f, 2.0f));
		startanime->CreateAnimation(L"IsDown", start, Vector2(0.0f, 0.0f), Vector2(87.0f, 22.0f), 1, Vector2(5.0f, 255.0f), 0.1f);
		startanime->PlayAnimation(L"IsDown", false);
		_mPlayer->SetState(Player::eState::RISING);
		


		// Floor ( Pixel )
		Texture* floorb = Resources::Load<Texture>(L"floor"
			, L"..\\Resources\\Image\\startfloor.bmp");
		_mPlayer->_mFloorTexture = floorb;

		Floor* floor = object::Instantiate<Floor>(eLayerType::Floor);
		SpriteRenderer* floorsr = floor->AddComponent<SpriteRenderer>();
		floorsr->SetImage(floorb);
		//floorsr->SetScale(Vector2(2.0f, 2.0f));
		floorsr->SetAlpha(0.0f);
		//floorsr->SetAffectCamera(false);
		tr = floor->GetComponent<Transform>();
		tr->SetPosition(Vector2(1700.0f, 869.0f));
		//tr->SetPosition(Vector2(1650.0f, 635.0f));

		// Wall
		Wall* wall_left = object::Instantiate<Wall>(eLayerType::Wall);
		Collider* colwall = wall_left->AddComponent<Collider>();
		colwall->SetSize(Vector2(100.0f, 1000.0f));
		tr = wall_left->GetComponent<Transform>();
		//colwall->SetOffset(Vector2(0.f, -30.f));
		tr->SetPosition(Vector2(_mLimitLeftX + 100.0f, 800.0f));
		

		Wall* wall_right = object::Instantiate<Wall>(eLayerType::Wall);
		Collider* colwall2 = wall_right->AddComponent<Collider>();
		colwall2->SetSize(Vector2(100.0f, 1000.0f));
		tr = wall_right->GetComponent<Transform>();
		wall_right->SetRight(false);
		tr->SetPosition(Vector2(_mLimitRightX + 50.0f, 1140.0f));

		// Portal
		Portal* portal = object::Instantiate<Portal>(eLayerType::Portal);
		Collider* colportal = portal->AddComponent<Collider>();
		colportal->SetNotColColor(RGB(50,50,255));
		colportal->SetSize(Vector2(70.0f, 350.0f));
		tr = portal->GetComponent<Transform>();
		colportal->SetOffset(Vector2(0.f, -30.f));
		tr->SetPosition(Vector2(_mLimitRightX - 60.0f, 1500.0f));

		// 충돌 체크
		CollisionMgr::CollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
		CollisionMgr::CollisionLayerCheck(eLayerType::Player, eLayerType::Wall, true);
		CollisionMgr::CollisionLayerCheck(eLayerType::Player, eLayerType::Portal, true);

		//Sound
		Resources::Load<Sound>(L"PlaySceneBgm", L"..\\Resources\\sound\\Brotherhood.wav");
	}
	void PlayScene1::SceneEnter()
	{
		Camera::SetTarget(_mPlayer);
		Resources::Find<Sound>(L"PlaySceneBgm")->Play(true);
		Resources::Find<Sound>(L"PlaySceneBgm")->SetVolume(5);
		Resources::Find<Sound>(L"ZONE_INFO")->Play(false);
		Resources::Find<Sound>(L"ZONE_INFO")->SetVolume(10);

		Camera::SetCameraLimit_Left(_mLimitLeftX);
		Camera::SetCameraLimit_Right(_mLimitRightX);
		Player::Info info = { 50,50,5,1 };
		_mPlayer->SetInfo(info);

		// F버튼 UI
		GuideBotton* PrssF = object::Instantiate<GuideBotton>(eLayerType::UI);
		Transform* buttontr = PrssF->GetComponent<Transform>();
		buttontr->SetPosition(Vector2(990.0f, 690.0f));
	}

	void PlayScene1::SceneOut()
	{
		Camera::SetTarget(nullptr);
		Resources::Find<Sound>(L"PlaySceneBgm")->Stop(true);
	}

	void PlayScene1::Update()
	{
		Scene::Update();


		if (Input::GetKeyUp(eKeyCode::N))
		{
			SceneMgr::LoadScene(L"TitleScene");
		}

		if (Input::GetKeyUp(eKeyCode::M))
		{
			SceneMgr::LoadScene(L"TutorialScene");
		}


	}
	void PlayScene1::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

}
