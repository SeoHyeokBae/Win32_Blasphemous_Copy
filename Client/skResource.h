#pragma once
#include "skEntity.h"

namespace sk
{
	class Resource : public Entity
	{
	public:
		Resource();
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;

		void SetPath(const std::wstring& path) { _mPath = path; }
		std::wstring& GetPath() { return _mPath; }

	private:
		std::wstring _mPath;
	};

}

