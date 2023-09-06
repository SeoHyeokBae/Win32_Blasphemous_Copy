#include "skExecutionCollider.h"
#include "skPlayer.h"
#include "skInput.h"
#include "skCollisionMgr.h"
#include "skTransform.h"
#include "skShieldman.h"
#include "skCollider.h"

namespace sk
{
	ExecutionCollider::ExecutionCollider()
	{
	}
	ExecutionCollider::~ExecutionCollider()
	{
	}
	void ExecutionCollider::Initialize()
	{
		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(450.f, 80.f));
	}
	void ExecutionCollider::Update()
	{
		GameObject::Update();
	}
	void ExecutionCollider::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void ExecutionCollider::Death()
	{
		Destroy(this);
	}
	void ExecutionCollider::OnCollisionEnter(Collider* other)
	{

	}
	void ExecutionCollider::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player != nullptr)
		{
			Transform* tr = player->GetComponent<Transform>();

			float len = fabs(other->GetPosition().x - this->GetComponent<Collider>()->GetPosition().x);
			float scales = fabs(other->GetSize().x / 2.0f + this->GetComponent<Collider>()->GetSize().x / 2.0f);

			if (len < scales)
			{
				if (Input::GetKeyDown(eKeyCode::K))
				{
					player->Pause();
				}
			}
		}
	}
	void ExecutionCollider::OnCollisionExit(Collider* other)
	{
	}

}