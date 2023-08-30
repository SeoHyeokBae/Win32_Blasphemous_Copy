#include "skStoner.h"
#include "skResources.h"
#include "skObject.h"
#include "skTimeMgr.h"
#include "skPlayer.h"
#include "skMonsterAttack.h"	
#include "skSlash.h"
#include "skStone.h"

namespace sk
{
	Stoner::Stoner()
		: _mAnimator(nullptr)
		, _mCollider(nullptr)
		, _mTransform(nullptr)
		, _mRigidBody(nullptr)
		, _mIsHit(false)
		, _mPlayerDistance(0.0f)
		, _mDelay(0.0f)
		, _mAttDelay(2.5f)
		, _mActionCount(0)
		/*, _mHitDmg(0)*/
		, _mMonsInfo{}
		, _mPrvState(eState::None)
		, _mCurState(eState::None)
		, _mPrvDir(eDir::None)
		, _mDir(eDir::Left)
		, _mType(eMonsType::Stoner)
		, _mTargetPos(Vector2::Zero)
		, _mStone(true)
		, _mCanRising(true)
	{
	}
	Stoner::~Stoner()
	{
	}
	void Stoner::Initialize()
	{
		_mAnimator = AddComponent<Animator>();
		_mCollider = AddComponent<Collider>();
		_mRigidBody = AddComponent<Rigidbody>();
		_mTransform = GetComponent<Transform>();

		_mMonsInfo = { 15,5 };

		Texture* Stoner_Rising = Resources::Load<Texture>(L"stoner_rising", L"..\\Resources\\image\\stoner\\stoner_rising.bmp");
		Texture* Stoner_Idle = Resources::Load<Texture>(L"stoner_idle", L"..\\Resources\\image\\stoner\\stoner_idle.bmp");
		Texture* Stoner_Turn = Resources::Load<Texture>(L"stoner_turn", L"..\\Resources\\image\\stoner\\stoner_turn.bmp");
		Texture* Stoner_Hurt = Resources::Load<Texture>(L"stoner_hurt", L"..\\Resources\\image\\stoner\\stoner_hurt.bmp");
		Texture* Stoner_Attack_Right = Resources::Load<Texture>(L"stoner_attack_right", L"..\\Resources\\image\\stoner\\stoner_attack_right.bmp");
		Texture* Stoner_Attack_Left = Resources::Load<Texture>(L"stoner_attack_left", L"..\\Resources\\image\\stoner\\stoner_attack_left.bmp");
		Texture* Stoner_Death = Resources::Load<Texture>(L"stoner_death", L"..\\Resources\\image\\stoner\\stoner_death.bmp");

		_mAnimator->CreateAnimation(L"Stoner_Rising", Stoner_Rising, Vector2(0.0f, 0.0f), Vector2(94.0f, 60.0f), 11, Vector2(0.0f, 0.0f), 0.1f);
		_mAnimator->CreateAnimation(L"Stoner_Idle_Right", Stoner_Idle, Vector2(0.0f, 0.0f), Vector2(94.0f, 60.0f), 12, Vector2(0.0f, -5.0f), 0.1f);
		_mAnimator->CreateAnimation(L"Stoner_Idle_Left", Stoner_Idle, Vector2(0.0f, 60.0f), Vector2(94.0f, 60.0f), 12, Vector2(0.0f, -5.0f), 0.1f);
		_mAnimator->CreateAnimation(L"Stoner_Turn_Right", Stoner_Turn, Vector2(0.0f, 0.0f), Vector2(94.0f, 60.0f), 7, Vector2(0.0f, -5.0f), 0.1f);
		_mAnimator->CreateAnimation(L"Stoner_Turn_Left", Stoner_Turn, Vector2(0.0f, 60.0f), Vector2(94.0f, 60.0f), 7, Vector2(0.0f, -5.0f), 0.1f);
		_mAnimator->CreateAnimation(L"Stoner_Hurt_Right", Stoner_Hurt, Vector2(0.0f, 0.0f), Vector2(94.0f, 60.0f), 6, Vector2(0.0f, -5.0f), 0.1f);
		_mAnimator->CreateAnimation(L"Stoner_Hurt_Left", Stoner_Hurt, Vector2(0.0f, 60.0f), Vector2(94.0f, 60.0f), 6, Vector2(0.0f, -5.0f), 0.1f);
		_mAnimator->CreateAnimation(L"Stoner_Attack_Right", Stoner_Attack_Right, Vector2(0.0f, 0.0f), Vector2(94.0f, 80.0f), 20, Vector2(0.0f, -26.0f), 0.07f);
		_mAnimator->CreateAnimation(L"Stoner_Attack_Left", Stoner_Attack_Left, Vector2(0.0f, 0.0f), Vector2(100.0f, 80.0f), 20, Vector2(-6.0f, -25.0f), 0.07f);
		_mAnimator->CreateAnimation(L"Stoner_Death_Right", Stoner_Death, Vector2(0.0f, 0.0f), Vector2(140.0f, 90.0f), 16, Vector2(0.0f, -39.0f), 0.06f);
		_mAnimator->CreateAnimation(L"Stoner_Death_Left", Stoner_Death, Vector2(0.0f, 90.0f), Vector2(140.0f, 90.0f), 16, Vector2(0.0f, -39.0f), 0.06f);
		_mAnimator->SetScale(Vector2(2.0f, 2.0f));

		_mCollider->SetSize(Vector2(150.0f, 90.0f));
	}
	void Stoner::Update()
	{
		GameObject::Update();

		_mPrvDir = _mDir;
		_mPrvState = _mCurState;

		_mTargetPos = Player::GetPlayerPos();
		if (_mCanRising && fabs(_mTransform->GetPosition().x - _mTargetPos.x) < 700.f)
		{
			_mCanRising = false;
			_mAnimator->PlayAnimation(L"Stoner_Rising", false);
			_mCurState = eState::Rising;
		}

		if (_mMonsInfo.Hp <= 0)
		{
			if (_mMonsInfo.Hp < 0)
			{
				_mMonsInfo.Hp = 0;
			}
			_mCurState = eState::Dead;
		}

		if (_mDir != _mPrvDir)
		{
			_mCurState = eState::Turn;
		}

		//UpdateInfo();
		ChangeOfDir();
		UpdateState();
		UpdateAnimation();
	}

