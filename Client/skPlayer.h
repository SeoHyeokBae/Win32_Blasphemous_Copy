#pragma once
#include"skGameObject.h"

namespace sk
{
	class Animator;
	class Rigidbody;
	class Collider;

	class Player : public GameObject
	{
	public:
		enum class eState
		{
			IDLE,
			MOVE,
			DODGE,
			ATTACK,
			ATTACKREADY,
			CROUCH,
			CROUCH_ATT,
			CROUCH_UP,
			RUN_OFF,
			PARRY,
			JUMP,
			RUN_JUMP,
			JUMP_OFF,
			JUMP_ATT,
			FALL,
			FALL_MOVE,
			CLIMB,
			HIT,
			HEAL,
			RISING,
			CUTSCENE,
			NONE
		};

		enum class eAttState
		{
			FIRST_SLASH,
			SECOND_SLASH,
			THIRD_SLASH,
			JUMP_FIRST_SLASH,
			JUMP_SECOND_SLASH,
			CROUCH_SLASH,
			COUNTER_SLASH,
			NONE,
		};

		struct Info
		{
			int Hp;
			int Dmg;
		};

		Player();
		virtual ~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void InitAnimation();
		void UpdateAnimation();
		void UpdateState();
		void PixelCollision();

		void Idle();
		void Move();
		void Dodge();
		void Attack();
		void AttackReady();
		void Crouch();
		void Crouch_Att();
		void Crouch_Up();
		void Run_Off();
		void Run_Jump();
		void Parry();
		void Jump();
		void Jump_Off();
		void Jump_Att();
		void Fall();
		void Fall_Move();
		void Climb();
		void Hit();
		void Heal();
		void Rising();
		void CutScene();

		void SetState(eState state){ _mCurState = state; }
		eState GetState() { return _mCurState; }
		eAttState GetAttState() { return _mCurAttState; }
		eDir GetDir() { return _mDir; }
		eDir GetPrvDir() { return _mPrvDir; }

		void SetCanClimb(bool climb) { _mbCanClimb = climb; }
		bool GetCanClimb() { return _mbCanClimb; }

		void SetDefendOn(bool enable) { _mbDefendOn = enable; }
		bool GetDefendOn() { return _mbDefendOn; }

		void SetCanDown(bool down) { _mbCanDown = down; }

		void SetAttCount(UINT count) { _mHitCount = count; }
		UINT GetAttCount() { return _mHitCount; }

		class Texture* _mFloorTexture;

		static Info GetInfo() { return _mPlayerInfo; }
		static math::Vector2 GetPlayerPos() { return _mPlayerPos; }
		static void SetAttSuccess(bool success) { _mbAttSuccess = success; }
		static bool GetAttSuccess() { return _mbAttSuccess; }
	private:
		static math::Vector2 _mPlayerPos;
		static Info _mPlayerInfo;
		static bool _mbAttSuccess;

		Animator* _mAnimator;
		Rigidbody* _mRigidbody;
		Collider* _mCollider;

		eState _mCurState;
		eState _mPrvState;
		eAttState _mCurAttState;
		eAttState _mPrvAttState;
		eDir _mDir;
		eDir _mPrvDir;
		float _mAttTime;
		float _mAttDelay;
		bool _mbCanClimb;
		bool _mbCanDown;
		bool _mbCanIgnore;
		bool _mbDefendOn;
		bool _mbCounter;
		bool _mbCanAtt;
		bool _mbCanEff;

		UINT _mHitCount;
		UINT _mAttCount;
		UINT _mImgIdx;
	};
} 


