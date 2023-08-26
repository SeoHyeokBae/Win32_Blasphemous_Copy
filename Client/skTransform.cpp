#include "skTransform.h"
#include "skInput.h"
#include "skTimeMgr.h"

namespace sk
{
	Transform::Transform() :
		Component(eComponentType::Transform)
		, _mRotation(0.0f)
	{
	}
	Transform::~Transform()
	{
	}
	void Transform::Initialize()
	{
	}
	void Transform::Update()
	{
	}
	void Transform::Render(HDC hdc)
	{
	}
}
