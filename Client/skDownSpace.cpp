#include "skDownSpace.h"
#include "skPlayer.h"
#include "skCollider.h"
#include "skRigidbody.h"
#include "skTransform.h"
#include "skSceneMgr.h"
#include "skTimeMgr.h"
#include "skCamera.h"
#include "skInput.h"

namespace sk
{
	DownSpace::DownSpace()
	{
	}
	DownSpace::~DownSpace()
	{
	}
	void DownSpace::Initialize()
	{
	}
	void DownSpace::Update()
	{
		GameObject::Update();
	}
	void DownSpace::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


	void DownSpace::OnCollisionEnter(Collider* other)
	{
	}
	void DownSpace::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		Transform* tr = nullptr;

		if (player != nullptr)
		{
			Transform* tr = player->GetComponent<Transform>();

			float len = fabs(other->GetPosition().x - this->GetComponent<Collider>()->GetPosition().x);
			float scale = fabs(other->GetSize().x / 2.0f + this->GetComponent<Collider>()->GetSize().x / 2.0f);

			if (len < scale)
			{
				player->SetCanDown(true);
			}
		}
	}
	void DownSpace::OnCollisionExit(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		player->SetCanDown(false);
	}
}