#include "skToolScene.h"
#include "skTitleScene.h"
#include "skPlayer.h"
#include "skSpriteRenderer.h"
#include "skObject.h"
#include "skInput.h"
#include "skTexture.h"
#include "skTransform.h"
#include "skResources.h"
#include "skBackGround.h"
#include "skCamera.h"
#include "skTile.h"

namespace sk
{
	ToolScene::ToolScene()
	{
	}
	ToolScene::~ToolScene()
	{
	}
	void ToolScene::Initialize()
	{
	}

	void ToolScene::Update()
	{
		Scene::Update();
	}
	void ToolScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		//MoveToEx(hdc, 0, 0, nullptr);

		//LineTo(hdc, 200, 200);
	}
}