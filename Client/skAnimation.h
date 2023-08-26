#pragma once
#include "skResource.h"


namespace sk
{
	using namespace math;
	class Texture;
	class Animator;
	class Animation : public Resource
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;
			Vector2 size;
			Vector2 offset;
			float duration;

			Sprite()
				: leftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, offset(Vector2::Zero)
				, duration(0.0f)
			{}


		};

		Animation();
		~Animation();

		void Update();
		void Render(HDC hdc);

		virtual HRESULT Load(const std::wstring& path) { return S_FALSE; };

		void Create(const std::wstring& name
			, class Texture* texture
			, Vector2 leftTop, Vector2 size, Vector2 offset
			, UINT spriteLength, float duration);

		void Reset();

		bool IsComplete() { return _mbComplete; }
		void SetAnimator(Animator* animator) { _mAnimator = animator; }

		void SetIndex(int idx){ _mIndex = idx; }
		int GetIndex() { return _mIndex; }

	private:
		Animator* _mAnimator;
		Texture* _mTexture;

		std::vector<Sprite> _mSpriteSheet;
		int _mIndex;
		float _mTime;
		bool _mbComplete;
	};
}


