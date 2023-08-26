#pragma once
#include "skGameObject.h"

namespace sk
{
	class DownSpace : public GameObject
	{
	public:
		DownSpace();
		virtual ~DownSpace();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
	};
}