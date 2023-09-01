#pragma once
#include "skGameObject.h"
#include "skPlayer.h"
#include "skMonster.h"

namespace sk
{
	class Collider;

	class Slash : public GameObject
	{
	public:
		Slash(Player* owner);
		Slash();
		virtual ~Slash();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		//__forceinline void SetPlayer(Player* player)
		//{
		//	_mPlayer = player;
		//	_mState = _mPlayer->GetState();
		//	_mAttState = _mPlayer->GetAttState();
		//}
		__forceinline GameObject* GetOwner() { return _mPlayer; }
		void SlashCollider();
		bool GetCounter() { return _mbCounter; }
		void IsHit();

	private:
		Collider* _mCollider;
		Player* _mPlayer;
		Monster* _mMonster;

		Player::eState _mState;
		Player::eAttState _mAttState;
		float _mTime;
		int _mIsHit;
		bool _mbCounter;
	};

}