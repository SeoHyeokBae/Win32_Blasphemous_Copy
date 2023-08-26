#pragma once
#include "skEntity.h"

namespace sk
{
	using namespace enums;
	class Component : public Entity
	{
	public:
		Component(eComponentType type);
		virtual ~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void SetOwner(class GameObject* owner) { _mOwner = owner; }
		class GameObject* GetOwner() { return _mOwner; }



	private:
		const eComponentType _mType;
		class GameObject* _mOwner;
	};

}

