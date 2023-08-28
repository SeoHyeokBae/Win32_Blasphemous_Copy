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
		, _mHitDmg(0)
		, _mMonsInfo{}
		, _mPrvState(eState::None)
		, _mPrvDir(eDir::None)
		, _mType(eMonsType::Pietat)
		, _mbCanAtt(true)
		, _mbDeadScene(true)
		, _mTargetPos(Vector2::Zero)
		, _mDestroyTime(0.f)
		, _mbCanDestroy(false)
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

		_mMonsInfo = { 150,5 };

		Texture* Pietat_onestep = Resources::Load<Texture>(L"Pietat_OneStep", L"..\\Resources\\image\\pietat_1step.bmp");
		Texture* Pietat_Idle = Resources::Load<Texture>(L"Pietat_Idle", L"..\\Resources\\image\\pietat_idle.bmp");
		Texture* Pietat_Slash = Resources::Load<Texture>(L"Pietat_Slash", L"..\\Resources\\image\\pietat_slash.bmp");
		Texture* Pietat_Stomp = Resources::Load<Texture>(L"Pietat_Stomp", L"..\\Resources\\image\\pietat_stomp.bmp");

		_mAnimator->CreateAnimation(L"Pietat_OneStep_Right", Pietat_onestep, Vector2(0.0f, 0.0f), Vector2(170.f, 240.f), 9, Vector2(0.0f, 30.f), 0.18f);
		_mAnimator->CreateAnimation(L"Pietat_OneStep_Left", Pietat_onestep, Vector2(0.0f, 240.0f), Vector2(170.f, 240.f), 9, Vector2(0.0f, 30.f), 0.18f);
		_mAnimator->CreateAnimation(L"Pietat_Idle_Right", Pietat_Idle, Vector2(0.0f, 0.0f), Vector2(145.f, 230.f), 13, Vector2(0.0f, 30.f), 0.18f);
		_mAnimator->CreateAnimation(L"Pietat_Idle_Left", Pietat_Idle, Vector2(0.0f, 230.0f), Vector2(145.f, 230.f), 13, Vector2(0.0f, 30.f), 0.18f);
		_mAnimator->CreateAnimation(L"Pietat_Slash_Right", Pietat_Slash, Vector2(0.0f, 0.0f), Vector2(350.f, 250.f), 52, Vector2(10.0f, 30.f), 0.11f);
		_mAnimator->CreateAnimation(L"Pietat_Slash_Left", Pietat_Slash, Vector2(0.0f, 250.0f), Vector2(350.f, 250.f), 52, Vector2(-35.0f, 30.f), 0.11f);
		_mAnimator->CreateAnimation(L"Pietat_Stomp_Right", Pietat_Stomp, Vector2(0.0f, 0.0f), Vector2(350.f, 250.f), 18, Vector2(0.0f, 30.f), 0.11f);
		_mAnimator->CreateAnimation(L"Pietat_Stomp_Left", Pietat_Stomp, Vector2(0.0f, 250.0f), Vector2(350.f, 250.f), 18, Vector2(0.0f, 30.f), 0.11f);
		_mAnimator->SetScale(Vector2(2.0f, 2.0f));

		//Resources::Load<Sound>(L"Elder_Attack", L"..\\Resources\\sound\\ELDER_BROTHER_ATTACK.wav");
		//Resources::Load<Sound>(L"ElderBGM", L"..\\Resources\\sound\\ElderBrother.wav");

		BossUI* UI = object::Instantiate<BossUI>(eLayerType::UI);


		_mAnimator->PlayAnimation(L"Pietat_OneStep_Left", false);

		_mCollider->SetSize(Vector2(150.0f, 350.0f));
		_mCollider->SetOffset(Vector2(0.0f, 50.f));
		//Resources::Find<Sound>(L"ElderBGM")->Play(true);
		//Resources::Find<Sound>(L"ElderBGM")->SetVolume(25.0f);
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
		if (_mAnimator->IsActiveAnimationComplete() && _mCurState != eState::Dead)
		{
			_mTargetPos = Player::GetPlayerPos();
			Vector2 Pos = _mTransform->GetPosition();
			if (_mTargetPos.x - Pos.x < 0)
				_mDir = eDir::Left;
			else if (_mTargetPos.x - Pos.x >= 0)
				_mDir = eDir::Right;
		}
	}

	void Pietat::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Pietat::Idle()
	{
		_mCurState = eState::Stomp;
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
		if (_mDir == eDir::Right)
		{
		}
		else
		{
		}
	}

	void Pietat::Stomp()
	{
		if (_mDir == eDir::Right)
		{
		}
		else
		{
		}
	}

	void Pietat::Ready() // 공격 대기
	{
		_mAttDelay += TimeMgr::DeltaTime();
		if (_mAttDelay > 1.0f)
		{
			_mbCanAtt = true;
			_mAttDelay = 0.0f;
		}
		if (_mbCanAtt)
		{
			_mbCanAtt = false;
			if (_mActionCount == 0)
			{
				_mActionCount = 1;
				_mCurState = eState::Attack;
			}
			else if (_mActionCount == 1)
			{
				_mActionCount = 0;
				//_mCurState = eState::Jump;
			}
		}
	}

	
	void Pietat::Attack()
	{
		//if (_mWaveEff == 0 && _mAnimator->GetActiveAnime()->GetIndex() == 17)
		//{
		//	_mWaveEff++;
		//	//Resources::Find<Sound>(L"Elder_Attack")->Play(false);

		//	Transform* tr = GetComponent<Transform>();
		//	Vector2 pos = tr->GetPosition();
		//	if (_mDir == eDir::Right)
		//	{
		//		MonsterAttack* att = object::Instantiate<MonsterAttack>(eLayerType::MonsAtt, Vector2(pos.x + 50.f, pos.y));
		//		att->SetMons(this);
		//		att->MonAttCollider();
		//	}
		//	else
		//	{
		//		MonsterAttack* att = object::Instantiate<MonsterAttack>(eLayerType::MonsAtt, Vector2(pos.x - 50.f, pos.y));
		//		att->SetMons(this);
		//		att->MonAttCollider();
		//	}
		//	Vector2 ColPos = _mCollider->GetPosition();
		//	if (_mDir == eDir::Right)
		//	{
		//		ElderWaveMgr* wave = object::Instantiate<ElderWaveMgr>(eLayerType::Monster);
		//		wave->SetPos(ColPos);
		//	}
		//	else
		//	{
		//		ElderWaveMgr* wave = object::Instantiate<ElderWaveMgr>(eLayerType::Monster);
		//		wave->SetPos(ColPos);
		//		wave->SetLeft(true);
		//	}
		//}

		//if (_mAnimator->IsActiveAnimationComplete())
		//{
		//	_mWaveEff = 0;
		//	_mCurState = eState::Ready;
		//}
	}
	void Pietat::Hit()
	{
	}
	void Pietat::Dead()
	{
		Resources::Find<Sound>(L"ElderBGM")->Stop(true);

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
			Slash();
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
		case sk::Pietat::eState::Ready:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"elderbrother_Idle_Right", true);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"elderbrother_Idle_Left", true);
			break;
		case sk::Pietat::eState::Attack:
		{
			// TODO
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"elderbrother_Attack_Right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"elderbrother_Attack_Left", false);
		}
		break;
		case sk::Pietat::eState::Hit:
			break;
		case sk::Pietat::eState::Dead:
		{
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"elderbrother_Dead_Right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"elderbrother_Dead_Left", false);
		}
		break;
		}
	}



	void Pietat::OnCollisionEnter(Collider* other)
	{
	}
	void Pietat::OnCollisionStay(Collider* other)
	{
	}
	void Pietat::OnCollisionExit(Collider* other)
	{
	}
}