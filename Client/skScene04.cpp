#include "skScene04.h"
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
#include "skPortal.h"
#include "skWall.h"
#include "skGuideBotton.h"
#include "skSound.h"
#include "skNpcDeosgracias.h"
#include "skNpcPrayerTable.h""

namespace sk
{
	Scene04::Scene04()
		: _mPlayer(nullptr)
		, _mTexture(nullptr)
		, _mLimitLeftX(0)
		, _mLimitRightX(1280)
	{
	}
	Scene04::~Scene04()
	{
	}
	void Scene04::Initialize()
	{
		// background
		Texture* fbackground = Resources::Load<Texture>(L"Scene04back"
			, L"..\\Resources\\Image\\Scene04back.bmp");

		BackGround* firstscenebg_bg = object::Instantiate<BackGround>(eLayerType::Background);
		firstscenebg_bg->GetComponent<Transform>()->SetPosition(Vector2(1000.0f, 295.0f));
		SpriteRenderer* firstscenebg_sr = firstscenebg_bg->AddComponent<SpriteRenderer>();
		firstscenebg_sr->SetImage(fbackground);
		firstscenebg_sr->SetScale(Vector2(2.5f, 2.5f));
		firstscenebg_sr->SetCameraRatio(Vector2(6.0f, 6.0f));


		//// middle
		Texture* middleimg = Resources::Load<Texture>(L"Scene04back2"
			, L"..\\Resources\\Image\\Scene04back2.bmp");

		BackGround* middleimg_bg = object::Instantiate<BackGround>(eLayerType::Background);
		middleimg_bg->GetComponent<Transform>()->SetPosition(Vector2(1054.0f, 306.0f));
		SpriteRenderer* middleimg_sr = middleimg_bg->AddComponent<SpriteRenderer>();
		middleimg_sr->SetImage(middleimg);
		middleimg_sr->SetScale(Vector2(2.0f, 2.0f));


		middleimg_sr->SetCameraRatio(Vector2(1.5f, 1.5f));

		///////////////////////////////////////////////////////////////////////////
		// front tile
		Texture* bgimg1 = Resources::Load<Texture>(L"Scene04floor"
			, L"..\\Resources\\Image\\Scene04floor.bmp");

		BackGround* Bg1 = object::Instantiate<BackGround>(eLayerType::Background);
		Bg1->GetComponent<Transform>()->SetPosition(Vector2(1636.f, 361.0f));
		SpriteRenderer* Bgsr1 = Bg1->AddComponent<SpriteRenderer>();
		Bgsr1->SetImage(bgimg1);
		Bgsr1->SetScale(Vector2(2.0f, 2.0f));
		//Bgsr1->SetAffectCamera(true);

		// 카메라 제한거리
		_mLimitLeftX = Bg1->GetComponent<Transform>()->GetPosition().x - bgimg1->GetWidth();
		_mLimitRightX = Bg1->GetComponent<Transform>()->GetPosition().x + bgimg1->GetWidth();

		///////////////////////////////////////////////////////////////////////////////
		// front
		Texture* bgfimg = Resources::Load<Texture>(L"Scene04front"
			, L"..\\Resources\\Image\\Scene04front.bmp");

		FrontBackGround* Bgfront = object::Instantiate<FrontBackGround>(eLayerType::FrontBackground);
		Bgfront->GetComponent<Transform>()->SetPosition(Vector2(1636.0f, 362.0f));
		SpriteRenderer* Bgsr = Bgfront->AddComponent<SpriteRenderer>();
		Bgsr->SetImage(bgfimg);
		Bgsr->SetScale(Vector2(2.0f, 2.0f));
		//Bgsr->SetAffectCamera(false);


		// Player
		_mPlayer = object::Instantiate<Player>(eLayerType::Player);
		Transform* Player_tr = _mPlayer->GetComponent<Transform>();
		Player_tr->SetPosition(Vector2(250.0f, 200.0f));
		_mPlayer->GetComponent<Animator>()->SetAffectedCamera(true);

		// NPC
		NpcDeosgracias* npc = object::Instantiate<NpcDeosgracias>(eLayerType::Npc);
		Transform* npc_tr = npc->GetComponent<Transform>();
		npc_tr->SetPosition(Vector2(1300.0f, 385.0f));

		NpcPrayerTable* npc2 = object::Instantiate<NpcPrayerTable>(eLayerType::Npc);
		Transform* npc2_tr = npc2->GetComponent<Transform>();
		npc2_tr->SetPosition(Vector2(2100.0f, 475.0f));

		// Floor ( Pixel )
		Texture* floorb = Resources::Load<Texture>(L"Scene04stair"
			, L"..\\Resources\\Image\\Scene04stair2.bmp");
		_mPlayer->_mFloorTexture = floorb;

		Floor* floor = object::Instantiate<Floor>(eLayerType::Floor);
		SpriteRenderer* floorsr = floor->AddComponent<SpriteRenderer>();
		Transform* tr = floor->GetComponent<Transform>();
		floorsr->SetImage(floorb);
		floorsr->SetAlpha(0.0f);
		//floorsr->SetAffectCamera(false);
		tr = floor->GetComponent<Transform>();
		//tr->SetPosition(Vector2(280.0f, 360.0f));
		tr->SetPosition(Vector2(1636.0f, 360.0f));

		//Floor* floor1 = object::Instantiate<Floor>(eLayerType::Floor);
		//Collider* colfloor1 = floor1->AddComponent<Collider>();
		//colfloor1->SetSize(Vector2(2800.0f, 50.0f));
		//Transform* floortr1 = floor1->GetComponent<Transform>();
		//floortr1->SetPosition(Vector2(1900.0f, 647.0f));

		// Wall
		Wall* wall_left = object::Instantiate<Wall>(eLayerType::Wall);
		Collider* colwall = wall_left->AddComponent<Collider>();
		colwall->SetSize(Vector2(50.0f, 720.0f));
		tr = wall_left->GetComponent<Transform>();
		tr->SetPosition(Vector2(_mLimitLeftX + 100.0f, 360.0f));


		Wall* wall_right = object::Instantiate<Wall>(eLayerType::Wall);
		Collider* colwall2 = wall_right->AddComponent<Collider>();
		colwall2->SetSize(Vector2(50.0f, 720.0f));
		tr = wall_right->GetComponent<Transform>();
		wall_right->SetRight(false);
		tr->SetPosition(Vector2(_mLimitRightX+25.f, 360.0f));

		// Portal
		Portal* portal = object::Instantiate<Portal>(eLayerType::Portal);
		Collider* colportal = portal->AddComponent<Collider>();
		colportal->SetNotColColor(RGB(50, 50, 255));
		colportal->SetSize(Vector2(70.0f, 300.0f));
		tr = portal->GetComponent<Transform>();
		tr->SetPosition(Vector2(_mLimitRightX - 60.0f, 460.0f));

		// 충돌 체크
		CollisionMgr::CollisionLayerCheck(eLayerType::Npc, eLayerType::Player, true);

		//Sound
	}
	void Scene04::SceneEnter()
	{
		//Resources::Find<Sound>(L"PlaySceneBgm")->Play(true);
		Camera::SetTarget(_mPlayer);
		Camera::SetPlayMode(true);
		Camera::SetCameraLimit_Left(_mLimitLeftX);
		Camera::SetCameraLimit_Right(_mLimitRightX);
	}

	void Scene04::SceneOut()
	{
		Camera::SetTarget(nullptr);
		Camera::SetPlayMode(false);

		//Resources::Find<Sound>(L"PlaySceneBgm")->Stop(true);
	}

	void Scene04::Update()
	{
		Scene::Update();

		if (Input::GetKeyUp(eKeyCode::M))
		{
			SceneMgr::LoadScene(L"Scene05");
		}
	}
	void Scene04::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

}
