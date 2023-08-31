#include "skPlayer.h"
#include "skTransform.h"
#include "skTimeMgr.h"
#include "skInput.h"
#include "skResources.h"
#include "skAnimator.h"
#include "skRigidbody.h"
#include "skCollider.h"
#include "skObject.h"
#include "skDodgeEffect.h"
#include "skSlash.h"
#include "skLadder.h"
#include "skMonsterAttack.h"
#include "skPlayerHit.h"
#include "skSound.h"
#include "skPlayerUI.h"
#include "skHealEffect.h"

namespace sk
{
	math::Vector2 Player::_mPlayerPos = {};
	Player::Info Player::_mPlayerInfo = { 200,60,5,0 };
	bool Player::_mbAttSuccess = false;
	bool Player::_mbCanCharge = false;

	Player::Player() :
		_mCurState(eState::IDLE)
		, _mPrvState(eState::NONE)
		, _mAnimator(nullptr)
		, _mRigidbody(nullptr)
		, _mCollider(nullptr)
		, _mDir(eDir::Right)
		, _mPrvDir(eDir::None)
		, _mCurAttState(eAttState::NONE)
		, _mPrvAttState(eAttState::NONE)
		, _mAttTime(0.f)
		, _mAttDelay(2.0f)
		, _mChargeTime(0.f)
		, _mHitCount(0)
		, _mAttCount(0)
		, _mImgIdx(0)
		, _mbCanClimb(false)
		, _mbCanIgnore(false)
		, _mbDefendOn(false)
		, _mbCounter(false)
		, _mbCanAtt(true)
		, _mbCanEff(true)
		, _mbCanPray(false)
		, _mbCanCargeAtt(false)
		, _mbEmtyFlask(false)
	{	
	}	
	Player::~Player()
	{
	}

	void Player::Initialize()
	{
		_mAnimator = AddComponent<Animator>();
		_mRigidbody = AddComponent<Rigidbody>();
		_mCollider = AddComponent<Collider>();

		_mCollider->SetSize(Vector2(50.0f, 140.0f));
		_mCollider->SetOffset(Vector2(0.0f, 185.0f));

		_mAnimator->SetScale(Vector2(2.0f, 2.0f));
		//_mPlayerInfo = { 200,100,5,2};

		InitAnimation();
		_mAnimator->PlayAnimation(L"Idle_right", true);
		_mCurState = eState::IDLE;

	}

