#include "skTimeMgr.h"
#include "skApplication.h"

extern sk::Application application;

namespace sk
{
	LARGE_INTEGER TimeMgr::_mCpuFrequency = {};
	LARGE_INTEGER TimeMgr::_mPrevFrequency = {};
	LARGE_INTEGER TimeMgr::_mCurFrequency = {};
	float TimeMgr::_mDeltaTime = 0.0f;
	bool TimeMgr::_mbDelay = false;
	float TimeMgr::_mfDelayTime = 0.1f;
	float TimeMgr::_mfDelayAcc = 0.f;

	void TimeMgr::Initialize()
	{
		// CPU 고유 진동수
		QueryPerformanceFrequency(&_mCpuFrequency);

		// 프로그램이 시작됐을때 진동수
		QueryPerformanceCounter(&_mPrevFrequency);
	}

	void TimeMgr::Update()
	{
		QueryPerformanceCounter(&_mCurFrequency);

		float DifferenceFrequency
			= static_cast<float>(_mCurFrequency.QuadPart - _mPrevFrequency.QuadPart);

		_mDeltaTime = DifferenceFrequency / static_cast<float>(_mCpuFrequency.QuadPart);
		_mPrevFrequency.QuadPart = _mCurFrequency.QuadPart;

		if (_mbDelay)
		{
			_mfDelayAcc += _mDeltaTime;
			_mDeltaTime = 0.f;

			if (_mfDelayAcc > _mfDelayTime)
			{
				_mfDelayAcc = 0.f;
				_mbDelay = false;
			}
		}

	}

	void TimeMgr::Render(HDC hdc)
	{
		//static float TimeCheck = 0.0f; // 시간 누적
		//
		//TimeCheck += _mDeltaTime; // 1초당 프레임 수를 체크하기위함
		//if (TimeCheck >= 1.0f)
		//{
		//	wchar_t szFloat[50] = {};
		//	float fps = 1.0f / _mDeltaTime; // fps = 1초당 프레임수

		//	swprintf_s(szFloat, 50, L"fps : %f DT : %f", fps, _mDeltaTime);
		//	int strLen = wcsnlen_s(szFloat, 50);
		//	SetWindowText(application.GetHwnd(), szFloat);
		//	//TextOut(hdc, 10, 10, szFloat, strLen);

		//	TimeCheck = 0.0f;
		//}
	}
	void TimeMgr::Delay()
	{
		_mbDelay = true;
	}
}