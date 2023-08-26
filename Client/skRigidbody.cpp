#include "skRigidbody.h"
#include "skTimeMgr.h"
#include "skGameObject.h"
#include "skTransform.h"

namespace sk
{
	Rigidbody::Rigidbody()
		:Component(eComponentType::Rigidbody)
		, _mMass(1.0f)
		, _mFriction(850.0f)
		, _mbGround(false)
	{
		_mLimitedVelocity.x = 500.0f;
		_mLimitedVelocity.y = 5000.0f;
		_mGravity = Vector2(0.0f, 1500.0f);
	}
	Rigidbody::~Rigidbody()
	{
	}
	void Rigidbody::Initialize()
	{
	}
	void Rigidbody::Update()
	{
		//F= ma
		_mAccelation = _mForce / _mMass;
		
		// 속도에 가속도를 더해줘야 총속도
		_mVelocity += _mAccelation * TimeMgr::DeltaTime();

		if (_mbGround)
		{
			// 땅에 붙어있을때
			Vector2 gravity = _mGravity;
			gravity.normalize();
			float dot = sk::math::Dot(_mVelocity, gravity);	// 방향과 중력 사이 내적
			_mVelocity -= gravity * dot;
		}
		else
		{
			// 공중에 있을 때
			_mVelocity += _mGravity * TimeMgr::DeltaTime();
		}

		/////////////////////////////////////////////////////////////
		// 최대 속도제한
		Vector2 gravity = _mGravity;
		gravity.normalize();
		float dot = sk::math::Dot(_mVelocity, gravity);
		gravity = gravity * dot;

		Vector2 sideVelocity = _mVelocity - gravity;
		if (_mLimitedVelocity.y < gravity.length())
		{
			gravity.normalize();
			gravity *= _mLimitedVelocity.y;
		}
		
		if (_mLimitedVelocity.x < sideVelocity.length())
		{
			sideVelocity.normalize();
			sideVelocity *= _mLimitedVelocity.x;
		}
		_mVelocity = gravity + sideVelocity;


		if (!(_mVelocity == Vector2::Zero))
		{
			// 속도에 반대 방향으로 마찰력 적용
			Vector2 friction = - _mVelocity;
			friction = friction.normalize() * _mFriction * _mMass * TimeMgr::DeltaTime();

			// 마찰력으로 의한 속도 감소량이 현재 속도보다 큰 경우

			if (_mVelocity.length() < friction.length())
			{
				// 멈춤
				_mVelocity = Vector2(0.f,0.f);
			}
			else
			{
				// 마찰력으로 속도 차감
				_mVelocity += friction;
			}
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos = pos + _mVelocity * TimeMgr::DeltaTime();
		tr->SetPosition(pos);
		_mForce.clear();
	}
	void Rigidbody::Render(HDC hdc)
	{
	}
}