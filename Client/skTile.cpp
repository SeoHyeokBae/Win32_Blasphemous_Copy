#include "skTile.h"
#include "skSpriteRenderer.h"
#include "skCollider.h"
#include "skTexture.h"
#include "skResources.h"

namespace sk
{
	Tile::Tile()
	{
	}

	Tile::~Tile()
	{
	}

	void Tile::Initialize()
	{
	}

	void Tile::Update()
	{
		GameObject::Update();
	}

	void Tile::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}