#include "skElderBrother.h"
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
	eDir ElderBrother::_mDir = eDir::Left;
	ElderBrother::eState ElderBrother::_mCurState = ElderBrother::eState::Fall;

	ElderBrother::ElderBrother()
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
		, _mType(eMonsType::ElderBrother)
		, _mbCanAtt(true)
		, _mbDeadScene(true)
		, _mJumpEff(0)
		, _mWaveEff(0)
		, _mTargetPos(Vector2::Zero)
		, _mDestroyTime(0.f)
		, _mbCanDestroy(false)
		,_mbSound(true)
	{
	}
	ElderBrother::~ElderBrother()
	{
	}
	void ElderBrother::Initialize()
	{
		_mAnimator = AddComponent<Animator>();
		_mRigidbody = AddComponent<Rigidbody>();
		_mCollider = AddComponent<Collider>();
		_mTransform = GetComponent<Transform>();

		_mMonsInfo = { 50,5 };

		Texture* ElderBrother_Idle = Resources::Load<Texture>(L"elderbrother_Idle", L"..\\Resources\\image\\elderbrother_idle.bmp");
		Texture* ElderBrother_Attack = Resources::Load<Texture>(L"elderbrother_Attack", L"..\\Resources\\image\\elderbrother_attack.bmp");
		Texture* ElderBrother_Move = Resources::Load<Texture>(L"elderbrother_Move", L"..\\Resources\\image\\elderbrother_move.bmp");
		Texture* ElderBrother_Jump = Resources::Load<Texture>(L"elderbrother_Jump", L"..\\Resources\\image\\elderbrother_jump.bmp");
		Texture* ElderBrother_JumpOff = Resources::Load<Texture>(L"elderbrother_JumpOff", L"..\\Resources\\image\\elderbrother_jumpOff.bmp");
		Texture* ElderBrother_Fall = Resources::Load<Texture>(L"elderbrother_Fall", L"..\\Resources\\image\\elderbrother_fall.bmp");
		Texture* ElderBrother_Dead = Resources::Load<Texture>(L"elderbrother_Dead", L"..\\Resources\\image\\elderbrother_dead1.bmp");

		_mAnimator->CreateAnimation(L"elderbrother_Idle_Right", ElderBrother_Idle, Vector2(0.0f, 0.0f), Vector2(170.f, 170.f), 10, Vector2(65.0f, -40.0f), 0.15f);
		_mAnimator->CreateAnimation(L"elderbrother_Idle_Left", ElderBrother_Idle, Vector2(0.0f, 170.0f), Vector2(170.f, 170.f), 10, Vector2(-65.0f, -40.0f), 0.15f);
		_mAnimator->CreateAnimation(L"elderbrother_Attack_Right", ElderBrother_Attack, Vector2(0.0f, 0.0f), Vector2(350.0f, 250.0f), 24, Vector2(150.0f, -100.0f), 0.08f);
		_mAnimator->CreateAnimation(L"elderbrother_Attack_Left", ElderBrother_Attack, Vector2(0.0f, 250.0f), Vector2(350.0f, 250.0f), 24, Vector2(-150.0f, -100.0f), 0.08f);
		_mAnimator->CreateAnimation(L"elderbrother_Move_Right", ElderBrother_Move, Vector2(0.0f, 0.0f), Vector2(120.0f, 120.0f), 10, Vector2(0.0f, 0.0f), 0.1f);
		_mAnimator->CreateAnimation(L"elderbrother_Move_Left", ElderBrother_Move, Vector2(0.0f, 120.0f), Vector2(120.0f, 120.0f), 10, Vector2(0.0f, 0.0f), 0.1f);
		_mAnimator->CreateAnimation(L"elderbrother_Jump_Right", ElderBrother_Jump, Vector2(0.0f, 0.0f), Vector2(225.0f, 210.0f), 11, Vector2(65.0f, -65.0f), 0.1f);
		_mAnimator->CreateAnimation(L"elderbrother_Jump_Left", ElderBrother_Jump, Vector2(0.0f, 210.0f), Vector2(225.0f, 210.0f), 11, Vector2(-65.0f, -65.0f), 0.1f);
		_mAnimator->CreateAnimation(L"elderbrother_JumpOff_Right", ElderBrother_JumpOff, Vector2(0.0f, 0.0f), Vector2(210.0f, 200.0f), 10, Vector2(65.0f, -65.0f), 0.08f);
		_mAnimator->CreateAnimation(L"elderbrother_JumpOff_Left", ElderBrother_JumpOff, Vector2(0.0f, 200.0f), Vector2(210.0f, 200.0f), 10, Vector2(-65.0f, -65.0f), 0.08f);
		_mAnimator->CreateAnimation(L"elderbrother_Fall_Right", ElderBrother_Fall, Vector2(0.0f, 0.0f), Vector2(210.0f, 200.0f), 1, Vector2(65.0f, -65.0f), 0.15f);
		_mAnimator->CreateAnimation(L"elderbrother_Fall_Left", ElderBrother_Fall, Vector2(0.0f, 200.0f), Vector2(210.0f, 200.0f), 1, Vector2(-65.0f, -65.0f), 0.15f);
		_mAnimator->CreateAnimation(L"elderbrother_Dead_Right", ElderBrother_Dead, Vector2(0.0f, 0.0f), Vector2(380.0f, 260.0f), 49, Vector2(-100.0f, -100.0f), 0.1f);
		_mAnimator->CreateAnimation(L"elderbrother_Dead_Left", ElderBrother_Dead, Vector2(0.0f, 260.0f), Vector2(380.0f, 260.0f), 49, Vector2(50.0f, -100.0f), 0.1f);
		_mAnimator->SetScale(Vector2(2.0f, 2.0f));

		Resources::Load<Sound>(L"Elder_Attack", L"..\\Resources\\sound\\ELDER_BROTHER_ATTACK.wav");
		Resources::Load<Sound>(L"ElderBGM", L"..\\Resources\\sound\\ElderBrother.wav");
		Resources::Load<Sound>(L"ELDER_BROTHER_LANDING", L"..\\Resources\\sound\\ELDER_BROTHER_LANDING.wav");
		Resources::Load<Sound>(L"ELDER_BROTHER_JUMP", L"..\\Resources\\sound\\ELDER_BROTHER_JUMP.wav");
		Resources::Load<Sound>(L"ELDER_BROTHER_ATTACK_VOICE", L"..\\Resources\\sound\\ELDER_BROTHER_ATTACK_VOICE.wav");
		Resources::Load<Sound>(L"ELDER_BROTHER_DEATH", L"..\\Resources\\sound\\ELDER_BROTHER_DEATH.wav");
		Resources::Load<Sound>(L"ELDER_BROTHER_DEATH_VOICE_2", L"..\\Resources\\sound\\ELDER_BROTHER_DEATH_VOICE_2.wav");

		BossUI* UI = object::Instantiate<BossUI>(eLayerType::UI);
		UI->SetBoss(this);


		_mAnimator->PlayAnimation(L"elderbrother_Fall_Left", false);

		_mCollider->SetSize(Vector2(150.0f, 225.0f));
		//_mCollider->SetOffset(Vector2(15.0f, 122.0f));
		_mRigidbody->SetGravity(Vector2(0.f, 7000.0f));
		_mRigidbody->SetLimitedX(1500.0f);

		Resources::Find<Sound>(L"ElderBGM")->Play(true);
		Resources::Find<Sound>(L"ElderBGM")->SetVolume(10.0f);
	}

	void ElderBrother::Update()
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

		PixelCollision();
		ChangeOfDir();
		UpdateState();
		UpdateAnimation();
	}
	void ElderBrother::ChangeOfDir()
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
	void ElderBrother::PixelCollision()
	{
		Transform* tr = GetComponent<Transform>();
		if (_mFloorTexture != nullptr)
		{
			Vector2 ColPos = _mCollider->GetPosition();
			Vector2 ColSize = _mCollider->GetSize();

			Vector2 Right = Vector2(ColPos.x + (ColSize.x / 2.0f), ColPos.y);
			Vector2 Left = Vector2(ColPos.x - (ColSize.x / 2.0f), ColPos.y);
			Vector2 Bottom = Vector2(ColPos.x, ColPos.y + (ColSize.y / 2.0f));

			COLORREF RightColor = _mFloorTexture->GetTexturePixel((int)Right.x, (int)Right.y);
			COLORREF RightBttomColor = _mFloorTexture->GetTexturePixel((int)Bottom.x + 1, (int)Bottom.y - 1);
			COLORREF LeftColor = _mFloorTexture->GetTexturePixel((int)Left.x, (int)Left.y);
			COLORREF LeftBttomColor = _mFloorTexture->GetTexturePixel((int)Bottom.x - 1, (int)Bottom.y - 1);
			COLORREF BottomColor = _mFloorTexture->GetTexturePixel((int)Bottom.x, (int)Bottom.y+1);

			Rigidbody* rb = GetComponent<Rigidbody>();

			if (BottomColor == RGB(255, 0, 255))
			{
				if (!(_mCurState == eState::Jump))
				{
					Vector2 pos = tr->GetPosition();
					//pos.y -= 1;
					tr->SetPosition(pos);

					_mRigidbody->SetGround(true);
				}
			}

			if (!(BottomColor == RGB(255, 0, 255)))
			{
				_mRigidbody->SetGround(false);
			}

			if (RightBttomColor == RGB(255, 0, 255))
			{
				Vector2 pos = tr->GetPosition();
				pos.y -= 1;
				tr->SetPosition(pos);

			}
			if (LeftBttomColor == RGB(255, 0, 255))
			{
				Vector2 pos = tr->GetPosition();
				pos.y -= 1;
				tr->SetPosition(pos);
			}

		}
	}

	void ElderBrother::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void ElderBrother::Idle()
	{

	}
	void ElderBrother::Ready() // 공격 대기
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
				_mCurState = eState::Jump;
			}
		}
	}

	void ElderBrother::Jump()
	{
		if ((!(_mRigidbody->GetGround()) && _mRigidbody->GetVelocity().y >= 0))
		{
			_mCurState = eState::Fall;
		}

		_mTargetPos = Player::GetPlayerPos();
		if (_mAnimator->GetActiveAnime()->GetIndex() == 9)
		{
			if (_mJumpEff==0)
			{
				_mJumpEff++;
				Vector2 ColPos = _mCollider->GetPosition();
				Vector2 ColSize = _mCollider->GetSize();
				ElderBroLandEff* landeffect = object::Instantiate<ElderBroLandEff>(eLayerType::Effect, Vector2(ColPos.x, ColPos.y));
			}

			//_mDir = eDir::Right;
			_mRigidbody->SetGround(false);
			Vector2  pos  = _mTransform->GetPosition();
			Vector2 velocity = _mRigidbody->GetVelocity();
			velocity.y = -2500.0f;
			if (_mDir == eDir::Right)
			{
				velocity.x = (fabs(_mTargetPos.x - pos.x) + 100.f);
			}
			else if (_mDir == eDir::Left)
			{
				velocity.x = -(fabs(_mTargetPos.x - pos.x) + 100.f);
			}
			_mRigidbody->SetVelocity(velocity);
		}
	}
	void ElderBrother::JumpOff()
	{
		Vector2 prvpos = Camera::GetLookPos();
		//Camera::SetLookPos(Vector2(prvpos.x + 20.f, prvpos.y + 20.f));

		if (_mAnimator->IsActiveAnimationComplete())
		{
			_mCurState = eState::Ready;
		}
	}
	void ElderBrother::Fall()
	{
		_mJumpEff = 0;
		Vector2  pos = _mTransform->GetPosition();
		Vector2 velocity = _mRigidbody->GetVelocity();
		if (_mDir == eDir::Right)
		{
			velocity.x = (fabs(_mTargetPos.x - pos.x) + 100.f);
		}
		else if (_mDir == eDir::Left)
		{
			velocity.x = -(fabs(_mTargetPos.x - pos.x) + 100.f);
		}
		_mRigidbody->SetVelocity(velocity);

		if (_mRigidbody->GetGround())
		{
			_mCurState = eState::JumpOff;
		}
	}
	void ElderBrother::Attack()
	{
		if (_mWaveEff == 0 && _mAnimator->GetActiveAnime()->GetIndex()== 17)
		{
			Resources::Find<Sound>(L"Elder_Attack")->Play(false);
			_mWaveEff++;

			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			if (_mDir == eDir::Right)
			{
				MonsterAttack* att = object::Instantiate<MonsterAttack>(eLayerType::MonsAtt, Vector2(pos.x + 50.f, pos.y));
				att->SetMons(this);
				att->MonAttCollider();
			}
			else
			{
				MonsterAttack* att = object::Instantiate<MonsterAttack>(eLayerType::MonsAtt, Vector2(pos.x - 50.f, pos.y));
				att->SetMons(this);
				att->MonAttCollider();
			}
			Vector2 ColPos = _mCollider->GetPosition();
			if (_mDir == eDir::Right)
			{
				ElderWaveMgr* wave = object::Instantiate<ElderWaveMgr>(eLayerType::Monster);
				wave->SetPos(ColPos);
			}
			else
			{
				ElderWaveMgr* wave = object::Instantiate<ElderWaveMgr>(eLayerType::Monster);
				wave->SetPos(ColPos);
				wave->SetLeft(true);
			}
		}

		if ( _mbSound && _mAnimator->GetActiveAnime()->GetIndex() == 19)
		{
			_mbSound = false;
			Resources::Find<Sound>(L"ELDER_BROTHER_ATTACK_HIT")->Play(false);
		}

		if (_mAnimator->IsActiveAnimationComplete())
		{
			_mbSound = true;
			_mWaveEff = 0;
			_mCurState = eState::Ready;
		}
	}
	void ElderBrother::Hit()
	{
	}
	void ElderBrother::Dead()
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
	void ElderBrother::UpdateState()
	{
		switch (_mCurState)
		{
		case sk::ElderBrother::eState::IDLE:
			Idle();
			break;
		case sk::ElderBrother::eState::Ready:
			Ready();
			break;
		case sk::ElderBrother::eState::Attack:
			Attack();
			break;
		case sk::ElderBrother::eState::Jump:
			Jump();
			break;
		case sk::ElderBrother::eState::JumpOff:
			JumpOff();
			break;
		case sk::ElderBrother::eState::Fall:
			Fall();
			break;
		case sk::ElderBrother::eState::Hit:
			Hit();
			break;
		case sk::ElderBrother::eState::Dead:
			Dead();
			break;
		case sk::ElderBrother::eState::None:
			break;
		}
	}

	void ElderBrother::UpdateAnimation()
	{
		if (_mPrvState == _mCurState && _mPrvDir == _mDir)
		{
			return;
		}
		switch (_mCurState)
		{
		case sk::ElderBrother::eState::IDLE:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"elderbrother_Idle_Right", true);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"elderbrother_Idle_Left", true);
			break;
		case sk::ElderBrother::eState::Ready:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"elderbrother_Idle_Right", true);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"elderbrother_Idle_Left", true);
			break;
		case sk::ElderBrother::eState::Jump:
		{
			Resources::Find<Sound>(L"ELDER_BROTHER_JUMP_VOICE")->Play(false);
			Resources::Find<Sound>(L"ELDER_BROTHER_JUMP")->Play(false);
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"elderbrother_Jump_Right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"elderbrother_Jump_Left", false);
		}
			break;
		case sk::ElderBrother::eState::JumpOff:
		{
			Resources::Find<Sound>(L"ELDER_BROTHER_LANDING")->Play(false);

			Vector2 ColPos = _mCollider->GetPosition();
			ElderBroLandEff::SetPos(ColPos);
			ElderBroLandEff* landeffect = object::Instantiate<ElderBroLandEff>(eLayerType::Effect, Vector2(ColPos.x, ColPos.y));

			if (_mDir == eDir::Right)
			{
				MonsterAttack* att = object::Instantiate<MonsterAttack>(eLayerType::MonsAtt, Vector2(ColPos.x + 20.f, ColPos.y));
				att->SetMons(this);
				att->MonAttCollider();
			}
			else
			{
				MonsterAttack* att = object::Instantiate<MonsterAttack>(eLayerType::MonsAtt, Vector2(ColPos.x - 20.f, ColPos.y));
				att->SetMons(this);
				att->MonAttCollider();
			}

			if ((_mDir == eDir::Right))
			{
				_mAnimator->PlayAnimation(L"elderbrother_JumpOff_Right", false);
			}
			else if ((_mDir == eDir::Left))
			{
				_mAnimator->PlayAnimation(L"elderbrother_JumpOff_Left", false);
			}
		}
			break;
		case sk::ElderBrother::eState::Fall:
			if ((_mDir == eDir::Right))
			{
				_mAnimator->PlayAnimation(L"elderbrother_Fall_Right", false);
			}
			else if ((_mDir == eDir::Left))
			{
				_mAnimator->PlayAnimation(L"elderbrother_Fall_Left", false);
			}
			break;
		case sk::ElderBrother::eState::Attack:
		{
			// TODO
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"elderbrother_Attack_Right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"elderbrother_Attack_Left", false);
		}
			break;
		case sk::ElderBrother::eState::Hit:
			break;
		case sk::ElderBrother::eState::Dead:
		{
			Resources::Find<Sound>(L"ELDER_BROTHER_DEATH")->Play(false);
			Resources::Find<Sound>(L"ELDER_BROTHER_DEATH_VOICE_2")->Play(false);
		if ((_mDir == eDir::Right))
			_mAnimator->PlayAnimation(L"elderbrother_Dead_Right", false);
		else if ((_mDir == eDir::Left))
			_mAnimator->PlayAnimation(L"elderbrother_Dead_Left", false); 
		}
			break;
		}
	}



	void ElderBrother::OnCollisionEnter(Collider* other)
	{
	}
	void ElderBrother::OnCollisionStay(Collider* other)
	{
	}
	void ElderBrother::OnCollisionExit(Collider* other)
	{
	}
}