	void Player::InitAnimation()
	{
		Texture* Rising = Resources::Load<Texture>(L"Rising", L"..\\Resources\\image\\rising.bmp");
		Texture* Idle = Resources::Load<Texture>(L"Idle", L"..\\Resources\\image\\Idle.bmp");
		Texture* run = Resources::Load<Texture>(L"run", L"..\\Resources\\image\\penitent_run.bmp");
		Texture* stoprun = Resources::Load<Texture>(L"stop_run_right", L"..\\Resources\\image\\stoprun.bmp");
		Texture* crouch = Resources::Load<Texture>(L"crouch", L"..\\Resources\\image\\penitent_crouch.bmp");
		Texture* crouchup = Resources::Load<Texture>(L"crouchup", L"..\\Resources\\image\\penitent_crouchup.bmp");
		Texture* crouch_attack = Resources::Load<Texture>(L"crouch_attack", L"..\\Resources\\image\\crouch_attack.bmp");
		Texture* parry = Resources::Load<Texture>(L"parry", L"..\\Resources\\image\\parry.bmp");
		Texture* attack = Resources::Load<Texture>(L"attack", L"..\\Resources\\image\\attack_combo1.bmp");
		Texture* attack2 = Resources::Load<Texture>(L"attack2", L"..\\Resources\\image\\attack_combo2.png");
		Texture* attack3 = Resources::Load<Texture>(L"attack3", L"..\\Resources\\image\\attack_combo3.png");
		Texture* dodge = Resources::Load<Texture>(L"dodge", L"..\\Resources\\image\\dodge.bmp");
		Texture* jump = Resources::Load<Texture>(L"jump", L"..\\Resources\\image\\jump.bmp");
		Texture* jump_attack = Resources::Load<Texture>(L"jump_attack", L"..\\Resources\\image\\jumpattack.bmp");
		Texture* climb_ladder = Resources::Load<Texture>(L"Climb", L"..\\Resources\\image\\climb.bmp");
		Texture* parrysuccess = Resources::Load<Texture>(L"ParrySucess", L"..\\Resources\\image\\parrysuccess.bmp");
		Texture* playerhit = Resources::Load<Texture>(L"PlayerHit", L"..\\Resources\\image\\playerHit.bmp");
		Texture* Heal = Resources::Load<Texture>(L"Healing", L"..\\Resources\\image\\penitent_healing.bmp");
		Texture* ChargeAtt = Resources::Load<Texture>(L"ChargeAtt", L"..\\Resources\\image\\penitent_charge_attack.bmp");
		Texture* Counter = Resources::Load<Texture>(L"Counter", L"..\\Resources\\image\\penitent_counter.png");
		Texture* Pray = Resources::Load<Texture>(L"Pray", L"..\\Resources\\image\\payer_pray.bmp");

		Resources::Load<Sound>(L"Dodge", L"..\\Resources\\sound\\PENITENT_DASH.wav");

		_mAnimator->CreateAnimation(L"Rising", Rising, Vector2(0.0f, 0.0f), Vector2(100.0f, 90.0f), 42, Vector2(-3.0f, 185.0f), 0.08f);

		_mAnimator->CreateAnimation(L"Idle_right", Idle, Vector2(0.0f, 0.0f), Vector2(80.0f, 80.0f), 13, Vector2(-30.0f, 175.0f), 0.1f);
		_mAnimator->CreateAnimation(L"Idle_left", Idle, Vector2(0.0f, 80.0f), Vector2(80.0f, 80.0f), 13, Vector2(30.0f, 175.0f), 0.1f);

		_mAnimator->CreateAnimation(L"Run_right", run, Vector2(0.0f, 0.0f), Vector2(80.0f, 80.0f), 14, Vector2(-40.0f, 175.0f), 0.05f);
		_mAnimator->CreateAnimation(L"Run_left", run, Vector2(0.0f, 80.0f), Vector2(80.0f, 80.0f), 14, Vector2(40.0f, 175.0f), 0.055f);

		_mAnimator->CreateAnimation(L"Stop_run_right", stoprun, Vector2(0.0f, 0.0f), Vector2(120.0f, 80.0f), 7, Vector2(0.0f, 175.0f), 0.03f);
		_mAnimator->CreateAnimation(L"Stop_run_left", stoprun, Vector2(0.0f, 80.0f), Vector2(120.0f, 80.0f), 7, Vector2(0.0f, 175.0f), 0.03f);

		_mAnimator->CreateAnimation(L"Crouch_down_right", crouch, Vector2(0.0f, 0.0f), Vector2(90.0f, 80.0f), 7, Vector2(-40.0f, 175.0f), 0.07f);
		_mAnimator->CreateAnimation(L"Crouch_down_left", crouch, Vector2(0.0f, 80.0f), Vector2(90.0f, 80.0f), 7, Vector2(40.0f, 175.0f), 0.07f);

		_mAnimator->CreateAnimation(L"Crouch_Up_right", crouchup, Vector2(0.0f, 0.0f), Vector2(81.0f, 80.0f), 5, Vector2(-40.0f, 175.0f), 0.07f);
		_mAnimator->CreateAnimation(L"Crouch_Up_left", crouchup, Vector2(0.0f, 80.0f), Vector2(81.0f, 80.0f), 5, Vector2(40.0f, 175.0f), 0.07f);

		_mAnimator->CreateAnimation(L"Crouch_attack_right", crouch_attack, Vector2(0.0f, 0.0f), Vector2(150.0f, 90.0f), 13, Vector2(27.0f, 173.0f), 0.05f);
		_mAnimator->CreateAnimation(L"Crouch_attack_left", crouch_attack, Vector2(0.0f, 90.0f), Vector2(150.0f, 90.0f), 13, Vector2(-27.0f, 173.0f), 0.05f);

		_mAnimator->CreateAnimation(L"Parry_right", parry, Vector2(0.0f, 0.0f), Vector2(90.0f, 80.0f), 10, Vector2(-30.0f, 175.0f), 0.06f);
		_mAnimator->CreateAnimation(L"Parry_left", parry, Vector2(0.0f, 80.0f), Vector2(90.0f, 80.0f), 10, Vector2(30.0f, 175.0f), 0.06f);

		_mAnimator->CreateAnimation(L"Attack1_right", attack, Vector2(0.0f, 0.0f), Vector2(200.0f, 80.0f), 8, Vector2(0.0f, 175.0f), 0.045f);
		_mAnimator->CreateAnimation(L"Attack1_left", attack, Vector2(0.0f, 80.0f), Vector2(200.0f, 80.0f), 8, Vector2(0.0f, 175.0f), 0.045f);

		_mAnimator->CreateAnimation(L"Attack2_right", attack2, Vector2(0.0f, 0.0f), Vector2(200.0f, 80.0f), 6, Vector2(0.0f, 175.0f), 0.05f);
		_mAnimator->CreateAnimation(L"Attack2_left", attack2, Vector2(0.0f, 80.0f), Vector2(200.0f, 80.0f), 6, Vector2(0.0f, 175.0f), 0.05f);

		_mAnimator->CreateAnimation(L"Attack3_right", attack3, Vector2(0.0f, 0.0f), Vector2(200.0f, 90.0f), 14, Vector2(140.0f, 165.0f), 0.06f);
		_mAnimator->CreateAnimation(L"Attack3_left", attack3, Vector2(0.0f, 90.0f), Vector2(200.0f, 90.0f), 14, Vector2(-140.0f, 165.0f), 0.06f);

		_mAnimator->CreateAnimation(L"Dodge_right", dodge, Vector2(0.0f, 0.0f), Vector2(100.0f, 80.0f), 13, Vector2(-30.0f, 175.0f), 0.04f);
		_mAnimator->CreateAnimation(L"Dodge_left", dodge, Vector2(0.0f, 80.0f), Vector2(100.0f, 80.0f), 13, Vector2(30.0f, 175.0f), 0.04f);

		_mAnimator->CreateAnimation(L"Jump_right", jump, Vector2(0.0f, 00.0f), Vector2(90.0f, 90.0f), 4, Vector2(-20.0f, 175.0f), 0.08f);
		_mAnimator->CreateAnimation(L"Jump_left", jump, Vector2(0.0f, 90.0f), Vector2(90.0f, 90.0f), 4, Vector2(20.0f, 175.0f), 0.08f);

		_mAnimator->CreateAnimation(L"Run_Jump_right", jump, Vector2(0.0f, 180.0f), Vector2(90.0f, 90.0f), 8, Vector2(0.0f, 175.0f), 0.1f);
		_mAnimator->CreateAnimation(L"Run_Jump_left", jump, Vector2(0.0f, 360.0f), Vector2(90.0f, 90.0f), 8, Vector2(0.0f, 175.0f), 0.1f);

		_mAnimator->CreateAnimation(L"Run_Fall_right", jump, Vector2(720.0f, 180.0f), Vector2(90.0f, 90.0f), 4, Vector2(-20.0f, 175.0f), 0.1f);
		_mAnimator->CreateAnimation(L"Run_Fall_left", jump, Vector2(720.0f, 360.0f), Vector2(90.0f, 90.0f), 4, Vector2(20.0f, 175.0f), 0.1f);

		_mAnimator->CreateAnimation(L"Jumploop_right", jump, Vector2(450.0f, 0.0f), Vector2(90.0f, 90.0f), 3, Vector2(-20.0f, 175.0f), 0.08f);
		_mAnimator->CreateAnimation(L"Jumploop_left", jump, Vector2(450.0f, 90.0f), Vector2(90.0f, 90.0f), 3, Vector2(20.0f, 175.0f), 0.08f);

		_mAnimator->CreateAnimation(L"Land_right", jump, Vector2(720.0f, 00.0f), Vector2(90.0f, 90.0f), 3, Vector2(-30.0f, 165.0f), 0.06f);
		_mAnimator->CreateAnimation(L"Land_left", jump, Vector2(720.0f, 90.0f), Vector2(90.0f, 90.0f), 3, Vector2(30.0f, 165.0f), 0.06f);

		_mAnimator->CreateAnimation(L"Jump_Attack_right", jump_attack, Vector2(0.0f, 0.0f), Vector2(155.0f, 100.0f), 5, Vector2(5.0f, 165.0f), 0.065f);
		_mAnimator->CreateAnimation(L"Jump_Attack_left", jump_attack, Vector2(0.0f, 100.0f), Vector2(155.0f, 100.0f), 5, Vector2(-5.0f, 165.0f), 0.065f);

		_mAnimator->CreateAnimation(L"Jump_Attack2_right", jump_attack, Vector2(0.0f, 200.0f), Vector2(155.0f, 100.0f), 5, Vector2(5.0f, 165.0f), 0.065f);
		_mAnimator->CreateAnimation(L"Jump_Attack2_left", jump_attack, Vector2(0.0f, 300.0f), Vector2(155.0f, 100.0f), 5, Vector2(-5.0f, 165.0f), 0.065f);

		_mAnimator->CreateAnimation(L"ParrySuccess_right", parrysuccess, Vector2(0.0f, 0.0f), Vector2(150.0f, 110.0f), 11, Vector2(20.0f, 152.0f), 0.065f);
		_mAnimator->CreateAnimation(L"ParrySuccess_left", parrysuccess, Vector2(0.0f, 110.0f), Vector2(150.0f, 110.0f), 11, Vector2(-20.0f, 152.0f), 0.065f);

		_mAnimator->CreateAnimation(L"PlayerHit_right", playerhit, Vector2(0.0f, 0.0f), Vector2(100.0f, 90.0f), 19, Vector2(-25.0f, 190.0f), 0.035f);
		_mAnimator->CreateAnimation(L"PlayerHit_left", playerhit, Vector2(0.0f, 90.0f), Vector2(100.0f, 90.0f), 19, Vector2(25.0f, 190.0f), 0.035f);

		_mAnimator->CreateAnimation(L"Healing_right", Heal, Vector2(0.0f, 00.0f), Vector2(80.0f, 90.0f), 36, Vector2(-20.0f, 175.0f), 0.08f);
		_mAnimator->CreateAnimation(L"Healing_left", Heal, Vector2(0.0f, 90.0f), Vector2(80.0f, 90.0f), 36, Vector2(20.0f, 175.0f), 0.08f);

		_mAnimator->CreateAnimation(L"Counter_right", Counter, Vector2(0.0f, 0.0f), Vector2(256.0f, 128.0f), 20, Vector2(87.0f, 151.0f), 0.045f);
		_mAnimator->CreateAnimation(L"Counter_left", Counter, Vector2(0.0f, 128.0f), Vector2(256.0f, 128.0f), 20, Vector2(-87.0f, 151.0f), 0.045f);

		_mAnimator->CreateAnimation(L"Climb_Ladder", climb_ladder, Vector2(0.0f, 0.0f), Vector2(35.0f, 80.0f), 10, Vector2(-5.0f, 165.0f), 0.1f);

		_mAnimator->CreateAnimation(L"Charge_Att_Right", ChargeAtt, Vector2(0.0f, 0.0f), Vector2(200.0f, 200.0f), 50, Vector2(22.0f, 64.0f), 0.06f);
		_mAnimator->CreateAnimation(L"Charge_Att_Left", ChargeAtt, Vector2(0.0f, 200.0f), Vector2(200.0f, 200.0f), 50, Vector2(-22.0f, 64.0f), 0.06f);

		_mAnimator->CreateAnimation(L"pray", Pray, Vector2(0.0f, 0.0f), Vector2(100.0f, 95.0f), 52, Vector2(-5.0f, 175.0f), 0.055f);

		PlayerUI* UI = object::Instantiate<PlayerUI>(eLayerType::UI);
		UI->SetPlayer(this);
	}

