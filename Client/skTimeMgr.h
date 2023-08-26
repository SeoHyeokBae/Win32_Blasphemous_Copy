#pragma once
#include "CommonInclude.h"

namespace sk
{
	class TimeMgr
	{
	public:
		void static Initialize();
		void static Update();
		void static Render(HDC hdc);

		__forceinline static float DeltaTime() { return _mDeltaTime; }

	private:
		static LARGE_INTEGER _mCpuFrequency; // LARGE_INTEGER 16바이트
		static LARGE_INTEGER _mPrevFrequency;
		static LARGE_INTEGER _mCurFrequency;
		static float _mDeltaTime; // DeltaTime 1프레임당 시간
		
	};
}