	void Stoner::ChangeOfDir()
	{
		_mPrvDir = _mDir;
		if (_mCurState != eState::Dead)
		{
			_mTargetPos = Player::GetPlayerPos();
			Vector2 Pos = _mTransform->GetPosition();
			if (_mTargetPos.x - Pos.x < 0)
				_mDir = eDir::Left;
			else if (_mTargetPos.x - Pos.x >= 0)
				_mDir = eDir::Right;
		}
		if (_mDir != _mPrvDir)
		{
			_mCurState = eState::Turn;
		}
	}
	void Stoner::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Stoner::Idle()
	{
		_mAttDelay += TimeMgr::DeltaTime();
		if (_mAttDelay > 3.0f)
		{
			_mAttDelay = 0.f;
			_mCurState = eState::Attack;
		}
	}
	void Stoner::Ready()
	{
	}
	void Stoner::Turn()
	{
		if (_mAnimator->IsActiveAnimationComplete())
		{
			_mCurState = eState::IDLE;
		}
	}
	void Stoner::Rising()
	{
		if (_mAnimator->IsActiveAnimationComplete())
		{
			_mCurState = eState::IDLE;
		}
	}
	void Stoner::Attack()
	{
		Vector2 Pos = _mTransform->GetPosition();

		if (_mAnimator->GetActiveAnime()->GetIndex() == 16)
		{
			if (_mStone)
			{
				_mStone = false;
				Stone* stone = object::Instantiate<Stone>(eLayerType::Projectile, Vector2(Pos.x, Pos.y));
				stone->SetDir(_mDir);
				stone->SetTarget(_mTargetPos);
				stone->SetStartPos(Vector2(Pos.x, Pos.y));
			}
		}

		if (_mAnimator->IsActiveAnimationComplete())
		{
			_mStone = true;
			_mCurState = eState::IDLE;
		}
	}
	void Stoner::Hit()
	{
		_mAttDelay = 0.f;

		if (_mAnimator->IsActiveAnimationComplete())
		{
			_mCurState = eState::IDLE;
		}
	}
	void Stoner::Dead()
	{
		if (_mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	//void Stoner::UpdateInfo()
	//{
		//if (_mIsHit)
		//{
		//	_mMonsInfo.Hp -= _mHitDmg;
		//	_mIsHit = false;
		//}
	//}

	void Stoner::UpdateState()
	{
		switch (_mCurState)
		{
		case sk::Stoner::eState::IDLE:
			Idle();
			break;
		case sk::Stoner::eState::Ready:
			Ready();
			break;
		case sk::Stoner::eState::Turn:
			Turn();
			break;
		case sk::Stoner::eState::Rising:
			Rising();
			break;
		case sk::Stoner::eState::Attack:
			Attack();
			break;
		case sk::Stoner::eState::Hit:
			Hit();
			break;
		case sk::Stoner::eState::Dead:
			Dead();
			break;
		}
	}

	void Stoner::UpdateAnimation()
	{
		if (_mPrvState == _mCurState && _mPrvDir == _mDir)
		{
			return;
		}

		switch (_mCurState)
		{
		case sk::Stoner::eState::IDLE:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Stoner_Idle_Right", true);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Stoner_Idle_Left", true);
			break;
		case sk::Stoner::eState::Ready:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"shieldman_Idle_Right", true);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"shieldman_Idle_Left", true);
			break;
		case sk::Stoner::eState::Turn:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Stoner_Turn_Right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Stoner_Turn_Left", false);
			break;
		case sk::Stoner::eState::Rising:
			//_mAnimator->PlayAnimation(L"Stoner_Rising", false);
			break;
		case sk::Stoner::eState::Attack:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Stoner_Attack_Right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Stoner_Attack_Left", false);
			break;
		case sk::Stoner::eState::Hit:
			break;
		case sk::Stoner::eState::Dead:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Stoner_Death_Right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Stoner_Death_Left", false);
			break;
		}
	}

	void Stoner::OnCollisionEnter(Collider* other)
	{
		Slash *slash = dynamic_cast<Slash*>(other->GetOwner());

		if (slash != nullptr)
		{
			_mCurState = eState::Hit;
			if (_mDir == eDir::Right)
			{
				_mAnimator->PlayAnimation(L"Stoner_Hurt_Right", false);
			}
			else if (_mDir == eDir::Left)
			{
				_mAnimator->PlayAnimation(L"Stoner_Hurt_Left", false);

			}
		}
	}
	void Stoner::OnCollisionStay(Collider* other)
	{
	}
	void Stoner::OnCollisionExit(Collider* other)
	{

	}
}