	void Player::Update()
	{
		GameObject::Update();

		_mPrvDir = _mDir;
		_mPrvState = _mCurState;
		_mPrvAttState = _mCurAttState;

		if (_mPlayerInfo.Flask <= 0)
			_mbEmtyFlask = true;
		else
			_mbEmtyFlask = false;


		if (_mbAttSuccess || _mbCounter)
		{
			_mAttTime += TimeMgr::DeltaTime();
			if (_mAttTime >= _mAttDelay)
			{
				_mAttTime = 0;
				_mHitCount = 0;
				_mbCounter = false;
				_mbAttSuccess = false;
				_mbCanAtt = true;
			}
		}

		PixelCollision();
		UpdateState();
		UpdateAnimation();
	}

	//pixel 충돌
	void Player::PixelCollision()
	{
		Transform* tr = GetComponent<Transform>();
		if (_mFloorTexture != nullptr)
		{
			Vector2 ColPos = _mCollider->GetPosition();
			Vector2 ColSize = _mCollider->GetSize();

			Vector2 Right = Vector2(ColPos.x + (ColSize.x / 2.0f), ColPos.y );
			Vector2 Left = Vector2(ColPos.x - (ColSize.x / 2.0f), ColPos.y );
			Vector2 Bottom = Vector2(ColPos.x, ColPos.y + (ColSize.y / 2.0f));

			COLORREF RightColor = _mFloorTexture->GetTexturePixel((int)Right.x, (int)Right.y);
			COLORREF RightBttomColor = _mFloorTexture->GetTexturePixel((int)Bottom.x+1, (int)Bottom.y-1);
			COLORREF LeftColor = _mFloorTexture->GetTexturePixel((int)Left.x,(int)Left.y);
			COLORREF LeftBttomColor = _mFloorTexture->GetTexturePixel((int)Bottom.x-1, (int)Bottom.y-1);
			COLORREF BottomColor = _mFloorTexture->GetTexturePixel((int)Bottom.x, (int)Bottom.y);

			Rigidbody* rb = GetComponent<Rigidbody>();

			if (BottomColor == RGB(255, 0, 255))
			{
				if (!(_mCurState == eState::JUMP || _mCurState == eState::RUN_JUMP))
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

		_mPlayerPos = tr->GetPosition();

	}
	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


	void Player::Idle()
	{
		Vector2 velocity = _mRigidbody->GetVelocity();

		if (Input::GetKeyDown(eKeyCode::Shift))
		{
			Resources::Find<Sound>(L"Dodge")->Play(false);
			_mCurState = eState::DODGE;
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			_mCurState = eState::ATTACK;
		}

		if (Input::GetKeyDown(eKeyCode::J))
		{
			_mCurState = eState::PARRY;
		}

		if (Input::GetKeyDown(eKeyCode::Space))
		{
			velocity.y = -850.0f;
			_mRigidbody->SetVelocity(velocity);
			_mRigidbody->SetGround(false);
			_mCurState = eState::JUMP;
		}
		
		// 플레이어 이동
		if (Input::GetKey(eKeyCode::A) && !(Input::GetKey(eKeyCode::D)))
		{
			_mCurState = eState::MOVE;
		}
		if (Input::GetKey(eKeyCode::D) && !(Input::GetKey(eKeyCode::A)))
		{
			_mCurState = eState::MOVE;
		}

		if (Input::GetKey(eKeyCode::S))
		{
			_mCurState = eState::CROUCH;
		}

		if ((_mbCanClimb && Input::GetKey(eKeyCode::S)) || (_mbCanClimb && Input::GetKey(eKeyCode::W)))
		{
			_mCurState = eState::CLIMB;
		}


		if (Input::GetKeyDown(eKeyCode::F) && !(_mbEmtyFlask))
		{
			_mPlayerInfo.Flask--;
			_mCurState = eState::HEAL;
		}

		if (_mbCanCharge && Input::GetKey(eKeyCode::K))
		{
			_mChargeTime += TimeMgr::DeltaTime();
			if (_mChargeTime > 0.3f)
			{
				_mCurState = eState::CHARGEATT;
			}
		}
	}

	void Player::Move()
	{
		Vector2 velocity = _mRigidbody->GetVelocity();

		if (Input::GetKey(eKeyCode::A) )
		{
			_mDir = eDir::Left;
			velocity.x = -250.0f;
			_mRigidbody->SetVelocity(velocity);
		}

		if (Input::GetKey(eKeyCode::D) )
		{
			_mDir = eDir::Right;
			velocity.x = 250.0f;
			_mRigidbody->SetVelocity(velocity);
		}

		if (Input::GetKeyDown(eKeyCode::Shift))
		{
			Resources::Find<Sound>(L"Dodge")->Play(false);
			_mCurState = eState::DODGE;
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			_mCurState = eState::ATTACK;
		}

		if (Input::GetKeyDown(eKeyCode::J))
		{
			_mCurState = eState::PARRY;
		}

		if (Input::GetKeyDown(eKeyCode::Space))
		{
			velocity.y = -850.0f;
			_mRigidbody->SetVelocity(velocity);
			_mRigidbody->SetGround(false);
		
			_mCurState = eState::RUN_JUMP;
		}

		if (Input::GetKeyUp(eKeyCode::A))
		{
			_mCurState = eState::RUN_OFF;
		}

		if (Input::GetKeyUp(eKeyCode::D))
		{
			_mCurState = eState::RUN_OFF;
		}

		// 좌우 동시입력시 이동제한
		if (Input::GetKey(eKeyCode::A) && Input::GetKeyDown(eKeyCode::D))
		{
			_mCurState = eState::RUN_OFF;
		}
		else if (Input::GetKey(eKeyCode::D) && Input::GetKeyDown(eKeyCode::A))
		{
			_mCurState = eState::RUN_OFF;
		}

		if ((_mbCanClimb && Input::GetKey(eKeyCode::S)) || (_mbCanClimb && Input::GetKey(eKeyCode::W)))
		{
			_mCurState = eState::CLIMB;
		}

		if (Input::GetKeyDown(eKeyCode::F) && !(_mbEmtyFlask))
		{
			_mPlayerInfo.Flask--;
			_mCurState = eState::HEAL;
		}
	}

	void Player::Dodge()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (!((_mAnimator->IsActiveAnimationComplete())) && (_mDir == eDir::Right))
			pos.x += 375.0f * TimeMgr::DeltaTime();
		else if (!((_mAnimator->IsActiveAnimationComplete())) && (_mDir == eDir::Left))
			pos.x -= 375.0f * TimeMgr::DeltaTime();

		tr->SetPosition(pos);

		if (_mAnimator->IsActiveAnimationComplete())
		{
			if (Input::GetKey(eKeyCode::S))
			{
				_mCurState = eState::CROUCH;
			}
			else
				_mCurState = eState::IDLE;
		}
	}

	void Player::Attack()
	{
		//if (Input::GetKey(eKeyCode::K))
		//{
		//	_mChargeTime += TimeMgr::DeltaTime();
		//	if (_mChargeTime >0.5f)
		//	{
		//		_mCurState = eState::CHARGEATT;
		//	}
		//}

		if (_mbCounter && _mbCanAtt)
		{
			_mCurAttState = eAttState::COUNTER_SLASH;
			if (_mAnimator->GetActiveAnime()->GetIndex() == 11)
			{
				_mbCounter = false;
				_mbCanAtt = false;
				Slash* slash = new Slash(this);
				object::Instantiate<Slash>(eLayerType::Attack, slash);
				_mCurState = eState::ATTACKREADY;
			}
		}
		else
		{
			if (_mHitCount == 0 && _mbCanAtt)
			{
				_mCurAttState = eAttState::FIRST_SLASH;
				if (_mbAttSuccess)
				{
					_mHitCount = 1;
					_mbAttSuccess = false;
				}
				if (_mAnimator->GetActiveAnime()->GetIndex() == 4)
				{
					Slash* slash = new Slash(this);
					object::Instantiate<Slash>(eLayerType::Attack, slash);
					_mbCanAtt = false;
					_mCurState = eState::ATTACKREADY;
				}
			}
			else if (_mHitCount == 1 && _mbCanAtt)
			{
				_mCurAttState = eAttState::SECOND_SLASH;
				if (_mbAttSuccess)
				{
					_mHitCount = 2;
					_mbAttSuccess = false;
				}
				if (_mAnimator->GetActiveAnime()->GetIndex() == 3)
				{
					Slash* slash = new Slash(this);
					object::Instantiate<Slash>(eLayerType::Attack, slash);
					_mbCanAtt = false;
					_mCurState = eState::ATTACKREADY;
				}
			}
			else if (_mHitCount == 2 && _mbCanAtt)
			{
				_mCurAttState = eAttState::THIRD_SLASH;
				if (_mbAttSuccess)
				{
					_mHitCount = 0;
					_mbAttSuccess = false;
				}
				if (_mAnimator->GetActiveAnime()->GetIndex() == 5)
				{
					Slash* slash = new Slash(this);
					object::Instantiate<Slash>(eLayerType::Attack, slash);
					_mbCanAtt = false;
					_mCurState = eState::ATTACKREADY;
				}
			}
		}
		
	}

	// 공격시 여러개 collider 생성 막기위함
	void Player::AttackReady()
	{
		if (Input::GetKeyDown(eKeyCode::K) && (_mAnimator->GetActiveAnime() != _mAnimator->FindAnimation(L"Counter_right") ||
											_mAnimator->GetActiveAnime() != _mAnimator->FindAnimation(L"Counter_left")))
		{
			_mbCanAtt = true;
		}

		if (_mAnimator->IsActiveAnimationComplete() &&
			(_mCurAttState == eAttState::FIRST_SLASH ||
			_mCurAttState == eAttState::SECOND_SLASH ||
			_mCurAttState == eAttState::THIRD_SLASH ||
			_mCurAttState == eAttState::COUNTER_SLASH))
		{
			if (_mbCanAtt)
			{
				_mCurState = eState::ATTACK;
			}
			else
			{
				_mbCanAtt = true;
				_mCurState = eState::IDLE;
			}
		}
		else if (_mAnimator->IsActiveAnimationComplete() &&
				(_mCurAttState == eAttState::JUMP_FIRST_SLASH||
				 _mCurAttState == eAttState::JUMP_SECOND_SLASH))
		{
			if (_mbCanAtt)
			{
				_mCurState = eState::JUMP_ATT;
			}
			else
			{
				_mbCanAtt = true;
				_mCurState = eState::FALL;
			}
		}
	}

	void Player::Crouch()
	{
		if (Input::GetKeyDown(eKeyCode::Shift))
		{
			_mCurState = eState::DODGE;
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			_mCurState = eState::CROUCH_ATT;
		}

		// 앉은상태에서 방향 전환
		if (Input::GetKeyDown(eKeyCode::A) && (_mDir == eDir::Right))
		{
			if (_mAnimator->IsActiveAnimationComplete())
			{
				_mDir = eDir::Left;
			}
		}
		else if (Input::GetKeyDown(eKeyCode::D) && (_mDir == eDir::Left))
		{
			if (_mAnimator->IsActiveAnimationComplete())
			{
				_mDir = eDir::Right;
			}
		}

		if (Input::GetKeyUp(eKeyCode::S))
		{
			_mCurState = eState::CROUCH_UP;
		}

		if (_mbCanDown &&Input::GetKey(eKeyCode::S) && Input::GetKeyDown(eKeyCode::Space))
		{
			_mCurState = eState::FALL;
			_mRigidbody->SetGround(false);
		}
	}
	void Player::Crouch_Att()
	{
		if (_mAnimator->GetActiveAnime()->GetIndex() == 6)
		{
			//Transform* tr = GetComponent<Transform>();
			//Slash* slash1 = object::Instantiate<Slash>(eLayerType::Attack, tr->GetPosition());
			//slash1->SetPlayer(this);
			//slash1->SlashCollider();
		}

		if (Input::GetKeyUp(eKeyCode::S))
		{
			_mCurState = eState::CROUCH_UP;
		}

		if (_mAnimator->IsActiveAnimationComplete())
			_mCurState = eState::CROUCH;
	}
	void Player::Crouch_Up()
	{
		if (_mAnimator->IsActiveAnimationComplete())
			_mCurState = eState::IDLE;
	}

	void Player::Parry()
	{
		if (_mAnimator->GetActiveAnime()->GetIndex() == 2)
		{
			_mbDefendOn = true;
		}
		if (_mAnimator->GetActiveAnime()->GetIndex() == 8)
		{
			_mbDefendOn = false;
		}
		

		if (_mAnimator->IsActiveAnimationComplete())
			_mCurState = eState::IDLE;
	}

	void Player::Run_Off()
	{

		if (Input::GetKeyDown(eKeyCode::K))
		{
			_mCurState = eState::ATTACK;
		}
		// 방향 바로 전환 가능
		if (Input::GetKey(eKeyCode::A))
		{
			_mCurState = eState::MOVE;
		}
		else if (Input::GetKey(eKeyCode::D) )
		{
			_mCurState = eState::MOVE;
		}
		if (_mAnimator->IsActiveAnimationComplete())
			_mCurState = eState::IDLE;
	}

	void Player::Jump_Att()
	{
		Vector2 velocity = _mRigidbody->GetVelocity();

		if (_mRigidbody->GetGround())
		{
			_mCurState = eState::JUMP_OFF;
		}

		if (Input::GetKey(eKeyCode::A) && _mAnimator->GetActiveAnime() == _mAnimator->FindAnimation(L"Jump_Attack_left"))
		{
			_mImgIdx = _mAnimator->GetActiveAnime()->GetIndex();
			_mDir = eDir::Left;
			velocity.x = -250.0f;
			_mRigidbody->SetVelocity(velocity);
		}

		if (Input::GetKey(eKeyCode::D) && _mAnimator->GetActiveAnime() == _mAnimator->FindAnimation(L"Jump_Attack_right"))
		{
			_mImgIdx = _mAnimator->GetActiveAnime()->GetIndex();
			_mDir = eDir::Right;
			velocity.x = 250.0f;
			_mRigidbody->SetVelocity(velocity);
		}

		if (_mHitCount == 0 && _mbCanAtt)
		{
			_mCurAttState = eAttState::JUMP_FIRST_SLASH;
			if (_mAnimator->GetActiveAnime()->GetIndex() == 4)
			{
				if (_mAttCount == 0)
				{
					_mAttCount++;
					Slash* slash = new Slash(this);
					object::Instantiate<Slash>(eLayerType::Attack, slash);
				}
				_mHitCount = 1;
				_mbCanAtt = false;
				_mCurState = eState::ATTACKREADY;
			}
		}
		else if (_mHitCount == 1 && _mbCanAtt)
		{
			_mCurAttState = eAttState::JUMP_SECOND_SLASH;
			if (_mAnimator->GetActiveAnime()->GetIndex() == 3)
			{
				if (_mAttCount ==0)
				{
					_mAttCount++;
					Slash* slash = new Slash(this);
					object::Instantiate<Slash>(eLayerType::Attack, slash);
				}
				_mHitCount = 2;
				_mbCanAtt = false;
				_mCurState = eState::ATTACKREADY;
			}
		}

		// att -> fall -> second att
		if (_mAnimator->IsActiveAnimationComplete())
			_mCurState = eState::FALL;
	}

	void Player::Jump()
	{
		Vector2 velocity = _mRigidbody->GetVelocity();

		_mRigidbody->SetVelocity(velocity);

		if ((!(_mRigidbody->GetGround()) && _mRigidbody->GetVelocity().y >= 0))
		{
			_mCurState = eState::FALL;
		}

		if (_mRigidbody->GetGround())
		{
			_mCurState = eState::JUMP_OFF;
		}

		if (Input::GetKeyDown(eKeyCode::A) && (_mDir == eDir::Right))
		{
			_mImgIdx = _mAnimator->GetActiveAnime()->GetIndex();
			_mDir = eDir::Left;
		}
		else if (Input::GetKeyDown(eKeyCode::D) && (_mDir == eDir::Left))
		{
			_mImgIdx = _mAnimator->GetActiveAnime()->GetIndex();
			_mDir = eDir::Right;
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			_mCurState = eState::JUMP_ATT;
		}

		if ((_mbCanClimb && Input::GetKey(eKeyCode::S)) || (_mbCanClimb && Input::GetKey(eKeyCode::W)))
		{
			_mCurState = eState::CLIMB;
		}

	}
	void Player::Jump_Off() // 바로움직일수잇게 나중에 수정해야
	{
		Vector2 velocity = _mRigidbody->GetVelocity();

		_mHitCount = 0;
		_mCurAttState = eAttState::NONE;

		if (Input::GetKeyDown(eKeyCode::Shift))
		{
			_mCurState = eState::DODGE;
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			_mCurState = eState::ATTACK;
		}

		if (Input::GetKey(eKeyCode::A) && !(Input::GetKey(eKeyCode::D)))
		{
			_mCurState = eState::MOVE;
		}
		if (Input::GetKey(eKeyCode::D) && !(Input::GetKey(eKeyCode::A)))
		{
			_mCurState = eState::MOVE;
		}

		if (Input::GetKeyDown(eKeyCode::Space))
		{
			velocity.y = -850.0f;
			_mRigidbody->SetVelocity(velocity);
			_mRigidbody->SetGround(false);
			_mCurState = eState::JUMP;
		}

		if (_mAnimator->IsActiveAnimationComplete())
			_mCurState = eState::IDLE;
	}

	void Player::Run_Jump()
	{
		Vector2 velocity = _mRigidbody->GetVelocity();

		_mRigidbody->SetVelocity(velocity);

		if (Input::GetKey(eKeyCode::A))
		{
			_mImgIdx = _mAnimator->GetActiveAnime()->GetIndex();
			_mDir = eDir::Left;
			velocity.x = -250.0f;
			_mRigidbody->SetVelocity(velocity);
		}

		if (Input::GetKey(eKeyCode::D))
		{
			_mImgIdx = _mAnimator->GetActiveAnime()->GetIndex();
			_mDir = eDir::Right;
			velocity.x = 250.0f;
			_mRigidbody->SetVelocity(velocity);
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			_mCurState = eState::JUMP_ATT;
		}

		if ((!(_mRigidbody->GetGround()) && _mRigidbody->GetVelocity().y >= 0))
		{
			_mCurState = eState::FALL;
		}

		if ((_mbCanClimb && Input::GetKey(eKeyCode::S)) || (_mbCanClimb && Input::GetKey(eKeyCode::W)))
		{
			_mCurState = eState::CLIMB;
		}
	}

	void Player::Fall()
	{
		Vector2 velocity = _mRigidbody->GetVelocity();

		if (_mRigidbody->GetGround())
		{
			_mCurState = eState::JUMP_OFF;
		}

		if (Input::GetKeyDown(eKeyCode::A) && (_mDir == eDir::Right))
		{
			_mImgIdx = _mAnimator->GetActiveAnime()->GetIndex();
			_mDir = eDir::Left;
		}
		else if (Input::GetKeyDown(eKeyCode::D) && (_mDir == eDir::Left))
		{
			_mImgIdx = _mAnimator->GetActiveAnime()->GetIndex();
			_mDir = eDir::Right;
		}

		// 낙하 이동
		if (Input::GetKey(eKeyCode::A))
		{
			_mCurState = eState::FALL_MOVE;
		}

		if (Input::GetKey(eKeyCode::D) )
		{
			_mCurState = eState::FALL_MOVE;
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			_mCurState = eState::JUMP_ATT;
		}

		if ((_mbCanClimb && Input::GetKey(eKeyCode::S)) || (_mbCanClimb && Input::GetKey(eKeyCode::W)))
		{
			_mCurState = eState::CLIMB;
		}
	}
	void Player::Fall_Move()
	{
		Vector2 velocity = _mRigidbody->GetVelocity();
		
		if (_mRigidbody->GetGround())
		{
			_mCurState = eState::JUMP_OFF;
		}

		if (Input::GetKey(eKeyCode::A))
		{
			_mDir = eDir::Left;
			velocity.x = -300.0f;
			_mRigidbody->SetVelocity(velocity);
		}

		if (Input::GetKey(eKeyCode::D))
		{
			_mDir = eDir::Right;
			velocity.x = 300.0f;
			_mRigidbody->SetVelocity(velocity);
		}

		if (Input::GetKeyUp(eKeyCode::A))
		{
			_mCurState = eState::FALL;
		}

		if (Input::GetKeyUp(eKeyCode::D))
		{
			_mCurState = eState::FALL;
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			_mCurState = eState::JUMP_ATT;
		}

		if ((_mbCanClimb && Input::GetKey(eKeyCode::S)) || (_mbCanClimb && Input::GetKey(eKeyCode::W)))
		{
			_mCurState = eState::CLIMB;
		}
	}
	void Player::Climb()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		if (_mImgIdx == 9)
		{
			_mImgIdx = 0;
		}
		if (Input::GetKey(eKeyCode::W))
		{
			pos.y -= 250.0f * TimeMgr::DeltaTime();
			_mImgIdx++;
		}
		if (Input::GetKey(eKeyCode::S))
		{
			pos.y += 250.0f * TimeMgr::DeltaTime();
			_mImgIdx++;
		}
		tr->SetPosition(pos);


		if (Input::GetKey(eKeyCode::Space))
		{
			_mRigidbody->SetGround(false);
			_mCurState = eState::FALL;
		}

	}

