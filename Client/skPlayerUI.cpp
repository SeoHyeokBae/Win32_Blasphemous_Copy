#include "skPlayerUI.h"
#include "skTransform.h"
#include "skMonster.h"
#include "skObject.h"
#include "skTimeMgr.h"
#include "skCamera.h"
#include "skResources.h"
#include "skSpriteRenderer.h"

namespace sk
{
	PlayerUI::PlayerUI() :
		_mPlayer(nullptr)
		, _mTime(0.f)
		, _mState(Player::eState::NONE)
	{
	}
	PlayerUI::~PlayerUI()
	{
	}
	void PlayerUI::Initialize()
	{
		Texture* Player_HpBar = Resources::Load<Texture>(L"Player_HpBar"
			, L"..\\Resources\\image\\Player_HpBar.bmp");
		Texture* Full_Flask = Resources::Load<Texture>(L"Full_Flask"
			, L"..\\Resources\\image\\Full_Flask.bmp");
		Texture* Empty_Flask = Resources::Load<Texture>(L"Empty_Flask"
			, L"..\\Resources\\image\\Empty_Flask.bmp");
		SpriteRenderer* sr = AddComponent<SpriteRenderer>();
		sr->SetImage(Player_HpBar);
		sr->SetAffectCamera(false);
		sr->SetOffset(Vector2(200.f, 85.f));

		SpriteRenderer* sr1 = AddComponent<SpriteRenderer>();
		sr1->SetImage(Full_Flask);
		sr1->SetAffectCamera(false);
		sr1->SetOffset(Vector2(160.f, 115.f));

		SpriteRenderer* sr2 = AddComponent<SpriteRenderer>();
		sr2->SetImage(Empty_Flask);
		sr2->SetAffectCamera(false);
		sr2->SetOffset(Vector2(200.f, 115.f));

	}
	void PlayerUI::Update()
	{
		GameObject::Update();
	}
	void PlayerUI::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}