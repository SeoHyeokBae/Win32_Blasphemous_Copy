#pragma once
#include "skGameObject.h"

namespace sk
{
	class Portal : public GameObject
	{
	public:
		Portal();
		virtual ~Portal();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		float _mTime;
	};
}

