#pragma once
#include "skComponent.h"


namespace sk
{
	using namespace math;
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		
		void AddForce(Vector2 force) { _mForce += force; }
		void SetMass(float mass) { _mMass = mass; }
		void SetGround(bool ground) { _mbGround = ground; }
		bool GetGround() { return _mbGround; }
		Vector2 GetVelocity() { return _mVelocity; }
		void SetVelocity(Vector2 velocity) { _mVelocity = velocity; }
		void SetGravity(Vector2 gravity) { _mGravity = gravity; }
		Vector2 GetGravity() { return _mGravity; }
		void SetLimitedX(float velocity) { _mLimitedVelocity.x = velocity; }


	private:
		float _mMass;

		float _mFriction;				// 마찰력
		//float _mStarticFriction;		// 정지마찰력
		//float _mKineticFriction;		// 운동마찰력
		//float _mCoefficentFriction;	// 물체각고유

		Vector2 _mForce;
		Vector2 _mAccelation;
		Vector2 _mVelocity;
		Vector2 _mGravity;
		Vector2 _mLimitedVelocity;

		bool _mbGround;
	};
}


