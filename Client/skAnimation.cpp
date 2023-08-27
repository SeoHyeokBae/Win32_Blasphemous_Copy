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
