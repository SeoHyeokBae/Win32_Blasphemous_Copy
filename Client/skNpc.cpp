#include "skNpc.h"
#include "skResources.h"
#include "skAnimator.h"
#include "skCollisionMgr.h"

namespace sk
{
	Npc::Npc()
	{
	}
	Npc::~Npc()
	{
	}
	void Npc::Initialize()
	{
	}
	void Npc::Update()
	{
		GameObject::Update();
	}
	void Npc::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Npc::OnCollisionEnter(Collider* other)
	{
	}
	void Npc::OnCollisionStay(Collider* other)
	{
	}
	void Npc::OnCollisionExit(Collider* other)
	{
	}
}