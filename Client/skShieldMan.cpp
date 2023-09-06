#include "skShieldMan.h"
#include "skResources.h"
#include "skObject.h"
#include "skSlash.h"
#include "skTimeMgr.h"
#include "skPlayer.h"
#include "skMonsterAttack.h"	
#include "skSound.h"
#include "skInput.h"


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
		, _mbSturn(false)
		, _mbCanExecution(true)
		, _mExecutionCol(nullptr)
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

		_mMonsInfo = { 50,5 };

		Texture* Shieldman_Idle = Resources::Load<Texture>(L"shieldman_Idle", L"..\\Resources\\image\\shieldman_idle.bmp");
		Texture* Shieldman_Attack = Resources::Load<Texture>(L"shieldman_attack", L"..\\Resources\\image\\shieldman_attack.bmp");
		Texture* Shieldman_Move = Resources::Load<Texture>(L"shieldman_move", L"..\\Resources\\image\\shieldman_move.bmp");
		Texture* Shieldman_Dead = Resources::Load<Texture>(L"shieldman_dead", L"..\\Resources\\image\\shieldman_dead.bmp");
		Texture* Shieldman_Sturn = Resources::Load<Texture>(L"shieldman_sturn", L"..\\Resources\\image\\shieldman_sturn.bmp");
		Texture* Shieldman_Excution = Resources::Load<Texture>(L"shieldman_execution", L"..\\Resources\\image\\execution.bmp");

		_mAnimator->CreateAnimation(L"shieldman_Idle_Right", Shieldman_Idle, Vector2(0.0f, 0.0f), Vector2(79.5f, 65.0f), 12, Vector2(0.0f, 5.0f), 0.15f);
		_mAnimator->CreateAnimation(L"shieldman_Idle_Left", Shieldman_Idle, Vector2(0.0f, 65.0f), Vector2(79.5f, 65.0f), 12, Vector2(0.0f, 0.0f), 0.15f);
		_mAnimator->CreateAnimation(L"shieldman_Attack_Right", Shieldman_Attack, Vector2(0.0f, 0.0f), Vector2(120.0f, 90.0f), 10, Vector2(0.0f, -25.0f), 0.08f);
		_mAnimator->CreateAnimation(L"shieldman_Attack_Left", Shieldman_Attack, Vector2(0.0f, 90.0f), Vector2(120.0f, 90.0f), 10, Vector2(0.0f, -25.0f), 0.08f);
		_mAnimator->CreateAnimation(L"shieldman_Move_Right", Shieldman_Move, Vector2(0.0f, 0.0f), Vector2(70.0f, 70.0f), 11, Vector2(0.0f,-5.0f), 0.1f);
		_mAnimator->CreateAnimation(L"shieldman_Move_Left", Shieldman_Move, Vector2(0.0f, 70.0f), Vector2(70.0f, 70.0f), 11, Vector2(0.0f, -5.0f), 0.1f);
		_mAnimator->CreateAnimation(L"shieldman_dead_Right", Shieldman_Dead, Vector2(0.0f, 0.0f), Vector2(120.0f, 110.0f), 30, Vector2(-20.0f,-40.0f), 0.08f);
		_mAnimator->CreateAnimation(L"shieldman_dead_Left", Shieldman_Dead, Vector2(0.0f, 220.0f), Vector2(120.0f, 110.0f), 30, Vector2(20.0f, -40.0f), 0.08f);
		_mAnimator->CreateAnimation(L"shieldman_sturn_Right", Shieldman_Sturn, Vector2(0.0f, 0.0f), Vector2(60.0f, 60.0f), 22, Vector2(0.0f, 0.0f), 0.07f);
		_mAnimator->CreateAnimation(L"shieldman_sturn_Left", Shieldman_Sturn, Vector2(0.0f, 60.0f), Vector2(60.0f, 60.0f), 22, Vector2(0.0f, 0.0f), 0.07f);
		_mAnimator->CreateAnimation(L"shieldman_execution_Right", Shieldman_Excution, Vector2(0.0f, 0.0f), Vector2(215.0f, 120.0f), 48, Vector2(-22.0f, -18.0f), 0.07f);
		_mAnimator->CreateAnimation(L"shieldman_execution_Left", Shieldman_Excution, Vector2(0.0f, 120.0f), Vector2(215.0f, 120.0f), 48, Vector2(22.0f, -18.0f), 0.07f);
		_mAnimator->SetScale(Vector2(2.0f, 2.0f));

		Resources::Load<Sound>(L"SHIELD_ENEMY_DEATH", L"..\\Resources\\sound\\SHIELD_ENEMY_DEATH.wav");
		Resources::Load<Sound>(L"SHIELD_ENEMY_ATTACK", L"..\\Resources\\sound\\SHIELD_ENEMY_ATTACK.wav");
		Resources::Load<Sound>(L"SHIELD_ENEMY_HIT_SHIELD", L"..\\Resources\\sound\\SHIELD_ENEMY_HIT_SHIELD.wav");
		Resources::Load<Sound>(L"SHIELD_EXECUTION", L"..\\Resources\\sound\\SHIELD_MAIDEN_EXECUTION.wav");

		_mAnimator->PlayAnimation(L"shieldman_Idle_Left", true);

		_mCollider->SetSize(Vector2(90.0f, 80.0f));
		_mCollider->SetOffset(Vector2(15.0f, 22.0f));
	}
	void ShieldMan::Update()
	{
		GameObject::Update();

		_mPrvDir = _mDir;
		_mPrvState = _mCurState;

		if (_mMonsInfo.Hp <= 0 && _mCurState != eState::Execution)
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

	void ShieldMan::Sturn()
	{
		Vector2 pos = _mCollider->GetPosition();
		
		if (_mbCanExecution)
		{
			_mbCanExecution = false;
			_mExecutionCol = object::Instantiate<ExecutionCollider>(eLayerType::Npc, pos);
			_mGuideBotton = object::Instantiate<GuideBotton>(eLayerType::UI, Vector2(pos.x,pos.y-80.f));
		}

		_mMonsInfo.Hp = 1.f;
		_mDelay += TimeMgr::DeltaTime();
		if (_mDelay > 5.0f )
		{
			_mDelay = 0.f;
			_mExecutionCol->Death();
			_mGuideBotton->Death();
			_mbCanExecution = true;
			_mMonsInfo.Hp = 15.0f;
			_mCurState = eState::IDLE;
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			_mCurState = eState::Execution;
		}
	}
	void ShieldMan::Dead()
	{
		if (_mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	void ShieldMan::Execution()
	{
		_mGuideBotton->Death();

		if (_mAnimator->IsActiveAnimationComplete())
		{
			_mExecutionCol->Death();
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
		case sk::ShieldMan::eState::Sturn:
			Sturn();
			break;
		case sk::ShieldMan::eState::Dead:
			Dead();
			break;
		case sk::ShieldMan::eState::Execution:
			Execution();
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
			Resources::Find<Sound>(L"SHIELD_ENEMY_ATTACK")->Play(false);
			Resources::Find<Sound>(L"SHIELD_ENEMY_ATTACK")->SetVolume(20.f);
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"shieldman_Attack_Right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"shieldman_Attack_Left", false);
			break;
		case sk::ShieldMan::eState::Hit:
			break;
		case sk::ShieldMan::eState::Sturn:
			break;
		case sk::ShieldMan::eState::Dead:
			Resources::Find<Sound>(L"SHIELD_ENEMY_DEATH")->Play(false);
			Resources::Find<Sound>(L"SHIELD_ENEMY_DEATH")->SetVolume(20.f);
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"shieldman_dead_Right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"shieldman_dead_Left", false);
			break;
		case sk::ShieldMan::eState::Execution:
			Resources::Find<Sound>(L"SHIELD_EXECUTION")->Play(false);
			Resources::Find<Sound>(L"SHIELD_EXECUTION")->SetVolume(20.f);
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"shieldman_execution_Left", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"shieldman_execution_Right", false);
			break;
		}
	}



	void ShieldMan::OnCollisionEnter(Collider* other)
	{		
		Slash* slash1 = dynamic_cast<Slash*>(other->GetOwner());

		Transform* tr = nullptr;
		if (slash1 != nullptr)
		{
			Resources::Find<Sound>(L"SHIELD_ENEMY_HIT_SHIELD")->Play(false);
			Resources::Find<Sound>(L"SHIELD_ENEMY_HIT_SHIELD")->SetVolume(20.f);

			if (slash1->GetCounter())
			{
				_mDelay = 0.f;
				if ((_mDir == eDir::Right))
					_mAnimator->PlayAnimation(L"shieldman_sturn_Right", true);
				else if ((_mDir == eDir::Left))
					_mAnimator->PlayAnimation(L"shieldman_sturn_Left", true);
				_mCurState = eState::Sturn;
			}
		}

	}
	void ShieldMan::OnCollisionStay(Collider* other)
	{
	}
	void ShieldMan::OnCollisionExit(Collider* other)
	{

	}
}