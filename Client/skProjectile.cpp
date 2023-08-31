#include "skProjectile.h"

namespace sk
{
	Projectile::Projectile()
	{
	}
	Projectile::~Projectile()
	{
	}
	void Projectile::Initialize()
	{
	}
	void Projectile::Update()
	{
		GameObject::Update();
	}
	void Projectile::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Projectile::OnCollisionEnter(Collider* other)
	{
	}
	void Projectile::OnCollisionStay(Collider* other)
	{
	}
	void Projectile::OnCollisionExit(Collider* other)
	{
	}
}