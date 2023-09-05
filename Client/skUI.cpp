#include "skUI.h"

namespace sk
{
	UI::UI()
	{
	}
	UI::~UI()
	{
	}
	void UI::Initialize()
	{
	}
	void UI::Update()
	{
		GameObject::Update();

	}
	void UI::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}