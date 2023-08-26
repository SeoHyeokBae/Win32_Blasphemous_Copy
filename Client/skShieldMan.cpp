#include "skShieldMan.h"
#include "skResources.h"
#include "skObject.h"
#include "skSlash.h"
#include "skTimeMgr.h"
#include "skPlayer.h"
#include "skMonsterAttack.h"	

namespace sk
{
	ShieldMan::ShieldMan()
		: _mAnimator(nullptr)
		, _mCollider(nullptr)
		, _mRigidbody(nullptr)
		, _mTransform(nullptr)
		, _mIsHit(false)
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
		, _mType(eMonsType::Shieldman)
	{
	}
	ShieldMan::~ShieldMan()
	{
	}
	void ShieldMan::Initialize()
	{
		_mAnimator = AddComponent<Animator>();
		_mRigidbody = AddComponent<Rigidbody>();
		_mCollider = AddComponent<Collider>();
		_mTransform = GetComponent<Transform>();

		_mMonsInfo = { 100,5 };

		Texture* Shieldman_Idle = Resources::Load<Texture>(L"shieldman_Idle", L"..\\Resources\\image\\shieldman_idle.bmp");
		Texture* Shieldman_Attack = Resources::Load<Texture>(L"shieldman_attack", L"..\\Resources\\image\\shieldman_attack.bmp");
		Texture* Shieldman_Move = Resources::Load<Texture>(L"shieldman_move", L"..\\Resources\\image\\shieldman_move.bmp");
		Texture* Shieldman_Dead = Resources::Load<Texture>(L"shieldman_dead", L"..\\Resources\\image\\shieldman_dead.bmp");

		_mAnimator->CreateAnimation(L"shieldman_Idle_Right", Shieldman_Idle, Vector2(0.0f, 0.0f), Vector2(79.5f, 65.0f), 12, Vector2(0.0f, 5.0f), 0.15f);
		_mAnimator->CreateAnimation(L"shieldman_Idle_Left", Shieldman_Idle, Vector2(0.0f, 65.0f), Vector2(79.5f, 65.0f), 12, Vector2(0.0f, 0.0f), 0.15f);
		_mAnimator->CreateAnimation(L"shieldman_Attack_Right", Shieldman_Attack, Vector2(0.0f, 0.0f), Vector2(120.0f, 90.0f), 10, Vector2(0.0f, -25.0f), 0.08f);
		_mAnimator->CreateAnimation(L"shieldman_Attack_Left", Shieldman_Attack, Vector2(0.0f, 90.0f), Vector2(120.0f, 90.0f), 10, Vector2(0.0f, -25.0f), 0.08f);
		_mAnimator->CreateAnimation(L"shieldman_Move_Right", Shieldman_Move, Vector2(0.0f, 0.0f), Vector2(70.0f, 70.0f), 11, Vector2(0.0f,-5.0f), 0.1f);
		_mAnimator->CreateAnimation(L"shieldman_Move_Left", Shieldman_Move, Vector2(0.0f, 70.0f), Vector2(70.0f, 70.0f), 11, Vector2(0.0f, -5.0f), 0.1f);
		_mAnimator->CreateAnimation(L"shieldman_dead_Right", Shieldman_Dead, Vector2(0.0f, 0.0f), Vector2(120.0f, 110.0f), 30, Vector2(-20.0f,-40.0f), 0.08f);
		_mAnimator->CreateAnimation(L"shieldman_dead_Left", Shieldman_Dead, Vector2(0.0f, 220.0f), Vector2(120.0f, 110.0f), 30, Vector2(20.0f, -40.0f), 0.08f);
		_mAnimator->SetScale(Vector2(2.0f, 2.0f));

		_mAnimator->PlayAnimation(L"shieldman_Idle_Left", true);

		_mCollider->SetSize(Vector2(90.0f, 80.0f));
		_mCollider->SetOffset(Vector2(15.0f, 22.0f));
	}
	void ShieldMan::Update()
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

