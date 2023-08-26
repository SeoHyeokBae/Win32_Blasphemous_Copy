#pragma once
#include "skGameObject.h"
#include "skPlayer.h"
#include "skMonster.h"

namespace sk
{
	class Collider;

	class Defend : public GameObject
	{
	public:
		Defend();
		virtual ~Defend();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		__forceinline void SetPlayer(Player* player)
		{
			_mPlayer = player;
			_mState = _mPlayer->GetState();
			_mAttState = _mPlayer->GetAttState();
		}
		__forceinline GameObject* GetOwner() { return _mPlayer; }
		void DefendCollider();

	private:
		Collider* _mCollider;
		GameObject* _mOwner;
		Player* _mPlayer;
		Monster* _mMonster;

		Player::eState _mState;
		Player::eAttState _mAttState;
		float _mTime;
		bool _mIsHit;
	};

}