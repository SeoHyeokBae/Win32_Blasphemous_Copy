#include "skFloor.h"
#include "skPlayer.h"
#include "skCollider.h"
#include "skRigidbody.h"
#include "skTransform.h"
#include "skMonster.h"
#include "skInput.h"
#include "skStone.h"
#include "skProjectile.h"

namespace sk
{
	Floor::Floor()
		: _mbIgnore(false)
	{
	}
	Floor::~Floor()
	{
	}
	void Floor::Initialize()
	{
	}
	void Floor::Update()
	{
		GameObject::Update();
	}
	void Floor::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Floor::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Monster* monster = dynamic_cast<Monster*>(other->GetOwner());
		Projectile* projectile = dynamic_cast<Projectile*>(other->GetOwner());

		Transform* tr = nullptr;
		Rigidbody* rb = nullptr;

		if (player != nullptr)
		{
			Transform* tr = player->GetComponent<Transform>();
			Rigidbody* rb = player->GetComponent<Rigidbody>();

			float len = fabs(other->GetPosition().y - this->GetComponent<Collider>()->GetPosition().y);
			float scale = fabs(other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetSize().y / 2.0f);

			float leftlimit = this->GetComponent<Collider>()->GetPosition().x - this->GetComponent<Collider>()->GetSize().x / 2.0f;
			float rightlimit = this->GetComponent<Collider>()->GetPosition().x + this->GetComponent<Collider>()->GetSize().x / 2.0f;
			

			// 충돌체 옆으로 진입시
			if (leftlimit > tr->GetPosition().x || rightlimit < tr->GetPosition().x)
			{
				_mbIgnore = true;
			}
			else if (player->GetState() == Player::eState::JUMP || player->GetState() == Player::eState::RUN_JUMP)
			{
				_mbIgnore = true;
			}

			if (_mbIgnore)
			{
				return;
			}


			if (other->GetPosition().y > GetComponent<Collider>()->GetPosition().y)
			{
				if (len < scale)
				{
					Vector2 playerPos = tr->GetPosition();
					playerPos.y += (scale - len) - 1.f;
					tr->SetPosition(playerPos);
				}
			}
			else
			{
				if (len < scale)
				{
					Vector2 playerPos = tr->GetPosition();
					playerPos.y -= (scale - len) - 1.0f;
					tr->SetPosition(playerPos);
				}

				rb->SetGround(true);
			}

		}

		if (monster != nullptr)
		{
			 tr = monster->GetComponent<Transform>();
			 rb = monster->GetComponent<Rigidbody>();

			float len = fabs(other->GetPosition().y - this->GetComponent<Collider>()->GetPosition().y);
			float scale = fabs(other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetSize().y / 2.0f);
			float len_x = fabs(other->GetPosition().x - this->GetComponent<Collider>()->GetPosition().x);
			float scale_x = fabs(other->GetSize().x / 2.0f - this->GetComponent<Collider>()->GetSize().x / 2.0f);

			if (len < scale)
			{
				Vector2 monpos = tr->GetPosition();

				// 몬스터 x축 제한범위 바닥 안
				float leftlimit = this->GetComponent<Collider>()->GetPosition().x - this->GetComponent<Collider>()->GetSize().x / 2.0f + other->GetSize().x / 2.0f;
				float rightlimit = this->GetComponent<Collider>()->GetPosition().x + this->GetComponent<Collider>()->GetSize().x / 2.0f - other->GetSize().x / 2.0f;

				if (len_x < scale_x)
				{
					if (monster->GetDir() == eDir::Left)
					{
						monpos.x += (scale_x - len_x) + 1.0f;
					}
					else if (monster->GetDir() == eDir::Right)
					{
						monpos.x -= (scale - len) - 1.0f;
					}
				}
				//if (leftlimit > other->GetPosition().x )
				//{
				//	monpos.x += (leftlimit - other->GetPosition().x) + 1.0f;
				//}
				//else if (rightlimit < other->GetPosition().x)
				//{
				//	monpos.x -= ( other->GetPosition().x - rightlimit) - 1.0f;
				//}
				monpos.y -= (scale - len) - 1.0f;
				tr->SetPosition(monpos);
			}

			rb->SetGround(true);
		}

