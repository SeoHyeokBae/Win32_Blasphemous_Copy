#pragma once
#include "skComponent.h"

namespace sk
{
	using namespace math;
	class Collider : public Component
	{
	public:
		Collider();
		virtual ~Collider();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void OnCollisionEnter(Collider* other);
		void OnCollisionStay(Collider* other);
		void OnCollisionExit(Collider* other);

		Vector2 GetSize() { return _mSize; }
		void SetSize(Vector2 size) { _mSize = size; }
		Vector2 GetOffset() { return _mOffset; }
		void SetOffset(Vector2 offset) { _mOffset = offset; }
		Vector2 GetPosition() { return _mPosition; }
		UINT GetCollisionNumber() { return _mCollisionNumber; }

		void SetOnColColor(COLORREF color) { _mOnColColor = color; }

		void SetNotColColor(COLORREF color) { _mNotColColor = color; }

		void SetRotate(float rotate) { _mRotate = rotate; }
		float GetRotate() { return _mRotate; }

	private:
		static UINT _mCollisionCount;

		Vector2 _mSize;
		Vector2 _mOffset;
		Vector2 _mPosition;

		COLORREF _mOnColColor;
		COLORREF _mNotColColor;

		UINT _mCollisionNumber;
		float _mRotate;
		bool _mbIsCollision;
	};
}