	void Player::Hit()
	{
		_mbCounter = false;
		_mAttTime = 0;
		_mHitCount = 0;
		_mbAttSuccess = false;
		_mbCanAtt = true;
		if (_mAnimator->IsActiveAnimationComplete())
		{
			_mCurState = eState::IDLE;
		}
	}

	void Player::Heal()
	{
		if (_mPlayerInfo.Flask <= 0)
		{
			_mbEmtyFlask = true;
			_mPlayerInfo.Flask = 0;
		}
		_mAttTime = 0;
		_mHitCount = 0;
		_mbAttSuccess = false;
		_mbCanAtt = true;

		if (_mbCanEff)
		{
			if (_mAnimator->GetActiveAnime()->GetIndex() == 14)
			{
				_mbCanEff = false;
				Transform* tr = GetComponent<Transform>();
				HealEffect* healeff = object::Instantiate<HealEffect>(eLayerType::Effect, tr->GetPosition());
				healeff->PlayAnimation(_mDir);
			}
		}

		if (_mAnimator->IsActiveAnimationComplete())
		{
			_mPlayerInfo.Hp += 70;
			if (_mPlayerInfo.Hp >= 200)
			{
				_mPlayerInfo.Hp = 200;
			}
			_mbCanEff = true;
			_mCurState = eState::IDLE;
		}
	}

