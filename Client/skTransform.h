#pragma once
#include "skComponent.h"

namespace sk
{
	using namespace math;
	class Transform : public Component
	{
	public:
		Transform();
		virtual ~Transform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
			
		void SetPosition(Vector2 pos) { _mPosition = pos; }
		Vector2 GetPosition() { return _mPosition; }
		float GetRotation() { return _mRotation; }

	private:
		Vector2 _mPosition;
		float _mRotation;
	};

}

