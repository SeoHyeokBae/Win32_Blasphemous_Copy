#include "skPietat.h"
#include "skResources.h"
#include "skObject.h"
#include "skSlash.h"
#include "skTimeMgr.h"
#include "skPlayer.h"
#include "skMonsterAttack.h"	
#include "skCamera.h"
#include "skElderBroLandEff.h"
#include "skElderCorpseEff.h"
#include "skElderWaveMgr.h"
#include "skBossUI.h"
#include "skFirstBossScene.h"
#include "skBossClearScene.h"
#include "skSound.h"
#include "skInput.h"
#include "skThorn_Projectile.h"
#include "skThorn.h"
#include "skThornMgr.h"

namespace sk
{
	eDir Pietat::_mDir = eDir::Left;
	Pietat::eState Pietat::_mCurState = Pietat::eState::OneStep;

	Pietat::Pietat()
		: _mAnimator(nullptr)
		, _mCollider(nullptr)
		, _mRigidbody(nullptr)
		, _mTransform(nullptr)
		, _mPlayerDistance(0.0f)
		, _mDelay(0.0f)
		, _mAttDelay(0.0f)
		, _mActionCount(0)
		, _mCurActionCount(0)
		, _mHitDmg(0)
		, _mMonsInfo{}
		, _mPrvState(eState::None)
		, _mPrvDir(eDir::None)
		, _mType(eMonsType::Pietat)
		, _mbCanAtt(true)
		, _mbCanAtt2(false)
		, _mbDeadScene(true)
		, _mTargetPos(Vector2::Zero)
		, _mDestroyTime(0.f)
		, _mbCanDestroy(false)
		, _mbSplitloop(0)
		, _mbPhase2(false)
		, _mbWalk(false)
		, _mbEffect(true)
	{
	}
	Pietat::~Pietat()
	{
	}
	void Pietat::Initialize()
	{
		_mAnimator = AddComponent<Animator>();
		_mRigidbody = AddComponent<Rigidbody>();
		_mCollider = AddComponent<Collider>();
		_mTransform = GetComponent<Transform>();

		_mMonsInfo = { 20,5 };

		Texture* Pietat_onestep = Resources::Load<Texture>(L"Pietat_OneStep", L"..\\Resources\\image\\pietat\\pietat_1step.bmp");
		Texture* Pietat_Idle = Resources::Load<Texture>(L"Pietat_Idle", L"..\\Resources\\image\\pietat\\pietat_idle.bmp");
		Texture* Pietat_Slash = Resources::Load<Texture>(L"Pietat_Slash", L"..\\Resources\\image\\pietat\\pietat_slash.bmp");
		Texture* Pietat_Stomp = Resources::Load<Texture>(L"Pietat_Stomp", L"..\\Resources\\image\\pietat\\pietat_stomp.bmp");
		Texture* Pietat_Spit_Start = Resources::Load<Texture>(L"Pietat_Spit_Start", L"..\\Resources\\image\\pietat\\pietat_spit_start.bmp");
		Texture* Pietat_Spit_Loop = Resources::Load<Texture>(L"Pietat_Spit_Loop", L"..\\Resources\\image\\pietat\\pietat_spit_loop.bmp");
		Texture* Pietat_Spit_Back_To_Idle = Resources::Load<Texture>(L"Pietat_Spit_Back_To_Idle", L"..\\Resources\\image\\pietat\\pietat_spit_back_to_idle.bmp");
		Texture* Pietat_Turnarround = Resources::Load<Texture>(L"pietat_Turnarround", L"..\\Resources\\image\\pietat\\pietat_turnarround.bmp");
		Texture* Pietat_GroundSmash = Resources::Load<Texture>(L"pietat_GroundSmash", L"..\\Resources\\image\\pietat\\pietat_groundsmash2.bmp"); // pietat_groundsmash1 삭제
		Texture* Pietat_Smash2Idle = Resources::Load<Texture>(L"Pietat_Smash2Idle", L"..\\Resources\\image\\pietat\\pietat_smash_to_idle.bmp"); 
		Texture* Pietat_Smash2reverseIdle = Resources::Load<Texture>(L"Pietat_Smash2reverseIdle", L"..\\Resources\\image\\pietat\\pietat_smash_reverse.bmp"); 
		Texture* Pietat_Walk = Resources::Load<Texture>(L"Pietat_Walk", L"..\\Resources\\image\\pietat\\pietat_walk.bmp"); 

		_mAnimator->CreateAnimation(L"Pietat_OneStep_Right", Pietat_onestep, Vector2(0.0f, 0.0f), Vector2(170.f, 240.f), 9, Vector2(0.0f, 30.f), 0.13f);
		_mAnimator->CreateAnimation(L"Pietat_OneStep_Left", Pietat_onestep, Vector2(0.0f, 240.0f), Vector2(170.f, 240.f), 9, Vector2(0.0f, 30.f), 0.13f);
		_mAnimator->CreateAnimation(L"Pietat_Idle_Right", Pietat_Idle, Vector2(0.0f, 0.0f), Vector2(145.f, 230.f), 13, Vector2(0.0f, 30.f), 0.18f);
		_mAnimator->CreateAnimation(L"Pietat_Idle_Left", Pietat_Idle, Vector2(0.0f, 230.0f), Vector2(145.f, 230.f), 13, Vector2(0.0f, 30.f), 0.18f);
		_mAnimator->CreateAnimation(L"Pietat_Slash_Right", Pietat_Slash, Vector2(0.0f, 0.0f), Vector2(350.f, 250.f), 52, Vector2(23.0f, 12.f), 0.07f);
		_mAnimator->CreateAnimation(L"Pietat_Slash_Left", Pietat_Slash, Vector2(0.0f, 250.0f), Vector2(350.f, 250.f), 52, Vector2(-43.0f, 14.f), 0.07f);
		_mAnimator->CreateAnimation(L"Pietat_Stomp_Right", Pietat_Stomp, Vector2(0.0f, 0.0f), Vector2(350.f, 250.f), 18, Vector2(25.0f, 14.f), 0.1f);
		_mAnimator->CreateAnimation(L"Pietat_Stomp_Left", Pietat_Stomp, Vector2(0.0f, 250.0f), Vector2(350.f, 250.f), 18, Vector2(-25.0f, 13.f), 0.1f);
		_mAnimator->CreateAnimation(L"Pietat_Spit_Start_Right", Pietat_Spit_Start, Vector2(0.0f, 0.0f), Vector2(150.f, 250.f), 10, Vector2(4.0f, 8.f), 0.08f);
		_mAnimator->CreateAnimation(L"Pietat_Spit_Start_Left", Pietat_Spit_Start, Vector2(0.0f, 250.0f), Vector2(150.f, 250.f), 10, Vector2(-4.0f, 8.f), 0.08f);
		_mAnimator->CreateAnimation(L"Pietat_Spit_Loop_Right", Pietat_Spit_Loop, Vector2(0.0f, 0.0f), Vector2(150.f, 250.f), 15, Vector2(5.0f, 8.f), 0.1f);
		_mAnimator->CreateAnimation(L"Pietat_Spit_Loop_Left", Pietat_Spit_Loop, Vector2(0.0f, 250.0f), Vector2(150.f, 250.f), 15, Vector2(-5.0f, 8.f), 0.1f);
		_mAnimator->CreateAnimation(L"Pietat_Spit_Back_To_Idle_Right", Pietat_Spit_Back_To_Idle, Vector2(0.0f, 0.0f), Vector2(150.f, 250.f), 5, Vector2(5.0f, 8.f), 0.11f);
		_mAnimator->CreateAnimation(L"Pietat_Spit_Back_To_Idle_Left", Pietat_Spit_Back_To_Idle, Vector2(0.0f, 250.0f), Vector2(150.f, 250.f), 5, Vector2(-5.0f, 8.f), 0.11f);
		_mAnimator->CreateAnimation(L"Pietat_Turnarround_Right", Pietat_Turnarround, Vector2(0.0f, 250.0f), Vector2(160.f, 250.f), 13, Vector2(0.0f, 0.f), 0.1f);
		_mAnimator->CreateAnimation(L"Pietat_Turnarround_Left", Pietat_Turnarround, Vector2(0.0f, 250.0f), Vector2(160.f, 250.f), 13, Vector2(0.0f, 0.f), 0.1f);
		_mAnimator->CreateAnimation(L"Pietat_GroundSmash_Right", Pietat_GroundSmash, Vector2(0.0f, 0.0f), Vector2(400.f, 300.f), 41, Vector2(-32.0f, -15.f), 0.075f);
		_mAnimator->CreateAnimation(L"Pietat_GroundSmash_Left", Pietat_GroundSmash, Vector2(0.0f, 300.f), Vector2(400.f, 300.f), 41, Vector2(32.0f, -15.f), 0.075f);
		_mAnimator->CreateAnimation(L"Pietat_Smash2Idle_Right", Pietat_Smash2Idle, Vector2(0.0f, 0.0f), Vector2(160.f, 235.f), 9, Vector2(17.0f, 23.f), 0.09f);
		_mAnimator->CreateAnimation(L"Pietat_Smash2Idle_Left", Pietat_Smash2Idle, Vector2(0.0f, 235.f), Vector2(160.f, 235.f), 9, Vector2(-17.0f, 23.f), 0.09f);
		_mAnimator->CreateAnimation(L"Pietat_Smash2reverseIdle_Right", Pietat_Smash2reverseIdle, Vector2(0.0f, 0.0f), Vector2(180.f, 250.f), 9, Vector2(0.0f, 0.f), 0.11f);
		_mAnimator->CreateAnimation(L"Pietat_Smash2reverseIdle_Left", Pietat_Smash2reverseIdle, Vector2(0.0f, 250.f), Vector2(180.f, 250.f), 9, Vector2(0.0f, 0.f), 0.11f);

		_mAnimator->CreateAnimation(L"Pietat_Walk_Right", Pietat_Walk, Vector2(0.0f, 0.f), Vector2(190.f, 250.f), 15, Vector2(0.0f, 50.f), 0.1f);
		_mAnimator->CreateAnimation(L"Pietat_Walk_Left", Pietat_Walk, Vector2(0.0f, 250.0f), Vector2(190.f, 250.f), 15, Vector2(0.0f, 50.f), 0.1f);
		_mAnimator->SetScale(Vector2(2.0f, 2.0f));

		//Resources::Load<Sound>(L"Elder_Attack", L"..\\Resources\\sound\\ELDER_BROTHER_ATTACK.wav");
		//Resources::Load<Sound>(L"ElderBGM", L"..\\Resources\\sound\\ElderBrother.wav");

		BossUI* UI = object::Instantiate<BossUI>(eLayerType::UI);
		UI->SetBoss(this);

		_mAnimator->PlayAnimation(L"Pietat_OneStep_Left", false);

		_mCollider->SetSize(Vector2(150.0f, 350.0f));
		_mCollider->SetOffset(Vector2(0.0f, 50.f));
		//Resources::Find<Sound>(L"ElderBGM")->Play(true);
		//Resources::Find<Sound>(L"ElderBGM")->SetVolume(25.0f);
		srand(GetTickCount64());
	}

