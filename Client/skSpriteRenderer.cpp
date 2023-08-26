#include "skSpriteRenderer.h"
#include "skTransform.h"
#include "skGameObject.h"
#include "skCamera.h"
#include "skTexture.h"

namespace sk
{
	SpriteRenderer::SpriteRenderer() :
		Component(eComponentType::SpriteRenderer)
		, _mScale(Vector2::One)
		, _mTexture(nullptr)
		, _mAlpha(1.0f)
		, _mbTile(false)
		, _mbAffectCamera(true)
		, _mCameraRatio(Vector2::One)
		, _mOffset(Vector2::Zero)
	{
	}
	SpriteRenderer::~SpriteRenderer()
	{
	}
	void SpriteRenderer::Initialize()
	{
	}
	void SpriteRenderer::Update()
	{
	}
	void SpriteRenderer::Render(HDC hdc)
	{
		if (_mTexture == nullptr)
			return;
		if (_mbTile)
		{
			GameObject* gameObj = GetOwner();
			Transform* tr = gameObj->GetComponent<Transform>();
			_mTexture->Render(hdc
				, tr->GetPosition()
				, Vector2(TILE_WIDTH, TILE_HEIGHT)
				// cut area
				, Vector2(_mTileIndexX * TILE_WIDTH
					, _mTileIndexY * TILE_HEIGHT)
				, Vector2(TILE_WIDTH ,TILE_HEIGHT)
				, _mOffset
				, _mScale
				, _mbAffectCamera
				, _mCameraRatio
				, _mAlpha
				, tr->GetRotation());
		}
		else
		{
			GameObject* gameObj = GetOwner();
			Transform* tr = gameObj->GetComponent<Transform>();
			_mTexture->Render(hdc
				, tr->GetPosition()
				, Vector2(_mTexture->GetWidth(), _mTexture->GetHeight())
				, Vector2(0.0f, 0.0f)
				, Vector2(_mTexture->GetWidth(), _mTexture->GetHeight())
				, _mOffset
				, _mScale
				, _mbAffectCamera
				, _mCameraRatio
				, _mAlpha
				, tr->GetRotation());
		}


	}
}