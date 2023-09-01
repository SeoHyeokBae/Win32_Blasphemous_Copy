#pragma once
#include "CommonInclude.h"
#include "skGameObject.h"

namespace sk
{
	using namespace math;
	class Camera
	{
	public:
		static void Initialize();
		static void Update();

		// 카메라가 위치한만큼 화면안의 다른 오브젝트들의 상대위치를 위한 계산 
		//static Vector2 CalculatePosition(Vector2 pos) { return pos - _mDistance; }
		static Vector2 CalculatePosition(Vector2 pos,Vector2 CameraRatio = Vector2::One) { return pos - (_mDistance / CameraRatio); }

		static GameObject* GetTarget() { return _mTarget; }
		static void SetTarget(GameObject* target) { _mTarget = target; }

		static void SetLookPos(Vector2 look) { _mTargetPosition = look; }
		static void SetLookPosTime(Vector2 look)	// 목표지점까지 시간대로 이동하기위함
		{
			_mTargetPosition = look;
			float MovDistance = (_mTargetPosition - _mPrvLookPosition).length();
			_mSpeed = MovDistance / _mTime;
			_mAccTime = 0.f;
		}
		static void SetPrvLookPos(Vector2 look) { _mPrvLookPosition = look; } // 이전위치 저장

		static Vector2 GetLookPos() { return _mLookPosition; }
		static Vector2 GetPrvLookPos() { return _mPrvLookPosition; }
		static void SetCameraLimit_Right(float right) { _mLimitRightX = right; }
		static void SetCameraLimit_Left(float left) { _mLimitLeftX = left; }
		static void SetCameraLimit_Y(float y) { _mLimitY = y; }
		
		static void SetPlayMode(bool on) { _mbPlayMode = on; }
		static void SetCutSceneMode(bool on) { _mbCutSceneMode = on; }
		static bool GetColliderRender() { return _mbCollider; }

	private:
		static Vector2 _mResolution;
		static Vector2 _mLookPosition;	 // 카메라 바라보고 있는 위치
		static Vector2 _mTargetPosition;	// 카메라 타겟 위치
		static Vector2 _mPrvLookPosition;	// 카메라 이전위치
		static Vector2 _mDistance;		// 해상도 가운데 좌표와 카메라가 보는좌표의 거리
		static GameObject* _mTarget;	/// 카메라가 바라보는 게임 오브젝트
		
		static float _mLimitRightX;
		static float _mLimitLeftX;
		static float _mTime;
		static float _mAccTime;
		static float _mSpeed;
		static float _mLimitY;
		static bool _mbPlayMode;
		static bool _mbCutSceneMode;
		static bool _mbCollider;
	};

}