	void Pietat::Update()
	{
		GameObject::Update();

		if (_mbCanDestroy)
		{
			Destroy(this);
		}

		_mPrvDir = _mDir;
		_mPrvState = _mCurState;

		if (_mMonsInfo.Hp <= 10)
		{
			_mbPhase2 = true;
		}
		if (_mMonsInfo.Hp <= 0)
		{
			if (_mMonsInfo.Hp < 0)
			{
				_mMonsInfo.Hp = 0;
			}
			_mCurState = eState::Dead;
		}

		ChangeOfDir();
		UpdateState();
		UpdateAnimation();
	}
	void Pietat::ChangeOfDir()
	{
		if (_mAnimator->IsActiveAnimationComplete() && _mCurState != eState::Dead && _mCurState != eState::Split)
		{
			_mTargetPos = Player::GetPlayerPos();
			Vector2 Pos = _mTransform->GetPosition();
			if (_mTargetPos.x - Pos.x < 0)
			{
				_mDir = eDir::Left;
			}
			else if (_mTargetPos.x - Pos.x >= 0)
			{
				_mDir = eDir::Right;
			}
		}
	}

	void Pietat::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Pietat::Idle()
	{
		_mCurState = eState::Ready;
	}

	void Pietat::OneStep()
	{
		if (_mDir == eDir::Right)
		{
			Vector2 velocity = _mRigidbody->GetVelocity();
			velocity.x = 120.0f;
			_mRigidbody->SetVelocity(velocity);
		}
		else
		{
			Vector2 velocity = _mRigidbody->GetVelocity();
			velocity.x = -120.0f;
			_mRigidbody->SetVelocity(velocity);
		}

		if (_mAnimator->IsActiveAnimationComplete())
		{
			_mCurState = eState::IDLE;
		}
	}
	void Pietat::Slash()
	{

		if (_mAnimator->GetActiveAnime()->GetIndex() == 14 && _mbEffect)
		{
			_mbEffect = false;

			_mTransform = GetComponent<Transform>();
			Vector2 pos = _mTransform->GetPosition();
			if (_mDir == eDir::Right)
			{
				MonsterAttack* att = object::Instantiate<MonsterAttack>(eLayerType::MonsAtt, Vector2(pos.x + 230.f, pos.y));
				att->SetMons(this);
				att->MonAttCollider();
			}
			else
			{
				MonsterAttack* att = object::Instantiate<MonsterAttack>(eLayerType::MonsAtt, Vector2(pos.x - 230.f, pos.y));
				att->SetMons(this);
				att->MonAttCollider();
			}
		}


		if (_mAnimator->IsActiveAnimationComplete())
		{
			_mbEffect = true;
			_mCurState = eState::IDLE;
		}
	}

