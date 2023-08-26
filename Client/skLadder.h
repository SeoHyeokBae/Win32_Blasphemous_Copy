#pragma once
#include "skGameObject.h"

namespace sk
{
	class Ladder : public GameObject
	{
	public:
		Ladder();
		virtual ~Ladder();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
	};
}