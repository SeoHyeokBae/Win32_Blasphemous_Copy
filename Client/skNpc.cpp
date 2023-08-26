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
		Animator* ani = AddComponent<Animator>();
		Collider* col = AddComponent<Collider>();

		Texture* Deosgracias = Resources::Load<Texture>(L"Deosgracias", L"..\\Resources\\image\\Deosgracias_idle.bmp");
		ani->CreateAnimation(L"Deosgracias_idle", Deosgracias, Vector2(0.0f, 0.0f), Vector2(256.f, 512.f), 19, Vector2(0.0f, 0.0f), 0.1f);

		ani->PlayAnimation(L"Deosgracias_idle", true);


		col->SetSize(Vector2(400.0f, 200.0f));
		col->SetOffset(Vector2(0.0f, 75.0f));

		CollisionMgr::CollisionLayerCheck(eLayerType::Npc, eLayerType::Player, true);


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