	void Pietat::Stomp()
	{
		if (_mAnimator->GetActiveAnime()->GetIndex() == 9 && _mbEffect) // 8
		{
			_mbEffect = false;

			_mTransform = GetComponent<Transform>();
			Vector2 pos = _mCollider->GetPosition();
			if (_mDir == eDir::Right)
			{
				MonsterAttack* att = object::Instantiate<MonsterAttack>(eLayerType::MonsAtt, Vector2(pos.x + 140.f, pos.y - 50.f));
				att->SetMons(this);
				att->MonAttCollider();

				ThornMgr* thorns = object::Instantiate<ThornMgr>(eLayerType::Effect);
				thorns->SetPos(Vector2(pos.x + 150.f, pos.y));
				thorns->SetAttType(ThornMgr::eAttType::Stomp);
				if (_mbPhase2)
					thorns->SetPhase2(true);
			}
			else
			{
				MonsterAttack* att = object::Instantiate<MonsterAttack>(eLayerType::MonsAtt, Vector2(pos.x - 140.f, pos.y - 50.f));
				att->SetMons(this);
				att->MonAttCollider();

				ThornMgr* thorns = object::Instantiate<ThornMgr>(eLayerType::Effect);
				thorns->SetPos(Vector2(pos.x - 150.f, pos.y));
				thorns->SetLeft(true);
				thorns->SetAttType(ThornMgr::eAttType::Stomp);
				if (_mbPhase2)
					thorns->SetPhase2(true);
			}
		}


		if (_mAnimator->IsActiveAnimationComplete())
		{
			_mbEffect = true;
			_mCurState = eState::IDLE;
		}
	}

