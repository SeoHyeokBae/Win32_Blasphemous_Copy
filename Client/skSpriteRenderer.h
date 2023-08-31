#pragma once
#include "skComponent.h"
#include "skTexture.h"

namespace sk
{
#define TILE_WIDTH 16
#define TILE_HEIGHT 16

	using namespace math;
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void SetImage(Texture* texture) { _mTexture = texture; }
		void SetScale(Vector2 scale) { _mScale = scale; }
		void SetAffectCamera(bool enable) { _mbAffectCamera = enable; }
		void SetCameraRatio(Vector2 ratio) { _mCameraRatio = ratio; }
		float GetAlpha() { return _mAlpha; }
		void SetAlpha(float alpha) { _mAlpha = alpha; }
		void SetUIratio(float ratio) { _mUIratio = ratio; }
		void SetTile(int x, int y) { _mbTile = true; _mTileIndexX = x; _mTileIndexY = y; }
		void SetOffset(Vector2 offset) { _mOffset = offset; }

	private:
		bool _mbAffectCamera; // 카메라에 영향을 받는가? true 

		bool _mbTile;
		int _mTileIndexX;
		int _mTileIndexY;

		Vector2 _mCameraRatio;
		Vector2 _mOffset;
		Texture* _mTexture;
		Vector2 _mScale;
		float _mAlpha; //투명도설정 0 ~ 1.0
		float _mUIratio;
	};

}

