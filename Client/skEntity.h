#pragma once
#include "CommonInclude.h"

namespace sk
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void SetName(const std::wstring& name) { _mName = name; }
		std::wstring& GetName() { return _mName; }

	private:
		std::wstring _mName;
	};

}

