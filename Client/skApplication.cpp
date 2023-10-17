#include "skApplication.h"
#include "skInput.h"
#include "skTimeMgr.h"
#include "skSceneMgr.h"
#include "skTitleScene.h"
#include "skCamera.h"
#include "skCollisionMgr.h"
#include "skSoundMgr.h"

namespace sk 
{
	Application::Application() : 
		_mHwnd(NULL), 
		_mHdc(NULL),
		_mWidth(0),
		_mHeight(0),
		_mBackHdc(NULL),
		_mBackBuffer(NULL),
		_mExit(S_OK)
	{

	}

	Application::~Application()
	{

	}

	void Application::Initialize(HWND hwnd)
	{
		_mHwnd = hwnd;
		_mHdc = GetDC(_mHwnd);

		_mWidth = 1280;
		_mHeight = 720;

		RECT rt = { 0, 0, _mWidth, _mHeight };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

		// 윈도우 창 크기 맞춤
		SetWindowPos(_mHwnd , 
			nullptr , 0 , 0, rt.right - rt.left, rt.bottom -rt.top ,0 );
		ShowWindow(_mHwnd, true);

		// 윈도우 해상도 동일한 비트맵 생성
		_mBackBuffer = CreateCompatibleBitmap(_mHdc, _mWidth, _mHeight);

		// 새로 생성한 비트맵을 가리키는 DC 생성
		_mBackHdc = CreateCompatibleDC(_mHdc);

		// 새로 생성한 비트맵과 DC를 서로 연결
		HBITMAP defalutBitmap
			= (HBITMAP)SelectObject(_mBackHdc, _mBackBuffer);
		DeleteObject(defalutBitmap);

		TimeMgr::Initialize();
		SoundMgr::Initialize();
		Input::Initialize();
		Camera::Initialize();

		CollisionMgr::Initialize();
		SceneMgr::Initialize();
	}

	void Application::Run()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		TimeMgr::Update();
		Input::Update();
		Camera::Update();

		CollisionMgr::Update();
		SceneMgr::Update();
	}

	void Application::Render()
	{
		TimeMgr::Render(_mBackHdc);

		HBRUSH brush = CreateSolidBrush(RGB(21, 22, 26)); // 17 8 3
		HBRUSH oldBrush = (HBRUSH)SelectObject(_mBackHdc, brush);
		Rectangle(_mBackHdc, -1, -1, _mWidth + 1, _mHeight + 1);
		SelectObject(_mBackHdc, oldBrush);
		DeleteObject(brush);

		CollisionMgr::Render(_mBackHdc);
		SceneMgr::Render(_mBackHdc);

		BitBlt(_mHdc, 0, 0, _mWidth, _mHeight
			, _mBackHdc, 0, 0, SRCCOPY);
	}

	void Application::Release()
	{

	}
}