	void Player::ChargeAtt()
	{
		_mCurAttState = eAttState::CHARGE_SLASH;

		_mChargeTime = 0.f;
		if (Input::GetKey(eKeyCode::K))
		{
			if (_mAnimator->GetActiveAnime()->GetIndex()== 30)
			{
				_mAnimator->GetActiveAnime()->SetIndex(23);
			}
		}

		if (Input::GetKeyUp(eKeyCode::K))
		{
			// 일정 프레임까지 차징
			if (_mAnimator->GetActiveAnime()->GetIndex() < 13)
			{
				if (_mDir == eDir::Right)
					_mAnimator->PlayAnimation(L"Idle_right", true);
				else
					_mAnimator->PlayAnimation(L"Idle_left", true);

				_mCurState = eState::IDLE;
			}
			else
			{
				_mAnimator->GetActiveAnime()->SetIndex(32);
			}
		}

		if (_mAnimator->GetActiveAnime()->GetIndex() == 38 && _mbCanAtt)
		{
			Slash* slash = new Slash(this);
			object::Instantiate<Slash>(eLayerType::Attack, slash);
			_mbCanAtt = false;
		}

		if (_mAnimator->IsActiveAnimationComplete())
		{
			// TODO 
			// ATTCOLLIDER
			_mbCanAtt = true;
			_mCurState = eState::IDLE;
		}
	}

