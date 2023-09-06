#pragma once
#include "skGameObject.h"

namespace sk
{
	class ExecutionCollider : public GameObject
	{
	public:
		ExecutionCollider();
		virtual ~ExecutionCollider();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Death();

	private:
	};
}

