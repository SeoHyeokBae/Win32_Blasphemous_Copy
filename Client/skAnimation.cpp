#include "skAnimation.h"
#include "skTexture.h"
#include "skAnimator.h"
#include "skTimeMgr.h"
#include "skTransform.h"
#include "skGameObject.h"
#include "skCamera.h"

namespace sk
{
	Animation::Animation()
		: _mAnimator(nullptr)
		, _mTexture(nullptr)
		, _mSpriteSheet{}
		, _mIndex(-1)
		, _mTime(0.0f)
		, _mbComplete(false)
	{
	}

	Animation::~Animation()
	{
	}

	void Animation::Update()
	{
		if (_mbComplete)
			return;

		_mTime += TimeMgr::DeltaTime();
		if (_mSpriteSheet[_mIndex].duration < _mTime)
		{
			//_mTime = 0.0f; 
			_mTime = _mTime - _mSpriteSheet[_mIndex].duration;

			if (_mIndex < _mSpriteSheet.size() - 1)
				_mIndex++;
			else
				_mbComplete = true;
		}
	}

	void Animation::Render(HDC hdc)
	{
		if (_mTexture == nullptr)
			return;

		Sprite sprite = _mSpriteSheet[_mIndex];

		Transform* tr = _mAnimator->GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		Animator* animator = _mAnimator;

		_mTexture->Render(hdc
			, pos
			, sprite.size
			, sprite.leftTop
			, sprite.size
			, sprite.offset
			, animator->GetScale()
			, animator->GetAlpha())
			, tr->GetRotation();

		//if (_mAnimator->GetAffectedCamera())
		//	pos = Camera::CalculatePosition(pos);

		//Vector2 scale = _mAnimator->GetScale();

		//if (_mTexture->GetType() == eTextureType::AlphaBmp)
		//{
		//	BLENDFUNCTION func = {};
		//	func.BlendOp = AC_SRC_OVER;
		//	func.BlendFlags = 0;
		//	func.AlphaFormat = AC_SRC_ALPHA;
		//	// 0.0f ~ 1.0f -> 0 ~ 255
		//	int alpha = (int)(_mAnimator->GetAlpha() * 255.0f);
		//	if (alpha <= 0)
		//		alpha = 0;
		//	func.SourceConstantAlpha = alpha; // 0 ~ 255

		//	AlphaBlend(hdc, (int)pos.x - ((_mSpriteSheet[_mIndex].size.x / 2.0f) + _mSpriteSheet[_mIndex].offset.x) * scale.x
		//		, (int)pos.y - ((_mSpriteSheet[_mIndex].size.y / 2.0f) + _mSpriteSheet[_mIndex].offset.y) * scale.y
		//		, _mSpriteSheet[_mIndex].size.x * scale.x
		//		, _mSpriteSheet[_mIndex].size.y * scale.y
		//		, _mTexture->GetHdc()
		//		, _mSpriteSheet[_mIndex].leftTop.x
		//		, _mSpriteSheet[_mIndex].leftTop.y
		//		, _mSpriteSheet[_mIndex].size.x
		//		, _mSpriteSheet[_mIndex].size.y
		//		, func);
		//}
		//else if (_mTexture->GetType() == eTextureType::Bmp)	// 24비트 에니메이션
		//{
		//	TransparentBlt(hdc
		//		, (int)pos.x - ((_mSpriteSheet[_mIndex].size.x / 2.0f) + _mSpriteSheet[_mIndex].offset.x) * scale.x
		//		, (int)pos.y - ((_mSpriteSheet[_mIndex].size.y / 2.0f) + _mSpriteSheet[_mIndex].offset.y) * scale.y
		//		, (int)(_mSpriteSheet[_mIndex].size.x) * scale.x
		//		, (int)(_mSpriteSheet[_mIndex].size.y) * scale.y
		//		, _mTexture->GetHdc()
		//		, (int)(_mSpriteSheet[_mIndex].leftTop.x)
		//		, (int)(_mSpriteSheet[_mIndex].leftTop.y)
		//		, (int)(_mSpriteSheet[_mIndex].size.x)
		//		, (int)(_mSpriteSheet[_mIndex].size.y)
		//		, RGB(255, 0, 255));
		//}
		//else
		//{	// 폴더 실행시 
		//	TransparentBlt(hdc
		//		, (int)pos.x - ((_mSpriteSheet[_mIndex].size.x / 2.0f) + _mSpriteSheet[_mIndex].offset.x)* scale.x
		//		, (int)pos.y - ((_mSpriteSheet[_mIndex].size.y / 2.0f) + _mSpriteSheet[_mIndex].offset.y)* scale.y
		//		, (int)(_mSpriteSheet[_mIndex].size.x) * scale.x
		//		, (int)(_mSpriteSheet[_mIndex].size.y) * scale.y
		//		, _mTexture->GetHdc()
		//		, (int)(_mSpriteSheet[_mIndex].leftTop.x)
		//		, (int)(_mSpriteSheet[_mIndex].leftTop.y)
		//		, (int)(_mSpriteSheet[_mIndex].size.x) 
		//		, (int)(_mSpriteSheet[_mIndex].size.y) 
		//		, RGB(255, 0, 255));
		//}
	}

	void Animation::Create(const std::wstring& name, Texture* texture
		, Vector2 leftTop, Vector2 size, Vector2 offset
		, UINT spriteLength, float duration)
	{
		_mTexture = texture;

		for (size_t i = 0; i < spriteLength; i++)
		{
			Sprite sprite = {};

			sprite.leftTop.x = leftTop.x + (size.x * i);
			sprite.leftTop.y = leftTop.y;
			// 아랫줄로 이어서 실행할때
			if (sprite.leftTop.x >= texture->GetWidth())
			{
				sprite.leftTop.x = sprite.leftTop.x - texture->GetWidth();
				sprite.leftTop.y = leftTop.y + size.y;
			}
			sprite.size = size;
			sprite.offset = offset;
			sprite.duration = duration;

			_mSpriteSheet.push_back(sprite);
		}
	}

	void Animation::Reset()
	{
		_mTime = 0.0f;
		_mIndex = 0;
		_mbComplete = false;
	}

}
