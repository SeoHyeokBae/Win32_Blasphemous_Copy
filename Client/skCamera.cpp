#include "skCamera.h"
#include "skApplication.h"
#include "skTransform.h"
#include "skInput.h"
#include "skTimeMgr.h"
#include "skComponent.h"

extern sk::Application application;

namespace sk
{
	Vector2 Camera::_mResolution = Vector2::Zero;
	Vector2 Camera::_mLookPosition = Vector2::Zero;
	Vector2 Camera::_mTargetPosition = Vector2::Zero;
	Vector2 Camera::_mPrvLookPosition = Vector2::Zero;
	Vector2 Camera::_mDistance = Vector2::Zero;
	GameObject* Camera::_mTarget = nullptr;
	bool Camera::_mbCollider = false;

	float Camera::_mLimitLeftX = 0.f;
	float Camera::_mLimitRightX = 0.f;
	float Camera::_mLimitY = 0.f;
	bool Camera::_mbPlayMode = false;
	bool Camera::_mbCutSceneMode = false;
	float Camera::_mTime = 2.0f;
	float Camera::_mAccTime = 0.f;
	float Camera::_mSpeed = 0.f;
	float Camera::_mfDuration= 0.f;
	float Camera::_mfShakeAccTime= 0.f;
	float Camera::_mfShakeIntensity= 0.f;
	bool Camera::_mbShake = false;

	void Camera::Initialize()
	{
		_mResolution.x = application.GetWidth();
		_mResolution.y = application.GetHeight();
		_mLookPosition = _mResolution / 2.0f;
	}
	void Camera::Update()
	{
		if (Input::GetKeyDown(eKeyCode::O))
		{
			_mbCollider = true;
		}
		if (Input::GetKeyUp(eKeyCode::O))
		{
			_mbCollider = false;
		}

		 
		if (_mTarget)
		{
			Transform* tr = _mTarget->GetComponent<Transform>();
			Vector2 Pos = tr->GetPosition();

			if (_mbPlayMode)
			{
				if (Pos.x - 640.f < _mLimitLeftX)
					_mLookPosition = (Vector2(_mLimitLeftX + 640.f, 360.f));
				else if (Pos.x + 640.f > _mLimitRightX)
					_mLookPosition = (Vector2(_mLimitRightX - 640.f, 360.f));
				else
					_mLookPosition = (Vector2(Pos.x, 360.0f));
			}
			else
			{
				if (Pos.x < _mLimitLeftX + 640.f)
				{
					if (Pos.y < 360.f)
					{
						_mLookPosition = Vector2(_mLimitLeftX + 640.f, 360.f);
					}
					else if (_mLimitY != 0 && Pos.y > _mLimitY)
					{
						_mLookPosition = Vector2(Pos.x, _mLimitY);
					}
					else
						_mLookPosition = Vector2(_mLimitLeftX + 640.f, Pos.y);
				}
				else if (Pos.x > _mLimitRightX - 640.f)
				{
					if (Pos.y < 360.f)
					{
						_mLookPosition = Vector2(_mLimitRightX - 640.f, 360.f);
					}
					else if (_mLimitY != 0 && Pos.y > _mLimitY)
					{
						_mLookPosition = Vector2(Pos.x, _mLimitY);
					}
					else
						_mLookPosition = Vector2(_mLimitRightX - 640.f, Pos.y);
				}
				else
				{
					if (Pos.y < 360.f)
					{
						_mLookPosition = Vector2(Pos.x, 360.f);
					}
					else if (_mLimitY != 0 && Pos.y > _mLimitY)
					{
						_mLookPosition = Vector2(Pos.x, _mLimitY);
					}
					else
						_mLookPosition = Pos;  
				}
			}
		}

		if (_mbShake)
		{
			_mfShakeAccTime += TimeMgr::DeltaTime();
			if (_mfDuration <= _mfShakeAccTime)
			{
				_mbShake = false;
				_mfShakeIntensity = 0.f;
				if(!_mbCutSceneMode)
					_mTargetPosition = Vector2(0.f, 0.f);
			}
			else
			{
				float offsetX = (rand() % 100 - 50) * _mfShakeIntensity;
				float offsetY = (rand() % 10 - 5) * _mfShakeIntensity;

				_mTargetPosition.x = _mLookPosition.x + offsetX;
				_mTargetPosition.y = _mLookPosition.y + offsetY;

				_mLookPosition.x = _mLookPosition.x + 0.5f * (_mTargetPosition.x - _mLookPosition.x );
				_mLookPosition.y = _mLookPosition.y + 0.5f * (_mTargetPosition.y - _mLookPosition.y );
			}
		}


		// ÄÆ¾À¸ðµå
		if (_mbCutSceneMode)
		{
			_mAccTime += TimeMgr::DeltaTime();
			if (_mTime <=_mAccTime)
			{
				_mLookPosition = _mTargetPosition;
			}
			else
			{
				Vector2 LookDir = _mTargetPosition - _mPrvLookPosition;
				_mPrvLookPosition += LookDir.normalize() * _mSpeed * TimeMgr::DeltaTime();
				_mLookPosition = _mPrvLookPosition;
			}
		}
		
		_mDistance = _mLookPosition - (_mResolution / 2.0f);
	}
}