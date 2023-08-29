#include "skCollider.h"
#include "skTransform.h"
#include "skGameObject.h"
#include "skCamera.h"

namespace sk
{
	UINT Collider::_mCollisionCount = 0;

	Collider::Collider()
		: Component(eComponentType::Collider)
		, _mColliderType(eColliderType::Rectangle)
		, _mSize(Vector2::Zero)
		, _mOffset(Vector2::Zero)
		, _mCollisionNumber(-1)
		, _mbIsCollision(false)
		, _mOnColColor(RGB(255, 50, 50))
		, _mNotColColor(RGB(50, 255, 50))
		, _mRotate(1.0f)
		, _mRadius(0.f)
	{
		_mCollisionNumber = _mCollisionCount;
		_mCollisionCount++;
	}
	Collider::~Collider()
	{
	}
	void Collider::Initialize()
	{
	}
	void Collider::Update()
	{
	}
	void Collider::Render(HDC hdc)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		_mPosition = pos + _mOffset;

		pos.x -= _mSize.x / 2.0f;
		pos.y -= _mSize.y / 2.0f;
		pos.x += _mOffset.x;
		pos.y += _mOffset.y;

		pos = Camera::CalculatePosition(pos);

		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

		HPEN pen = NULL;
		if (_mbIsCollision)
		{
			pen = CreatePen(PS_SOLID, 2, _mOnColColor);
		}
		else
		{
			pen = CreatePen(PS_SOLID, 2, _mNotColColor);
		}

		HPEN oldPen = (HPEN)SelectObject(hdc, pen);

		if (_mColliderType == eColliderType::Rectangle)
		{
			Rectangle(hdc
				, pos.x, pos.y
				, pos.x + _mSize.x, pos.y + _mSize.y);
		}
		else if (_mColliderType == eColliderType::Elipse)
		{
			Ellipse(hdc
				, pos.x - _mRadius, pos.y - _mRadius
				, pos.x + _mRadius, pos.y + _mRadius);
		}

		
		
		SelectObject(hdc, oldBrush);
		DeleteObject(transparentBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(pen);
	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		_mbIsCollision = true;
		GetOwner()->OnCollisionEnter(other);
	}
	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}
	void Collider::OnCollisionExit(Collider* other)
	{
		_mbIsCollision = false;
		GetOwner()->OnCollisionExit(other);
	}
}