	void Pietat::Split()
	{
		if (_mbSplitloop != 3 && _mAnimator->IsActiveAnimationComplete())
		{
			Vector2 Pos = _mTransform->GetPosition();
			if (!(_mbPhase2) && _mbSplitloop == 0)
			{
				Thorn_Projectile* thorn = object::Instantiate<Thorn_Projectile>(eLayerType::Projectile, Vector2(Pos.x, Pos.y));
				thorn->SetDir(_mDir);
				thorn->SetTarget(_mTargetPos);
				thorn->SetStartPos(Vector2(Pos.x, Pos.y - 100.f));
				
				_mbSplitloop = 3;
			}
			else if (_mbPhase2 && _mbSplitloop == 0 && _mAnimator->IsActiveAnimationComplete())
			{
				Thorn_Projectile* thorn = object::Instantiate<Thorn_Projectile>(eLayerType::Projectile, Vector2(Pos.x, Pos.y));
				thorn->SetDir(_mDir);
				thorn->SetTarget(_mTargetPos);
				thorn->SetStartPos(Pos);
				if (_mDir == eDir::Right)
					_mAnimator->PlayAnimation(L"Pietat_Spit_Loop_Right", false);
				else
					_mAnimator->PlayAnimation(L"Pietat_Spit_Loop_Left", false);

				_mbSplitloop = 1;
			}
			else if(_mbPhase2 && _mbSplitloop == 1 && _mAnimator->IsActiveAnimationComplete())
			{
				if (_mDir == eDir::Right)
				{
					Thorn_Projectile* thorn = object::Instantiate<Thorn_Projectile>(eLayerType::Projectile, Vector2(Pos.x, Pos.y));
					thorn->SetDir(_mDir);
					thorn->SetTarget(Vector2(_mTargetPos.x + 200.f, _mTargetPos.y));
					thorn->SetStartPos(Vector2(Pos.x, Pos.y - 100.f));
					_mAnimator->PlayAnimation(L"Pietat_Spit_Loop_Right", false);
				}
				else 
				{
					Thorn_Projectile* thorn = object::Instantiate<Thorn_Projectile>(eLayerType::Projectile, Vector2(Pos.x, Pos.y));
					thorn->SetDir(_mDir);
					thorn->SetTarget(Vector2(_mTargetPos.x - 200.f, _mTargetPos.y));
					thorn->SetStartPos(Vector2(Pos.x, Pos.y - 100.f));
					_mAnimator->PlayAnimation(L"Pietat_Spit_Loop_Left", false);
				}

				_mbSplitloop = 2;
			}
			else if (_mbPhase2 && _mbSplitloop == 2 && _mAnimator->IsActiveAnimationComplete())
			{
				if (_mDir == eDir::Right)
				{
					Thorn_Projectile* thorn = object::Instantiate<Thorn_Projectile>(eLayerType::Projectile, Vector2(Pos.x, Pos.y));
					thorn->SetDir(_mDir);
					thorn->SetTarget(Vector2(_mTargetPos.x + 80.f, _mTargetPos.y));
					thorn->SetStartPos(Vector2(Pos.x, Pos.y - 100.f));
					_mAnimator->PlayAnimation(L"Pietat_Spit_Loop_Right", false);

				}
				else
				{
					Thorn_Projectile* thorn = object::Instantiate<Thorn_Projectile>(eLayerType::Projectile, Vector2(Pos.x, Pos.y));
					thorn->SetDir(_mDir);
					thorn->SetTarget(Vector2(_mTargetPos.x - 80.f, _mTargetPos.y));
					thorn->SetStartPos(Vector2(Pos.x, Pos.y - 100.f));
					_mAnimator->PlayAnimation(L"Pietat_Spit_Loop_Left", false);

				}
				_mbSplitloop = 3;
			}
		}
	
		if (_mbSplitloop == 3 && _mAnimator->IsActiveAnimationComplete())
		{
			_mbSplitloop = 0;
			_mCurState = eState::SplitOff;
		}
	}

