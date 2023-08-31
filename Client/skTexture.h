#pragma once
#include "skResource.h"

namespace sk
{
	using namespace math;
	enum class eTextureType
	{
		Bmp,
		AlphaBmp,
		Png,
		None,
	};

	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();


		static Texture* Create(const std::wstring& name, UINT width, UINT height);

		virtual HRESULT Load(const std::wstring& path) override;
		void Render(HDC hdc
			, Vector2 pos
			, Vector2 size
			, Vector2 leftTop
			, Vector2 rightBottom
			, Vector2 offset = Vector2::Zero
			, Vector2 scale = Vector2::One
			, bool affectCamera = true
			, Vector2 CameraRatio = Vector2::One
			, float alpha = 1.0f
			, float rotate = 0.0f
		    , float UIratio = 1.0f );

		COLORREF GetTexturePixel(int x, int y);

		UINT GetWidth() { return _mWidth; }
		void SetWidth(UINT width) { _mWidth = width; }
		UINT GetHeight() { return _mHeight; }
		void SetHeight(UINT height) { _mHeight = height; }

		HDC GetHdc() { return _mHdc; }
		eTextureType GetType() { return _mType; }
		void SetType(eTextureType type) { _mType = type; }
		Gdiplus::Image* GetImage() { return _mImage; }
		void SetHBitmap(HBITMAP bitmap) { _mBitmap = bitmap; }
		void SetHdc(HDC hdc) { _mHdc = hdc; }
		//void SetParallaxCamera(bool enable) { _mbParallaxCamera = enable; }

	private:
		eTextureType _mType;
		Gdiplus::Image* _mImage;		//png
		
		HBITMAP _mBitmap;				//bmp
		HDC _mHdc;
		UINT _mWidth;
		UINT _mHeight;

		//bool _mbParallaxCamera;
	};
}


