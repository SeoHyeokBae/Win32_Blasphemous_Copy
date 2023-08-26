#include "skBottonUI.h"
#include "skTexture.h"
#include "skResources.h"
#include "skSpriteRenderer.h"
#include"skInput.h"

namespace sk
{
	BottonUI::BottonUI()
		: _mCurState(eState::Off)
	{

	}
	BottonUI::~BottonUI()
	{
	}
	void BottonUI::Initialize()
	{
		AddComponent<SpriteRenderer>();

		_mSelect.resize((UINT)eState::None);
		for (size_t i = 0; i < (UINT)eState::None; i++)
		{
			_mSelect[i] = nullptr;
		}

	}
	void BottonUI::Update()
	{
		GameObject::Update();

		SpriteRenderer* sr = GetComponent<SpriteRenderer>();
		if (_mCurState == eState::On)
		{
			sr->SetImage(_mSelect[(UINT)eState::On]);
		}
		else if (_mCurState == eState::Off)
		{
			sr->SetImage(_mSelect[(UINT)eState::Off]);
		}
		sr->SetScale(Vector2(2.f, 2.f));
	}
	void BottonUI::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}