	void Pietat::SplitOff()
	{
		if (_mAnimator->IsActiveAnimationComplete())
		{
			_mCurState = eState::IDLE;
		}
	}

	void Pietat::Smash()
	{
		Vector2 ColPos = _mCollider->GetPosition();

		if (_mAnimator->GetActiveAnime()->GetIndex() == 28 && _mbEffect)
		{
			_mbEffect = false;
			MonsterAttack* att = object::Instantiate<MonsterAttack>(eLayerType::MonsAtt, Vector2(ColPos.x, ColPos.y));
			att->SetMons(this);
			att->MonAttCollider();

			ThornMgr* thorns_right = object::Instantiate<ThornMgr>(eLayerType::Effect);
			thorns_right->SetPos(Vector2(ColPos.x - 50.f, ColPos.y));
			thorns_right->SetAttType(ThornMgr::eAttType::Smash);
			if (_mbPhase2)
				thorns_right->SetPhase2(true);

			ThornMgr* thorns_left = object::Instantiate<ThornMgr>(eLayerType::Effect);
			thorns_left->SetPos(Vector2(ColPos.x + 50.f, ColPos.y));
			thorns_left->SetLeft(true);
			thorns_left->SetAttType(ThornMgr::eAttType::Smash);
			if (_mbPhase2)
				thorns_left->SetPhase2(true);

		}

		if (_mAnimator->IsActiveAnimationComplete())
		{
			_mCurState = eState::SmashOff;
		}
	}

