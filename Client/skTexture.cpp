#include "skTexture.h"
#include "skApplication.h"
#include "skResources.h"
#include "skTransform.h"
#include "skCamera.h"
#include "skGameObject.h"

extern sk::Application application;

namespace sk
{
	Texture::Texture() :
		 _mImage(nullptr) //png
		,_mBitmap(NULL)	//bmp
		,_mHdc(NULL)
		,_mWidth(0)
		,_mHeight(0)
		, _mType(eTextureType::None)
		, _mBackGround(false)
		//, _mbAffectCamera(true)
		//, _mbParallaxCamera(false)
	{
	}
	Texture::~Texture()
	{
		delete _mImage;
		_mImage = nullptr;

		DeleteObject(_mBitmap);
		_mBitmap = NULL;
	}

	Texture* Texture::Create(const std::wstring& name, UINT width, UINT height)
	{
		Texture* image = Resources::Find<Texture>(name);
		if (image != nullptr)
			return image;

		image = new Texture();
		image->SetWidth(width);
		image->SetHeight(height);
		HDC hdc = application.GetHdc();
		HBITMAP bitmap = CreateCompatibleBitmap(hdc, width, height);
		image->SetHBitmap(bitmap);

		HDC bitmapHdc = CreateCompatibleDC(hdc);
		image->SetHdc(bitmapHdc);

		HBITMAP defaultBitmap = (HBITMAP)SelectObject(bitmapHdc, bitmap);
		DeleteObject(defaultBitmap);

		image->SetName(name);
		Resources::Insert<Texture>(name, image);

		if (name.find(L"back") != std::string::npos || name.find(L"bg") != std::string::npos || name.find(L"middle") != std::string::npos || name.find(L"front") != std::string::npos)
			image->IsBackGround(true);

		return image;
	}

	HRESULT Texture::Load(const std::wstring& path)
	{
		// Ȯ���� ã��
		std::wstring ext 
			= path.substr(path.find_last_of(L".") + 1);
		if (ext == L"bmp")			// bmp �϶�
		{
			_mType = eTextureType::Bmp;
			_mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0
				, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			if (_mBitmap == nullptr)
				return S_FALSE;

			BITMAP info = {};
			GetObject(_mBitmap, sizeof(BITMAP), &info);

			if (info.bmBitsPixel == 32)
				_mType = eTextureType::AlphaBmp;

			_mWidth = info.bmWidth;
			_mHeight = info.bmHeight;

			HDC mainDC = application.GetHdc();
			_mHdc = CreateCompatibleDC(mainDC);

			HBITMAP defaultBitmap = (HBITMAP)SelectObject(_mHdc, _mBitmap);
			DeleteObject(defaultBitmap);
		}
		else if (ext == L"png")		// png �϶�
		{
			_mType = eTextureType::Png;
			// image.png ������ �̿��Ͽ� Image ��ü�� ����
			//HDC hdc = application.GetHdc();

			_mImage = Gdiplus::Image::FromFile(path.c_str());

			_mWidth = _mImage->GetWidth();
			_mHeight = _mImage->GetHeight();
			//Gdiplus::Graphics g(hdc);

			//// image.png ������ �̿��Ͽ� Image ��ü�� �����մϴ�.
			//g.DrawImage(image, x, y, width, height);

			//// ������ �޸� ����
			//delete image;
			//ReleaseDC(application.GetHwnd() , hdc);
		}

		return S_OK;

	}