	void Player::Rising()
	{
		if (Input::GetKey(eKeyCode::F))
		{
			_mAnimator->PlayAnimation(L"Rising");
		}
		
		if (_mAnimator->GetActiveAnime() == _mAnimator->FindAnimation(L"Rising") && _mAnimator->IsActiveAnimationComplete())
		{
			_mCurState = eState::IDLE;
		}
	}

	void Player::CutScene()
	{

	}

	void Player::Pray()
	{
		if (_mAnimator->IsActiveAnimationComplete())
		{
			_mPlayerInfo.Hp = 200;
			_mPlayerInfo.Mp = 100;
			_mPlayerInfo.Flask = 2;
			_mCurState = eState::IDLE;
		}
	}

	///////////////////////////////////////
	void Player::UpdateState()
	{
		switch (_mCurState)
		{
		case sk::Player::eState::IDLE:
			_mCollider->SetSize(Vector2(50.0f, 140.0f));
			_mCollider->SetOffset(Vector2(0.0f, 185.0f));
			Idle();
			break;
		case sk::Player::eState::MOVE:
			Move();
			break;
		case sk::Player::eState::DODGE:
			_mCollider->SetSize(Vector2(70.0f, 70.0f));
			_mCollider->SetOffset(Vector2(0.0f, 220.0f));
			Dodge();
			break;
		case sk::Player::eState::ATTACK:
			Attack();
			break;
		case sk::Player::eState::ATTACKREADY:
			AttackReady();
			break;
		case sk::Player::eState::CROUCH:
			_mCollider->SetSize(Vector2(70.0f, 70.0f));
			_mCollider->SetOffset(Vector2(0.0f, 220.0f));
			Crouch();
			break;
		case sk::Player::eState::CROUCH_ATT:
			Crouch_Att();
			break;
		case sk::Player::eState::CROUCH_UP:
			Crouch_Up();
			break;
		case sk::Player::eState::PARRY:
			Parry();
			break;
		case sk::Player::eState::RUN_OFF:
			Run_Off();
			break;
		case sk::Player::eState::JUMP:
			Jump();
			break;
		case sk::Player::eState::RUN_JUMP:
			Run_Jump();
			break;
		case sk::Player::eState::JUMP_OFF:
			Jump_Off();
			break;
		case sk::Player::eState::JUMP_ATT:
			Jump_Att();
			break;
		case sk::Player::eState::FALL:
			Fall();
			break;
		case sk::Player::eState::FALL_MOVE:
			Fall_Move();
			break;
		case sk::Player::eState::CLIMB:
			Climb();
			break;
		case sk::Player::eState::HIT:
			Hit();
			break;
		case sk::Player::eState::RISING:
			Rising();
			break;
		case sk::Player::eState::CUTSCENE:
			CutScene();
			break;
		case sk::Player::eState::HEAL:
			Heal();
			break;
		case sk::Player::eState::CHARGEATT:
			ChargeAtt();
			break;
		case sk::Player::eState::PRAY:
			Pray();
			break;
		}
	}