	void Pietat::SmashOff()
	{
		if (_mAnimator->IsActiveAnimationComplete())
		{
			_mbEffect = true;
			_mCurState = eState::IDLE;
		}
	}

	void Pietat::Ready() // 공격 대기
	{
		_mTargetPos = Player::GetPlayerPos();
		Vector2 pos = _mTransform->GetPosition();

		_mActionCount = rand() % 4;
		if (!(_mbWalk))
		{
			_mAttDelay += TimeMgr::DeltaTime();
		}
		if (_mAttDelay > 1.0f && !(_mbWalk))
		{
			_mbCanAtt = true;
			_mAttDelay = 0.0f;
		}

		if (_mbCanAtt)
		{
			_mbCanAtt = false;

			if (_mActionCount== 0 || _mActionCount ==  1)
			{
				if (fabs(pos.x - _mTargetPos.x) > 350.f)
				{
					_mCurActionCount = _mActionCount;
					_mbWalk = true;
					_mbCanAtt2 = true;
					if ((_mDir == eDir::Right))
						_mAnimator->PlayAnimation(L"Pietat_Walk_Right", true);
					else if ((_mDir == eDir::Left))
						_mAnimator->PlayAnimation(L"Pietat_Walk_Left", true);
				}
				else
				{
					if (_mActionCount == 0)
						_mCurState = eState::Slash;
					else if (_mActionCount == 1)
						_mCurState = eState::Smash;
				}
			}
			else
			{
				if (_mActionCount == 2)
					_mCurState = eState::Split;
				else if (_mActionCount == 3)
					_mCurState = eState::Stomp;
			}
		}
		

		if (_mbWalk && _mbCanAtt2)
		{
			Vector2 velocity = _mRigidbody->GetVelocity();
			//_mTargetPos = Player::GetPlayerPos();
			Vector2 Pos = _mTransform->GetPosition();

			if (_mDir == eDir::Right)
				velocity.x = 150.f;
			else
				velocity.x = -150.f;

			_mRigidbody->SetVelocity(velocity);

			if (fabs(Pos.x - _mTargetPos.x) <= 300.f)
			{
				_mbWalk = false;
				_mbCanAtt2 = false;
				if (_mCurActionCount == 0)
					_mCurState = eState::Slash;
				else if (_mCurActionCount == 1)
					_mCurState = eState::Smash;
			}
		}
	}

	void Pietat::Attack()
	{
	}
	void Pietat::Hit()
	{
	}
	void Pietat::Turn()
	{
		if (_mAnimator->IsActiveAnimationComplete())
		{
			_mCurState = eState::IDLE;
		}
	}
	void Pietat::Dead()
	{
		//Resources::Find<Sound>(L"ElderBGM")->Stop(true);

		if (_mAnimator->IsActiveAnimationComplete())
		{
			if (_mbDeadScene)
			{
				_mbDeadScene = false;
				BossClearScene* ClearScene = object::Instantiate<BossClearScene>(eLayerType::ClearScene);
			}

			//_mDestroyTime += TimeMgr::DeltaTime();
			//if (_mDestroyTime >= 10.0f)
			//{
			//	Destroy(this);
			//}
		}
	}
	void Pietat::UpdateState()
	{
		switch (_mCurState)
		{
		case sk::Pietat::eState::IDLE:
			Idle();
			break;
		case sk::Pietat::eState::OneStep:
			OneStep();
			break;
		case sk::Pietat::eState::Slash:
			Slash();
			break;
		case sk::Pietat::eState::Stomp:
			Stomp();
			break;
		case sk::Pietat::eState::Split:
			Split();
			break;
		case sk::Pietat::eState::SplitOff:
			SplitOff();
			break;
		case sk::Pietat::eState::Smash:
			Smash();
			break;
		case sk::Pietat::eState::SmashOff:
			SmashOff();
			break;
		case sk::Pietat::eState::Ready:
			Ready();
			break;
		case sk::Pietat::eState::Attack:
			Attack();
			break;
		case sk::Pietat::eState::Hit:
			Hit();
			break;
		case sk::Pietat::eState::Turn:
			Turn();
			break;
		case sk::Pietat::eState::Dead:
			Dead();
			break;
		case sk::Pietat::eState::None:
			break;
		}
	}

