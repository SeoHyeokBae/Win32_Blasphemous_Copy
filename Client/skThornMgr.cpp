#include "skThornMgr.h"
#include "skObject.h"
#include "skTransform.h"
#include "skResources.h"
#include "skTexture.h"
#include "skTimeMgr.h"
#include "skThorn.h"

namespace sk
{
	ThornMgr::ThornMgr() :
		_mPos(Vector2::Zero)
		, _mLeft(false)
		, _mCount(0)
		, _mTime(1.f)
		, _mbPhase2(false)
		, _mType(eAttType::None)
	{
	}
	ThornMgr::~ThornMgr()
	{
	}
	void ThornMgr::Initialize()
	{
	}
	void ThornMgr::Update()
	{
		GameObject::Update();

		_mTime += TimeMgr::DeltaTime();
		if (_mType == eAttType::Stomp)
		{
			Stomp();
		}
		else if (_mType == eAttType::Smash)
		{
			Smash();
		}

	}

	void ThornMgr::PlayAnimation(int cnt)
	{
		if (_mLeft)
		{
			Thorn* thorn = object::Instantiate<Thorn>(eLayerType::Projectile, Vector2(_mPos.x - (160.f + cnt * Thorn_length), _mPos.y + 75.f));
		}
		else
		{
			Thorn* thorn = object::Instantiate<Thorn>(eLayerType::Projectile, Vector2(_mPos.x + (160.f + cnt * Thorn_length), _mPos.y + 75.f));
		}
		_mCount++;
	}

	void ThornMgr::Stomp()
	{
		if (_mbPhase2)
		{
			if (_mCount == 3)
			{
				if (_mTime > 1.2f)
					Destroy(this);
			}
			if (_mCount != 3)
			{
				if (_mTime > 0.25f)  // png老矫 0.35
				{
					_mTime = 0.0f;
					PlayAnimation(_mCount);
				}
			}
		}
		else
		{
			if (_mCount == 1)
			{
				if (_mTime > 1.2f)
					Destroy(this);
			}
			if (_mCount != 1)
			{
				if (_mTime > 0.25f)  // png老矫 0.35
				{
					_mTime = 0.0f;
					PlayAnimation(_mCount);
				}
			}
		}
	}

	void ThornMgr::Smash()
	{
		if (_mbPhase2)
		{
			if (_mCount == 5)
			{
				if (_mTime > 1.2f)
					Destroy(this);
			}
			if (_mCount != 5)
			{
				if (_mTime > 0.25f)  // png老矫 0.35
				{
					_mTime = 0.0f;
					PlayAnimation(_mCount);
				}
			}
		}
		else
		{
			if (_mCount == 3)
			{
				if (_mTime > 1.2f)
					Destroy(this);
			}
			if (_mCount != 3)
			{
				if (_mTime > 0.25f)  // png老矫 0.35
				{
					_mTime = 0.0f;
					PlayAnimation(_mCount);
				}
			}
		}
	}

	void ThornMgr::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}