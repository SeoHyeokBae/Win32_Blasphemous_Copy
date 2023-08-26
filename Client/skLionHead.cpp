#include "skLionHead.h"
#include "skResources.h"
#include "skObject.h"
#include "skSlash.h"
#include "skTimeMgr.h"
#include "skPlayer.h"
#include "skMonsterAttack.h"	
#include "skPlayerHit.h"

namespace sk
{
	LionHead::LionHead()
		: _mAnimator(nullptr)
		, _mCollider(nullptr)
		, _mRigidbody(nullptr)
		, _mTransform(nullptr)
		, _mPlayerDistance(0.0f)
		, _mDelay(0.0f)
		, _mAttDelay(0.0f)
		, _mActionCount(0)
		, _mHitDmg(0)
		, _mMonsInfo{}
		, _mPrvState(eState::None)
		, _mCurState(eState::IDLE)
		, _mPrvDir(eDir::None)
		, _mDir(eDir::Left)
		, _mType(eMonsType::LionHead)
		, _mbCanAtt(true)
	{
	}
	LionHead::~LionHead()
	{
	}
	void LionHead::Initialize()
	{
		_mAnimator = AddComponent<Animator>();
		_mRigidbody = AddComponent<Rigidbody>();
		_mCollider = AddComponent<Collider>();
		_mTransform = GetComponent<Transform>();

		_mMonsInfo = { 20,5 };

		Texture* LionHead_Idle = Resources::Load<Texture>(L"lionhead_Idle", L"..\\Resources\\image\\lionhead_idle.bmp");
		Texture* LionHead_Attack = Resources::Load<Texture>(L"lionhead_Attack", L"..\\Resources\\image\\lionhead_attack.bmp");
		Texture* LionHead_Move = Resources::Load<Texture>(L"lionhead_Move", L"..\\Resources\\image\\lionhead_move.bmp");
		Texture* LionHead_Dead = Resources::Load<Texture>(L"lionhead_Dead", L"..\\Resources\\image\\lionhead_dead.bmp");

		_mAnimator->CreateAnimation(L"lionhead_Idle_right", LionHead_Idle, Vector2(0.0f, 0.0f), Vector2(100.f, 120.f), 10, Vector2(0.0f, 15.0f), 0.15f);
		_mAnimator->CreateAnimation(L"lionhead_Idle_Left", LionHead_Idle, Vector2(0.0f, 120.0f), Vector2(100.f, 120.f), 10, Vector2(0.0f, 15.0f), 0.15f);
		_mAnimator->CreateAnimation(L"lionhead_Attack_Right", LionHead_Attack, Vector2(0.0f, 0.0f), Vector2(244.0f, 170.0f), 28, Vector2(100.0f, -20.0f), 0.07f);
		_mAnimator->CreateAnimation(L"lionhead_Attack_Left", LionHead_Attack, Vector2(0.0f, 170.0f), Vector2(244.0f, 170.0f), 28, Vector2(-100.0f, -20.0f), 0.07f);
		_mAnimator->CreateAnimation(L"lionhead_Move_Right", LionHead_Move, Vector2(0.0f, 0.0f), Vector2(120.0f, 120.0f), 10, Vector2(0.0f, 15.0f), 0.1f);
		_mAnimator->CreateAnimation(L"lionhead_Move_Left", LionHead_Move, Vector2(0.0f, 120.0f), Vector2(120.0f, 120.0f), 10, Vector2(0.0f, 15.0f), 0.1f);
		_mAnimator->CreateAnimation(L"lionhead_BackMove_Right", LionHead_Move, Vector2(0.0f, 360.0f), Vector2(120.0f, 120.0f), 10, Vector2(0.0f, 15.0f), 0.1f);
		_mAnimator->CreateAnimation(L"lionhead_BackMove_Left", LionHead_Move, Vector2(0.0f, 240.0f), Vector2(120.0f, 120.0f), 10, Vector2(0.0f, 15.0f), 0.1f);
		_mAnimator->CreateAnimation(L"lionhead_dead_Right", LionHead_Dead, Vector2(0.0f, 0.0f), Vector2(141.0f, 130.0f), 41, Vector2(0.0f, 15.0f), 0.1f);
		_mAnimator->CreateAnimation(L"lionhead_dead_Left", LionHead_Dead, Vector2(0.0f, 130.0f), Vector2(141.0f, 130.0f), 41, Vector2(0.0f, 15.0f), 0.1f);
		_mAnimator->SetScale(Vector2(2.0f, 2.0f));

		_mAnimator->PlayAnimation(L"lionhead_Idle_right", true);

		_mCollider->SetSize(Vector2(90.0f, 200.0f));
		_mCollider->SetOffset(Vector2(15.0f, 22.0f));
	}
	void LionHead::Update()
	{
		GameObject::Update();

		_mPrvDir = _mDir;
		_mPrvState = _mCurState;

		if (_mMonsInfo.Hp <= 0)
		{
			if (_mMonsInfo.Hp < 0)
			{
				_mMonsInfo.Hp = 0;
			}
			_mCurState = eState::Dead;
		}

		UpdateState();
		UpdateAnimation();
	}
	void LionHead::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void LionHead::Idle()
	{
		Vector2 velocity = _mRigidbody->GetVelocity();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		_mPlayerDistance = tr->GetPosition().x - Player::GetPlayerPos().x;

		if (fabs(_mPlayerDistance) < scale / 2 + 300.f && (Player::GetPlayerPos().y + 90.f >= _mCollider->GetPosition().y - 100.f))
		{
			_mCurState = eState::Trace;
		}

		_mDelay += TimeMgr::DeltaTime();
		if (_mDelay > 4.0f)
		{
			_mDelay = 0.f;
			_mActionCount++;
			_mCurState = eState::Patrol;
		}
	}
	void LionHead::Ready()
	{
		_mAttDelay += TimeMgr::DeltaTime();
		if (_mAttDelay > 1.5f)
		{
			_mbCanAtt = true;
			_mAttDelay = 0.0f;
		}
		if (_mbCanAtt)
		{
			_mbCanAtt = false;
			_mCurState = eState::Attack;
		}
	}
	void LionHead::Patrol()
	{
		Vector2 velocity = _mRigidbody->GetVelocity();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		_mPlayerDistance = tr->GetPosition().x - Player::GetPlayerPos().x;

		if (fabs(_mPlayerDistance) < scale / 2 + 300.f && (Player::GetPlayerPos().y + 90.f >= _mCollider->GetPosition().y - 100.f))
		{
			_mDelay = 0.f;
			_mCurState = eState::Trace;
		}

		_mDelay += TimeMgr::DeltaTime();
		if (_mDelay > 3.0f)
		{
			_mDelay = 0.f;
			if (_mActionCount == 2)
			{
				_mActionCount = 0;
			}
			_mCurState = eState::IDLE;
		}
		if (_mActionCount == 1)
		{
			_mDir = eDir::Right;
			velocity.x = 120.0f;
			_mRigidbody->SetVelocity(velocity);
		}
		else if (_mActionCount == 2)
		{
			_mDir = eDir::Left;
			velocity.x = -120.0f;
			_mRigidbody->SetVelocity(velocity);
		}

		_mTransform->SetPosition(pos);
	}
	void LionHead::Trace()
	{
		Vector2 velocity = _mRigidbody->GetVelocity();
		Transform* tr = GetComponent<Transform>();
		_mPlayerDistance = tr->GetPosition().x - Player::GetPlayerPos().x;

		if (_mPlayerDistance >= 0)
		{
			_mDir = eDir::Left;
			if (fabs(_mPlayerDistance) < scale / 2 + 125.f && (Player::GetPlayerPos().y + 90.f >= _mCollider->GetPosition().y - 100.f))
			{
				_mCurState = eState::BackMove;
			}
			else if (fabs(_mPlayerDistance) > scale / 2 + 175.f && (Player::GetPlayerPos().y + 90.f >= _mCollider->GetPosition().y - 100.f))
			{
				velocity.x = -120.0f;
			}
			else
			{
				_mCurState = eState::Ready;
			}
			_mRigidbody->SetVelocity(velocity);
		}
		else if (_mPlayerDistance < 0)
		{
			_mDir = eDir::Right;
			if (fabs(_mPlayerDistance) < scale / 2 + 125.f && (Player::GetPlayerPos().y + 90.f >= _mCollider->GetPosition().y - 100.f))
			{
				_mCurState = eState::BackMove;
			}
			else if (fabs(_mPlayerDistance) > scale / 2 + 175.f && (Player::GetPlayerPos().y + 90.f >= _mCollider->GetPosition().y - 100.f))
			{
				velocity.x = +120.0f;
			}
			else
			{
				_mCurState = eState::Ready;
			}
			_mRigidbody->SetVelocity(velocity);
		}
	}
	void LionHead::Attack()
	{
		if (_mAnimator->GetActiveAnime()->GetIndex() == 11)
		{
			Transform* tr = GetComponent<Transform>();
			MonsterAttack* att = object::Instantiate<MonsterAttack>(eLayerType::MonsAtt, tr->GetPosition());
			att->SetMons(this);
			att->MonAttCollider();
		}
		 
		if (_mAnimator->IsActiveAnimationComplete())
		{
			_mCurState = eState::IDLE;
		}

	}
	void LionHead::Hit()
	{
	}
	void LionHead::Dead()
	{
		if (_mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	void LionHead::BackMove()
	{
		Vector2 velocity = _mRigidbody->GetVelocity();
		Transform* tr = GetComponent<Transform>();
		_mPlayerDistance = tr->GetPosition().x - Player::GetPlayerPos().x;

		if (_mPlayerDistance >= 0)
		{
			_mDir = eDir::Left;
			if (fabs(_mPlayerDistance) <= scale / 2 + 175.f && fabs(_mPlayerDistance) >= scale / 2 + 125.f)
			{
				_mCurState = eState::Ready;
			}
			if (fabs(_mPlayerDistance) < scale / 2 + 125.f && (Player::GetPlayerPos().y + 90.f >= _mCollider->GetPosition().y - 100.f))
			{
				velocity.x = 120.0f;
			}
			
			_mRigidbody->SetVelocity(velocity);
		}
		else if (_mPlayerDistance < 0)
		{
			_mDir = eDir::Right;
			if (fabs(_mPlayerDistance) <= scale / 2 + 175.f && fabs(_mPlayerDistance) >= scale / 2 + 125.f)
			{
				_mCurState = eState::Ready;
			}
			if (fabs(_mPlayerDistance) < scale / 2 + 125.f)
			{
				velocity.x = -120.0f;
			}

			_mRigidbody->SetVelocity(velocity);
		}
	}
	void LionHead::UpdateState()
	{
		switch (_mCurState)
		{
		case sk::LionHead::eState::IDLE:
			Idle();
			break;
		case sk::LionHead::eState::Ready:
			Ready();
			break;
		case sk::LionHead::eState::Patrol:
			Patrol();
			break;
		case sk::LionHead::eState::Trace:
			Trace();
			break;
		case sk::LionHead::eState::Attack:
			Attack();
			break;
		case sk::LionHead::eState::Hit:
			Hit();
			break;
		case sk::LionHead::eState::BackMove:
			BackMove();
			break;
		case sk::LionHead::eState::Dead:
			Dead();
			break;
		}
	}

	void LionHead::UpdateAnimation()
	{
		if (_mPrvState == _mCurState && _mPrvDir == _mDir)
		{
			return;
		}
		switch (_mCurState)
		{
		case sk::LionHead::eState::IDLE:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"lionhead_Idle_right", true);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"lionhead_Idle_Left", true);
			break;
		case sk::LionHead::eState::Ready:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"lionhead_Idle_right", true);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"lionhead_Idle_Left", true);
			break;
		case sk::LionHead::eState::Patrol:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"lionhead_Move_Right", true);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"lionhead_Move_Left", true);
			break;
		case sk::LionHead::eState::Trace:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"lionhead_Move_Right", true);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"lionhead_Move_Left", true);
			break;
		case sk::LionHead::eState::Attack:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"lionhead_Attack_Right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"lionhead_Attack_Left", false);
			break;
		case sk::LionHead::eState::Hit:
			break;
		case sk::LionHead::eState::BackMove:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"lionhead_BackMove_Right", true);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"lionhead_BackMove_Left", true);			
			break;
		case sk::LionHead::eState::Dead:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"lionhead_dead_Right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"lionhead_dead_Left", false);
			break;
		}
	}



	void LionHead::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Rigidbody* player_rb = player->GetComponent<Rigidbody>();
			Vector2 velocity = player_rb->GetVelocity();
			Vector2 pos = player->GetComponent<Transform>()->GetPosition();
			Player::eState playerState = player->GetState();
			if (playerState != Player::eState::DODGE && playerState != Player::eState::HIT)
			{
				player->SetState(Player::eState::HIT);
				player_rb->SetGround(false);
				if (player->GetDir() == eDir::Right)
				{
					_mDir = eDir::Right;
					velocity.x = -350.0f;
					velocity.y = -350.0f;
					player_rb->SetVelocity(velocity);
					PlayerHit* phiteffect = object::Instantiate<PlayerHit>(eLayerType::Effect, pos);
					phiteffect->PlayAnimation(eDir::Right);
					player->GetComponent<Animator>()->PlayAnimation(L"PlayerHit_right", false);
				}
				else if (player->GetDir() == eDir::Left)
				{
					_mDir = eDir::Left;
					velocity.x = 350.0f;
					velocity.y = -350.0f;
					player_rb->SetVelocity(velocity);
					PlayerHit* phiteffect = object::Instantiate<PlayerHit>(eLayerType::Effect,pos);
					phiteffect->PlayAnimation(eDir::Left);
					player->GetComponent<Animator>()->PlayAnimation(L"PlayerHit_left", false);
				}
			}
		}

	}
	void LionHead::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Rigidbody* player_rb = player->GetComponent<Rigidbody>();
			Vector2 velocity = player_rb->GetVelocity();
			Vector2 pos = player->GetComponent<Transform>()->GetPosition();
			Player::eState playerState = player->GetState();
			if (playerState != Player::eState::DODGE && playerState != Player::eState::HIT)
			{
				player->SetState(Player::eState::HIT);
				player_rb->SetGround(false);
				if (player->GetDir() == eDir::Right)
				{
					_mDir = eDir::Right;
					velocity.x = -350.0f;
					velocity.y = -350.0f;
					player_rb->SetVelocity(velocity);
					PlayerHit* phiteffect = object::Instantiate<PlayerHit>(eLayerType::Effect, pos);
					phiteffect->PlayAnimation(eDir::Right);
					player->GetComponent<Animator>()->PlayAnimation(L"PlayerHit_right", false);
				}
				else if (player->GetDir() == eDir::Left)
				{
					_mDir = eDir::Left;
					velocity.x = 350.0f;
					velocity.y = -350.0f;
					player_rb->SetVelocity(velocity);
					PlayerHit* phiteffect = object::Instantiate<PlayerHit>(eLayerType::Effect, pos);
					phiteffect->PlayAnimation(eDir::Left);
					player->GetComponent<Animator>()->PlayAnimation(L"PlayerHit_left", false);
				}
			}
		}
	}
	void LionHead::OnCollisionExit(Collider* other)
	{

	}
}