	void Texture::Render(HDC hdc
		, Vector2 pos
		, Vector2 size
		, Vector2 leftTop
		, Vector2 rightBottom
		, Vector2 offset
		, Vector2 scale
		, bool affectCamera
		, Vector2 CameraRatio
		, float alpha
		, float rotate
		, float UIratio)
	{
		if (_mBitmap == nullptr && _mImage ==nullptr)
			return;

		if (affectCamera)
			pos = Camera::CalculatePosition(pos, CameraRatio);

		if (_mType == eTextureType::AlphaBmp)
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			// 0.0f ~ 1.0f -> 0 ~ 255
			alpha = (int)(alpha * 255.0f);
			
			if (alpha <= 0)
				alpha = 0;
			func.SourceConstantAlpha = alpha; // 0 ~ 255

			if (_mBackGround)
			{
				Vector2 LookPos = Camera::GetLookPos();
				int screenWidth = 1280; 
				int screenHeight = 720;

				// ȭ�鿡 ���̴� ���� ���
				int screenLeft = LookPos.x - (screenWidth / 2);
				int screenRight = LookPos.x + (screenWidth / 2);
				int screenTop = LookPos.y - (screenHeight / 2);
				int screenBottom = LookPos.y + (screenHeight / 2);

				// �ؽ�ó�� ���� ũ��
				int texWidth = size.x * scale.x;
				int texHeight = size.y * scale.y;

				// �߶� UV ���� ��� (����)
				leftTop.x = max(0, screenLeft - pos.x + (texWidth / 2));
				rightBottom.x = min(texWidth, screenRight - pos.x + (texWidth / 2));

				// �߶� UV ���� ��� (����)
				leftTop.y = max(0, screenTop - pos.y + (texHeight / 2));
				rightBottom.y = min(texHeight, screenBottom - pos.y + (texHeight / 2));

				// ȭ�� ������ ������ �κ��� ���� ���, �� �κ��� �����ϰ� �������ϵ��� ����
				if (leftTop.x >= rightBottom.x || leftTop.y >= rightBottom.y) {
					// ���� �ڸ� ������ ȭ�� ������ ���� ���, �׷����� �ʵ��� ó��
					return;
				}
			}

			AlphaBlend(hdc
				, (int)pos.x - (size.x * scale.x / 2.0f) + offset.x
				, (int)pos.y - (size.y * scale.y / 2.0f) + offset.y
				, size.x * scale.x * UIratio
				, size.y * scale.y
				, _mHdc
				, leftTop.x, leftTop.y
				, rightBottom.x, rightBottom.y
				, func);
		}
		else if (_mType == eTextureType::Png)
		{
			//// ���� ���ϴ� �ȼ��� ����ȭ ��ų��
			//Gdiplus::ImageAttributes imageAtt = {};
			//// ����ȭ ��ų �ȼ� �� ����
			//imageAtt.SetColorKey(Gdiplus::Color(255, 0, 255)
			//	, Gdiplus::Color(0, 0, 255));

			Gdiplus::Graphics graphics(hdc);
			graphics.TranslateTransform((float)pos.x, (float)pos.y);
			graphics.RotateTransform(rotate);
			graphics.TranslateTransform(-(float)pos.x, -(float)pos.y);
			graphics.DrawImage(_mImage
				, Gdiplus::Rect
				(
					(int)(pos.x - (size.x * scale.x / 2.0f) + offset.x)
					, (int)(pos.y - (size.y * scale.y / 2.0f) + offset.y)
					, (int)(size.x * scale.x)
					, (int)(size.y * scale.y)
				)
				, leftTop.x, leftTop.y
				, rightBottom.x, rightBottom.y
				, Gdiplus::UnitPixel
				, /*&imageAtt*/nullptr);
		}
		else if(_mType == eTextureType::Bmp)
		{	// ��������� ,, alpha(32)��Ʈ ���Ͼƴҽ�, png�Ͻ�
			TransparentBlt(hdc
				, (int)pos.x - (size.x * scale.x / 2.0f) + offset.x
				, (int)pos.y - (size.y * scale.y / 2.0f) + offset.y
				, size.x * scale.x
				, size.y * scale.y
				, _mHdc
				, leftTop.x, leftTop.y, rightBottom.x * UIratio, rightBottom.y
				, RGB(255, 0, 255));
		}
		// �߽�Ȯ��
		//Rectangle(hdc
		//	, pos.x, pos.y
		//	, pos.x + 10, pos.y + 10);
	}
	// �ȼ��浹
	COLORREF Texture::GetTexturePixel(int x, int y)
	{
		COLORREF rgb = GetPixel(_mHdc, x, y);

		return rgb;
	}
}