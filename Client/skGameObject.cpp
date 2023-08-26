#include "skGameObject.h"
#include "skTransform.h"
#include "skSpriteRenderer.h"

sk::GameObject::GameObject()
{
	AddComponent<Transform>();
}

sk::GameObject::~GameObject()
{
	for (Component* comp : _mComponents)
	{
		delete comp;
		comp = nullptr;
	}
}

void sk::GameObject::Initialize()
{
}

void sk::GameObject::Update()
{
	for (Component* comp : _mComponents)
	{
		comp->Update();
	}
}

void sk::GameObject::Render(HDC hdc)
{
	for (Component* comp : _mComponents)
	{
		comp->Render(hdc);
	}
}

void sk::GameObject::OnCollisionEnter(Collider* other)
{
}

void sk::GameObject::OnCollisionStay(Collider* other)
{
}

void sk::GameObject::OnCollisionExit(Collider* other)
{
}
