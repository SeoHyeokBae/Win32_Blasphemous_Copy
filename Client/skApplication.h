#pragma once
#include "CommonInclude.h"

namespace sk
{
	using namespace math;
	class Application
	{
	public:
		Application();
		~Application();

		void Initialize(HWND hwnd);
		void Run();
		void Update();
		void Render();
		void Release();

		HWND GetHwnd() { return _mHwnd; }
		HDC GetHdc() { return _mHdc; }
		UINT GetWidth() {return _mWidth;}
		UINT GetHeight() {return _mHeight;}
		void SetExit(HRESULT result) { _mExit = result; }
		HRESULT GetExit() { return _mExit; }
		
	private:
		HWND _mHwnd;
		HDC _mHdc;
		UINT _mWidth;
		UINT _mHeight;

		HDC _mBackHdc;
		HBITMAP _mBackBuffer;

		HRESULT _mExit;
	};
}

