#include "skComponent.h"

namespace sk
{
	Component::Component(eComponentType type) :
		_mType(type)
	{
	}
	Component::~Component()
	{
	}
	void Component::Initialize()
	{
	}
	void Component::Update()
	{
	}
	void Component::Render(HDC hdc)
	{
	}
}