		if (projectile != nullptr)
		{
			Transform* tr = projectile->GetComponent<Transform>();
			Rigidbody* rb = projectile->GetComponent<Rigidbody>();

			float len = fabs(other->GetPosition().y - this->GetComponent<Collider>()->GetPosition().y);
			float scale = fabs(other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetSize().y / 2.0f);

			if (this->GetComponent<Collider>()->GetPosition().y < tr->GetPosition().y)
			{
				_mbIgnore = true;
			}

			if (_mbIgnore)
			{
				return;
			}

			if (len < scale)
			{
				Vector2 playerPos = tr->GetPosition();
				playerPos.y -= (scale - len) - 1.0f;
				tr->SetPosition(playerPos);
			}

			rb->SetGround(true);
		}

	}
	void Floor::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Projectile* projectile = dynamic_cast<Projectile*>(other->GetOwner());

		Transform* tr = nullptr;
		Rigidbody* rb = nullptr;

		if (player != nullptr)
		{
			Transform* tr = player->GetComponent<Transform>();
			Rigidbody* rb = player->GetComponent<Rigidbody>();

			float leftlimit = this->GetComponent<Collider>()->GetPosition().x - this->GetComponent<Collider>()->GetSize().x / 2.0f;
			float rightlimit = this->GetComponent<Collider>()->GetPosition().x + this->GetComponent<Collider>()->GetSize().x / 2.0f;

			if (leftlimit > tr->GetPosition().x || rightlimit < tr->GetPosition().x)
			{
				_mbIgnore = true;
			}
			if (player->GetState() == Player::eState::CLIMB) // 사다리
			{
				_mbIgnore = true;
			}
			else if (player->GetState() == Player::eState::CROUCH && Input::GetKeyDown(eKeyCode::Space)) // 아래점프
			{
				_mbIgnore = true;
			}
			if (_mbIgnore)
			{
				return;
			}
			
			float len = fabs(other->GetPosition().y - this->GetComponent<Collider>()->GetPosition().y);
			float scale = fabs(other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetSize().y / 2.0f);

			if (other->GetPosition().y > GetComponent<Collider>()->GetPosition().y)
			{
				if (len < scale)
				{
					Vector2 playerPos = tr->GetPosition();
					playerPos.y += (scale - len) - 1.f;
					tr->SetPosition(playerPos);
				}
			}

		}


		if (projectile != nullptr)
		{
			Transform* tr = projectile->GetComponent<Transform>();
			Rigidbody* rb = projectile->GetComponent<Rigidbody>();

			float len = fabs(other->GetPosition().y - this->GetComponent<Collider>()->GetPosition().y);
			float scale = fabs(other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetSize().y / 2.0f);

			if (this->GetComponent<Collider>()->GetPosition().y < tr->GetPosition().y)
			{
				_mbIgnore = true;
			}

			if (_mbIgnore)
			{
				return;
			}

			if (len < scale)
			{
				Vector2 playerPos = tr->GetPosition();
				playerPos.y -= (scale - len) - 1.0f;
				tr->SetPosition(playerPos);
			}

			rb->SetGround(true);
		}
	}
	void Floor::OnCollisionExit(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Rigidbody* rb = player->GetComponent<Rigidbody>();

			if (player->GetState() != Player::eState::CLIMB)
			{
				rb->SetGround(false);

				// 플레이어 낙하시
				if ((player->GetState() != Player::eState::JUMP) && (rb->GetVelocity().y >= 0))
				{
					player->SetState(Player::eState::FALL);
				}
			}
		}
		_mbIgnore = false;
	}
}