	void Player::UpdateAnimation()
	{
		if (_mPrvState == _mCurState && _mPrvAttState == _mCurAttState && _mPrvDir ==_mDir && _mCurState !=eState::CLIMB)
		{
			return;
		}

		_mAttCount = 0;

		switch (_mCurState)
		{
		case sk::Player::eState::IDLE:
			if (_mAnimator->IsActiveAnimationComplete() && (_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Idle_right", true);
			else if (_mAnimator->IsActiveAnimationComplete() && (_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Idle_left", true);
			break;
		case sk::Player::eState::MOVE:
			if (_mDir == eDir::Right)
				_mAnimator->PlayAnimation(L"Run_right", true);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Run_left", true);
			break;
		case sk::Player::eState::DODGE:
			if (_mDir == eDir::Right)
			{
				Transform* tr = GetComponent<Transform>();
				DodgeEffect* dodgeeffect = object::Instantiate<DodgeEffect>(eLayerType::Effect, tr->GetPosition());
				dodgeeffect->PlayAnimation(_mDir);
				_mAnimator->PlayAnimation(L"Dodge_right", false);
			}
			else if ((_mDir == eDir::Left))
			{
				Transform* tr = GetComponent<Transform>();
				DodgeEffect* dodgeeffect = object::Instantiate<DodgeEffect>(eLayerType::Effect, tr->GetPosition());
				dodgeeffect->PlayAnimation(_mDir);
				_mAnimator->PlayAnimation(L"Dodge_left", false);
			}
			break;
		case sk::Player::eState::ATTACK:
			if (_mbCounter)
			{
				if (_mDir == eDir::Right)
					_mAnimator->PlayAnimation(L"Counter_right", false);
				else if ((_mDir == eDir::Left))
					_mAnimator->PlayAnimation(L"Counter_left", false);
			}
			else
			{
				if (_mHitCount == 0)
				{
					if (_mDir == eDir::Right)
						_mAnimator->PlayAnimation(L"Attack1_right", false);
					else if ((_mDir == eDir::Left))
						_mAnimator->PlayAnimation(L"Attack1_left", false);
				}
				else if (_mHitCount == 1)
				{
					if (_mDir == eDir::Right)
						_mAnimator->PlayAnimation(L"Attack2_right", false);
					else if ((_mDir == eDir::Left))
						_mAnimator->PlayAnimation(L"Attack2_left", false);
				}
				else if (_mHitCount == 2)
				{
					if (_mDir == eDir::Right)
						_mAnimator->PlayAnimation(L"Attack3_right", false);
					else if ((_mDir == eDir::Left))
						_mAnimator->PlayAnimation(L"Attack3_left", false);
				}
			}
			break;
		case sk::Player::eState::CROUCH:
			if (_mDir == eDir::Right)
				_mAnimator->PlayAnimation(L"Crouch_down_right", false);
			else if (_mDir == eDir::Left)
				_mAnimator->PlayAnimation(L"Crouch_down_left", false);

			if (_mPrvState == eState::DODGE)
			{
				_mAnimator->GetActiveAnime()->SetIndex(6);
			}
			// 앉은상태에서 방향전환
			if (_mPrvDir != _mDir)
			{
				_mAnimator->GetActiveAnime()->SetIndex(6);
			}
			// 공격후 앉은자세
			if (_mPrvState == eState::CROUCH_ATT)
			{
				_mAnimator->GetActiveAnime()->SetIndex(6);
			}
			break;
		case sk::Player::eState::CROUCH_ATT:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Crouch_attack_right", false);
			else if (_mDir == eDir::Left)
				_mAnimator->PlayAnimation(L"Crouch_attack_left", false);
			break;
		case sk::Player::eState::CROUCH_UP:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Crouch_Up_right", false);
			else if (_mDir == eDir::Left)
				_mAnimator->PlayAnimation(L"Crouch_Up_left", false);
			break;
		case sk::Player::eState::PARRY:
			if (_mDir == eDir::Right)
				_mAnimator->PlayAnimation(L"Parry_right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Parry_left", false);
			break;
		case sk::Player::eState::RUN_OFF:
			if (_mDir == eDir::Right)
				_mAnimator->PlayAnimation(L"Stop_run_right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Stop_run_left", false);
			break;
		case sk::Player::eState::JUMP:
			if (_mPrvDir != _mDir && _mPrvState == _mCurState)
			{
				if (Input::GetKeyDown(eKeyCode::A) && (_mDir == eDir::Right))
				{
					_mAnimator->PlayAnimation(L"Jump_left", false);
					_mAnimator->GetActiveAnime()->SetIndex(_mImgIdx);
				}
				else if (Input::GetKeyDown(eKeyCode::D) && (_mDir == eDir::Left))
				{
					_mAnimator->PlayAnimation(L"Jump_right", false);
					_mAnimator->GetActiveAnime()->SetIndex(_mImgIdx);
				}
			}
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Jump_right", false);
			else if (_mDir == eDir::Left)
				_mAnimator->PlayAnimation(L"Jump_left", false);
			break;
		case sk::Player::eState::RUN_JUMP:
			if (_mPrvDir != _mDir && _mPrvState == _mCurState)
			{
				if (Input::GetKeyDown(eKeyCode::A) && (_mDir == eDir::Right))
				{
					_mAnimator->PlayAnimation(L"Run_Jump_left", false);
					_mAnimator->GetActiveAnime()->SetIndex(_mImgIdx);
				}
				else if (Input::GetKeyDown(eKeyCode::D) && (_mDir == eDir::Left))
				{
					_mAnimator->PlayAnimation(L"Run_Jump_right", false);
					_mAnimator->GetActiveAnime()->SetIndex(_mImgIdx);
				}
			}
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Run_Jump_right", false);
			else if (_mDir == eDir::Left)
				_mAnimator->PlayAnimation(L"Run_Jump_left", false);
			break;
		case sk::Player::eState::JUMP_OFF:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Land_right", false);
			else if (_mDir == eDir::Left)
				_mAnimator->PlayAnimation(L"Land_left", false);
			break;
		case sk::Player::eState::JUMP_ATT:
			//_mImgIdx =_mAnimator->GetActiveAnime()->GetIndex();
			if (_mHitCount == 0)
			{
				if ((_mDir == eDir::Right))
					_mAnimator->PlayAnimation(L"Jump_Attack_right", false);
				else if (_mDir == eDir::Left)
					_mAnimator->PlayAnimation(L"Jump_Attack_left", false);
			}
			else if (_mHitCount == 1)
			{
				if ((_mDir == eDir::Right))
					_mAnimator->PlayAnimation(L"Jump_Attack2_right", false);
				else if (_mDir == eDir::Left)
					_mAnimator->PlayAnimation(L"Jump_Attack2_left", false);
			}
			break;
		case sk::Player::eState::FALL:
			if (_mPrvDir != _mDir && _mPrvState == _mCurState)
			{
				if (Input::GetKeyDown(eKeyCode::A) && (_mDir == eDir::Right))
				{
					_mAnimator->PlayAnimation(L"Jumploop_left", false);
					_mAnimator->GetActiveAnime()->SetIndex(_mImgIdx);
				}
				else if (Input::GetKeyDown(eKeyCode::D) && (_mDir == eDir::Left))
				{
					_mAnimator->PlayAnimation(L"Jumploop_right", false);
					_mAnimator->GetActiveAnime()->SetIndex(_mImgIdx);
				}
			}
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Jumploop_right", true);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Jumploop_left", true);
			break;
		case sk::Player::eState::FALL_MOVE:
			if (_mPrvDir != _mDir && _mPrvState == _mCurState)
			{
				if (Input::GetKeyDown(eKeyCode::A) && (_mDir == eDir::Right))
				{
					_mAnimator->PlayAnimation(L"Run_Fall_right", false);
					_mAnimator->GetActiveAnime()->SetIndex(_mImgIdx);
				}
				else if (Input::GetKeyDown(eKeyCode::D) && (_mDir == eDir::Left))
				{
					_mAnimator->PlayAnimation(L"Run_Fall_left", false);
					_mAnimator->GetActiveAnime()->SetIndex(_mImgIdx);
				}
			}
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Run_Fall_right", true);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Run_Fall_left", true);
			break;
		case sk::Player::eState::CLIMB:
			if (_mPrvState != eState::CLIMB )
			{
				_mAnimator->PlayAnimation(L"Climb_Ladder", false);
			}
			break;
		case sk::Player::eState::HEAL:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Healing_right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Healing_left", false);
			break;
		case sk::Player::eState::CHARGEATT:
			if ((_mDir == eDir::Right))
				_mAnimator->PlayAnimation(L"Charge_Att_Right", false);
			else if ((_mDir == eDir::Left))
				_mAnimator->PlayAnimation(L"Charge_Att_Left", false);
			break;
		//case sk::Player::eState::HIT:
		//	break;
		}
	}


	void Player::OnCollisionEnter(Collider* other)
	{
		MonsterAttack* monatt = dynamic_cast<MonsterAttack*>(other->GetOwner());

		if (monatt != nullptr)
		{
			Vector2 velocity = _mRigidbody->GetVelocity();

			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			if (_mbDefendOn)
			{
				_mbCounter = true;
				if (_mDir == eDir::Right)
				{
					_mAnimator->PlayAnimation(L"ParrySuccess_right");
					if (monatt->GetMonsType() == Monster::eMonsType::LionHead)
					{
						velocity.x = -600.f;
					}
					else
						pos.x -= 5.f;
				}
				else if (_mDir == eDir::Left)
				{
					_mAnimator->PlayAnimation(L"ParrySuccess_left");
					if (monatt->GetMonsType() == Monster::eMonsType::LionHead)
					{
						velocity.x = 600.f;
					}
					else
						pos.x += 5.f;
				}
				_mRigidbody->SetVelocity(velocity);
				tr->SetPosition(pos);
				_mbDefendOn = false;
			}

			if (_mCurState != eState::PARRY && _mCurState != eState::DODGE && _mCurState != eState::HIT)
			{
				_mCurState = eState::HIT;
				_mRigidbody->SetGround(false);
				PlayerHit* phiteffect = object::Instantiate<PlayerHit>(eLayerType::Effect, tr->GetPosition());
				if (monatt->GetDir() == eDir::Left)
				{
					_mDir = eDir::Right;
					velocity.x = -350.0f;
					velocity.y = -350.0f;
					_mRigidbody->SetVelocity(velocity);
					phiteffect->PlayAnimation(eDir::Right);
					_mAnimator->PlayAnimation(L"PlayerHit_right", false);
				}
				else if (monatt->GetDir() == eDir::Right)
				{
					_mDir = eDir::Left;
					velocity.x = 350.0f;
					velocity.y = -350.0f;
					_mRigidbody->SetVelocity(velocity);
					phiteffect->PlayAnimation(eDir::Left);
					_mAnimator->PlayAnimation(L"PlayerHit_left", false);
				}
			}
		}
		// 충돌시 동작
	}

	void Player::OnCollisionStay(Collider* other)
	{
		// 총돌 도중 동작
	}

	void Player::OnCollisionExit(Collider* other)
	{
		// 충돌 빠져나올시 동작
	}
}