		UpdateInfo();
		UpdateState();
		UpdateAnimation();
	}
	void ShieldMan::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void ShieldMan::Idle()
	{
		Vector2 velocity = _mRigidbody->GetVelocity();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		_mPlayerDistance = tr->GetPosition().x - Player::GetPlayerPos().x;

		if (fabs(_mPlayerDistance) < scale / 2 + 150.f)
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
	void ShieldMan::Ready()
	{
		_mAttDelay += TimeMgr::DeltaTime();
		if (_mAttDelay > 1.5f)
		{
			_mAttDelay = 0.0f;
			_mCurState = eState::Attack;
		}
	}
	void ShieldMan::Patrol()
	{
		Vector2 velocity = _mRigidbody->GetVelocity();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		_mPlayerDistance = tr->GetPosition().x - Player::GetPlayerPos().x;

		if (fabs(_mPlayerDistance) < scale / 2 + 100.f)
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
			velocity.x = 100.0f;
			_mRigidbody->SetVelocity(velocity);
		}
		else if (_mActionCount == 2)
		{
			_mDir = eDir::Left;
			velocity.x = -100.0f;
			_mRigidbody->SetVelocity(velocity);
		}

		_mTransform->SetPosition(pos);
	}
	void ShieldMan::Trace()
	{
		Vector2 velocity = _mRigidbody->GetVelocity();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		_mPlayerDistance = tr->GetPosition().x - Player::GetPlayerPos().x;

		if (_mPlayerDistance >= 0)
		{
			_mDir = eDir::Left;
			if (fabs(_mPlayerDistance) > scale / 2 + 70.f)
			{
				velocity.x = -100.0f;	
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
			if (fabs(_mPlayerDistance) > scale / 2 + 70.f)
			{
				velocity.x = +100.0f;
			}
			else
			{
				_mCurState = eState::Ready;
			}
			_mRigidbody->SetVelocity(velocity);
		}

		_mTransform->SetPosition(pos);
	}
	void ShieldMan::Attack()
	{
		if (_mAnimator->GetActiveAnime()->GetIndex() == 5)
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
	void ShieldMan::Hit()
	{
	}
	void ShieldMan::Dead()
	{
		if (_mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	void ShieldMan::UpdateInfo()
	{
		if (_mIsHit)
		{
			_mMonsInfo.Hp -= _mHitDmg;
			_mIsHit =false;
		}
	}

	void ShieldMan::UpdateState()
	{
		switch (_mCurState)
		{
		case sk::ShieldMan::eState::IDLE:
			Idle();
			break;
		case sk::ShieldMan::eState::Ready:
			Ready();
			break;
		case sk::ShieldMan::eState::Patrol:
			Patrol();
			break;
		case sk::ShieldMan::eState::Trace:
			Trace();
			break;
		case sk::ShieldMan::eState::Attack:
			Attack();
			break;
		case sk::ShieldMan::eState::Hit:
			Hit();
			break;
		case sk::ShieldMan::eState::Dead:
			Dead();
			break;
		}
	}

	void ShieldMan::UpdateAnimation()
	{
		if (_mPrvState == _mCurState  && _mPrvDir == _mDir)
		{
			return;
		}
		switch (_mCurState)
		{
		case sk::ShieldMan::eState::IDLE:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"shieldman_Idle_Right", true);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"shieldman_Idle_Left", true);
			break;
		case sk::ShieldMan::eState::Ready:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"shieldman_Idle_Right", true);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"shieldman_Idle_Left", true);
			break;
		case sk::ShieldMan::eState::Patrol:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"shieldman_Move_Right", true);
			else if ( (_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"shieldman_Move_Left", true);
			break;
		case sk::ShieldMan::eState::Trace:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"shieldman_Move_Right", true);
			else if ( (_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"shieldman_Move_Left", true);
			break;
		case sk::ShieldMan::eState::Attack:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"shieldman_Attack_Right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"shieldman_Attack_Left", false);
			break;
		case sk::ShieldMan::eState::Hit:
			break;
		case sk::ShieldMan::eState::Dead:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"shieldman_dead_Right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"shieldman_dead_Left", false);
			break;
		}
	}



	void ShieldMan::OnCollisionEnter(Collider* other)
	{		
		Slash* slash1 = dynamic_cast<Slash*>(other->GetOwner());

		Transform* tr = nullptr;
		if (slash1 != nullptr)
		{
			//if (!(_mIsHit))
			//{
			//	_mMonsInfo.Hp -= Player::GetInfo().Dmg;
			//	_mIsHit = true;
			//}
		}
	}
	void ShieldMan::OnCollisionStay(Collider* other)
	{
	}
	void ShieldMan::OnCollisionExit(Collider* other)
	{

	}
}