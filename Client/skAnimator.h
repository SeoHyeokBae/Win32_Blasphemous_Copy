#pragma once
#include "skComponent.h"
#include "skAnimation.h"

namespace sk
{
	using namespace math;
	class Animator : public Component
	{
	public:
		Animator();
		~Animator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		Animation* CreateAnimation(const std::wstring& name
			, class Texture* texture
			, Vector2 leftTop
			, Vector2 size
			, UINT spriteLength
			, Vector2 offset, float duration = 0.1f);
		
		void CreateAnimationFolder(const std::wstring& name
			, const std::wstring path
			, Vector2 offset = Vector2::Zero
			, float duration = 0.1f);

		Animation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop = false );

		bool IsActiveAnimationComplete() { return _mActiveAnimation->IsComplete(); }
		bool GetAffectedCamera() { return _mbAffectedCamera; }
		void SetAffectedCamera(bool enable) { _mbAffectedCamera = enable; }
		float GetAlpha() { return _mAlpha; }
		void SetAlpha(float alpha) { _mAlpha = alpha; }

		void SetScale(Vector2 scale) { _mScale = scale; }
		Vector2 GetScale() { return _mScale; }

		void SetWaiting(float wait) { _mWaiting = wait; }

		Animation* GetActiveAnime() { return _mActiveAnimation; }

	private:
		std::map<std::wstring, Animation*> _mAnimations;
		
		Animation* _mActiveAnimation;
		bool _mbLoop;
		bool _mbAffectedCamera;
		float _mAlpha;
		Vector2 _mScale;
		float _mWaiting;	// 애니메이션 대기 시간
		float _mWTime;		// 대기시간 저장
	};
}


