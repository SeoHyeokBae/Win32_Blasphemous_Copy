#include "skTitleScene.h"
#include "skPlayer.h"
#include "skSpriteRenderer.h"
#include "skObject.h"
#include "skResources.h"
#include "skBackGround.h"
#include "skCamera.h"
#include "skTransform.h"
#include "skInput.h"
#include "skSceneMgr.h"
#include "skAnimator.h"
#include "skBottonUI.h"
#include "skSound.h"
#include "skUI.h"

namespace sk
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		BackGround* background = object::Instantiate<BackGround>(eLayerType::Background);
		background->GetComponent<Transform>()->SetPosition(Vector2(640.0f, 360.0f));

		Animator* at = background->AddComponent<Animator>();
		at->CreateAnimationFolder(L"Background", L"..\\Resources\\image\\main\\main_bg");
		at->SetScale(Vector2(2.0f, 2.0f));
		at->PlayAnimation(L"Background", true);


		///////////////////////////////////////////////////////////////////////////////////////////////////
		BackGround* bg2 = object::Instantiate<BackGround>(eLayerType::Background);
		bg2->GetComponent<Transform>()->SetPosition(Vector2(440.0f, 360.0f));


		Animator* at2 = bg2->AddComponent<Animator>();
		Texture* image = Resources::Load<Texture>(L"Background2", L"..\\Resources\\image\\main\\bg123.bmp");
		at2->SetScale(Vector2(2.0f, 2.0f));
		at2->CreateAnimation(L"Background2", image, Vector2(0.0f,0.0f), Vector2(440.0f,360.0f),14 , Vector2(0.0f, 0.0f),0.25f);
		//at2->SetAffectedCamera(true);
		at2->PlayAnimation(L"Background2", true);

		///////////////////////////////////////////////////////////////////////////////////////////////////
		BackGround* flower = object::Instantiate<BackGround>(eLayerType::Background);
		Transform* tr3 = flower->GetComponent<Transform>();

		tr3->SetPosition(Vector2(640.0f, 360.0f));

		Animator* at3 = flower->AddComponent<Animator>();
		Texture* image2 = Resources::Load<Texture>(L"Background_flower", L"..\\Resources\\image\\main\\flower1.bmp");
		at3->CreateAnimation(L"Background_flower", image2, Vector2(0.0f, 0.0f), Vector2(640.0f, 360.0f), 6, Vector2(0.0f, 0.0f), 0.1f); 
		at3->SetScale(Vector2(2.0f, 2.0f));
		at3->SetWaiting(3.0f);
		//at3->SetAffectedCamera(true);
		at3->PlayAnimation(L"Background_flower", true);

		Animator* at4 = flower->AddComponent<Animator>();
		Texture* image3 = Resources::Load<Texture>(L"Background_flower2", L"..\\Resources\\image\\main\\flower2.bmp");
		at4->CreateAnimation(L"Background_flower2", image3, Vector2(0.0f, 0.0f), Vector2(640.0f, 360.0f), 44, Vector2(0.0f, 0.0f), 0.07f);
		at4->SetScale(Vector2(2.0f, 2.0f));
		//at4->SetAffectedCamera(true);
		at4->PlayAnimation(L"Background_flower2", true);

		// UI
		// 
		//start
		Texture* startbutton = Resources::Load<Texture>(L"start", L"..\\Resources\\image\\ui\\start.png");
		Texture* startbutton_on = Resources::Load<Texture>(L"start_on", L"..\\Resources\\image\\ui\\starton.png");
		Texture* alliedCherub = Resources::Load<Texture>(L"AlliedCherub", L"..\\Resources\\image\\effect\\alliedCherub.png");

		_mSelectEff = object::Instantiate<UI>(eLayerType::UI);
		Animator* anim = _mSelectEff->AddComponent<Animator>();
		anim->CreateAnimation(L"alliedCherub", alliedCherub, Vector2(0.0f, 0.0f), Vector2(70.0f, 70.0f), 11, Vector2(15.0f, -5.0f), 0.07f);
		anim->SetScale(Vector2(2.0f, 2.0f));

		BottonUI* StartButton = object::Instantiate<BottonUI>(eLayerType::UI);
		_mStartbutton = StartButton;

		Transform* tr = StartButton->GetComponent<Transform>();
		tr->SetPosition(Vector2(1130.0f, 560.0f));

		StartButton->SetSelect(BottonUI::eState::On, startbutton_on);
		StartButton->SetSelect(BottonUI::eState::Off, startbutton);

		//exit
		Texture* exitbutton = Resources::Load<Texture>(L"exit", L"..\\Resources\\image\\ui\\exit.png");
		Texture* exitbutton_on = Resources::Load<Texture>(L"exit_on", L"..\\Resources\\image\\ui\\exiton.png");

		BottonUI* ExitButton = object::Instantiate<BottonUI>(eLayerType::UI);
		_mExitbutton = ExitButton;
		
		tr = ExitButton->GetComponent<Transform>();
		tr->SetPosition(Vector2(1130.0f, 610.0f));

		ExitButton->SetSelect(BottonUI::eState::On, exitbutton_on);
		ExitButton->SetSelect(BottonUI::eState::Off, exitbutton);

		// Sound
		Resources::Load<Sound>(L"TitleBgm", L"..\\Resources\\sound\\Intro_Flagellant.wav");
		Resources::Load<Sound>(L"ZONE_INFO", L"..\\Resources\\sound\\ZONE_INFO.wav");
		Resources::Load<Sound>(L"Relic", L"..\\Resources\\sound\\Relic.wav");
		
		//Camera::SetTarget(bg);
	}

	void TitleScene::SceneEnter()
	{
		Resources::Find<Sound>(L"TitleBgm")->Play(true);
		Resources::Find<Sound>(L"TitleBgm")->SetVolume(20);
	}

	void TitleScene::SceneOut()
	{
		Resources::Find<Sound>(L"TitleBgm")->Stop(true);
	}

	void TitleScene::Update()
	{
		Scene::Update();

		// 게임시작 / 종료
		if (Input::GetKeyDown(eKeyCode::Enter))
		{
			if (_mStartbutton->GetBottonState()==BottonUI::eState::On)
			{
				SceneMgr::LoadScene(L"PlayScene1");
			}
			else if (_mExitbutton->GetBottonState() == BottonUI::eState::On)
			{
				WM_CLOSE;
				// To Do
			}
		}

		if (Input::GetKeyDown(eKeyCode::W) || Input::GetKeyDown(eKeyCode::S))
		{
			if (_mStartbutton->GetBottonState() == BottonUI::eState::On)
			{
				_mStartbutton->SetBottonState(BottonUI::eState::Off);
				_mExitbutton->SetBottonState(BottonUI::eState::On);
				Transform* tr = _mSelectEff->GetComponent<Transform>();
				tr->SetPosition(Vector2(1000.0f, 610.0f));
				Animator* anim = _mSelectEff->GetComponent<Animator>();
				anim->PlayAnimation(L"alliedCherub",true);
			}
			else
			{
				_mStartbutton->SetBottonState(BottonUI::eState::On);
				_mExitbutton->SetBottonState(BottonUI::eState::Off);
				Transform* tr = _mSelectEff->GetComponent<Transform>();
				tr->SetPosition(Vector2(1000.0f, 560.0f));
				Animator* anim = _mSelectEff->GetComponent<Animator>();
				anim->PlayAnimation(L"alliedCherub", true);
			}
		}

		if (Input::GetKeyUp(eKeyCode::N))
		{
			SceneMgr::LoadScene(L"TitleScene");
		}

		if (Input::GetKeyUp(eKeyCode::M))
		{
			SceneMgr::LoadScene(L"PlayScene1");
		}

	}
	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

}