	void Pietat::UpdateAnimation()
	{
		if (_mPrvState == _mCurState && _mPrvDir == _mDir)
		{
			return;
		}

		switch (_mCurState)
		{
		case sk::Pietat::eState::IDLE:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Pietat_Idle_Right", true);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Pietat_Idle_Left", true);
			break;
		case sk::Pietat::eState::Slash:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Pietat_Slash_Right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Pietat_Slash_Left", false);
			break;
		case sk::Pietat::eState::Stomp:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Pietat_Stomp_Right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Pietat_Stomp_Left", false);
			break;
		case sk::Pietat::eState::Split:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Pietat_Spit_Start_Right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Pietat_Spit_Start_Left", false);
			break;
		case sk::Pietat::eState::SplitOff:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Pietat_Spit_Back_To_Idle_Right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Pietat_Spit_Back_To_Idle_Left", false);
			break;
		case sk::Pietat::eState::Smash:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Pietat_GroundSmash_Right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Pietat_GroundSmash_Left", false);
			break;
		case sk::Pietat::eState::SmashOff:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Pietat_Smash2Idle_Right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Pietat_Smash2Idle_Left", false);
			break;
		case sk::Pietat::eState::Ready:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Pietat_Idle_Right", true);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Pietat_Idle_Left", true);
			break;
		case sk::Pietat::eState::Attack:
			break;
		case sk::Pietat::eState::Hit:
			break;
		case sk::Pietat::eState::Turn:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Pietat_Turnarround_Right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Pietat_Turnarround_Left", false);
			break;
		case sk::Pietat::eState::Dead:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"elderbrother_Dead_Right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"elderbrother_Dead_Left", false);
			break;
		}
	}



	void Pietat::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player != nullptr)
		{
			if (player->GetState() == Player::eState::DODGE)
			{
				return;
			}

			Transform* tr = player->GetComponent<Transform>();

			float len = fabs(other->GetPosition().x - this->GetComponent<Collider>()->GetPosition().x);
			float size = fabs(other->GetSize().x / 2.0f + this->GetComponent<Collider>()->GetSize().x / 2.0f);

			if (len < size - 50.0f)
			{
				Vector2 playerPos = tr->GetPosition();
				if (player->GetDir() == eDir::Right)
				{
					playerPos.x -= (size - 50.0f - len) + 1.1f;
				}
				else
				{
					playerPos.x += (size - 50.0f - len) + 1.1f;
				}
				tr->SetPosition(playerPos);
			}
		}
	}
	void Pietat::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player != nullptr)
		{
			if (player->GetState() == Player::eState::DODGE)
			{
				return;
			}
			
			Transform* tr = player->GetComponent<Transform>();

			float len = fabs(other->GetPosition().x - this->GetComponent<Collider>()->GetPosition().x);
			float size = fabs(other->GetSize().x / 2.0f + this->GetComponent<Collider>()->GetSize().x / 2.0f);

			if (len < size - 50.0f)
			{
				tr = player->GetComponent<Transform>();
				Vector2 playerPos = tr->GetPosition();
				if (player->GetDir() == eDir::Right)
				{
					playerPos.x -= (size - 50.0f - len) + 1.1f;
				}
				else if (player->GetDir() == eDir::Left)
				{
					playerPos.x += (size - 50.0f - len) + 1.1f;
				}
				tr->SetPosition(playerPos);
			}
		}
	}
	void Pietat::OnCollisionExit(Collider* other)
	{
	}
}