#include "skElderWaveMgr.h"
#include "skElderBrother.h"
#include "skElderCorpseEff.h"
#include "skObject.h"
#include "skTransform.h"
#include "skElderWave.h"
#include "skResources.h"
#include "skTexture.h"
#include "skTimeMgr.h"

namespace sk
{
	ElderWaveMgr::ElderWaveMgr() :
		_mPos(Vector2::Zero)
		, _mLeft(false)
		, _mCount(0)
		, _mTime(1.f)
	{
	}
	ElderWaveMgr::~ElderWaveMgr()
	{
	}
	void ElderWaveMgr::Initialize()
	{
	}
	void ElderWaveMgr::Update()
	{
		GameObject::Update();

		_mTime += TimeMgr::DeltaTime();
		if (_mCount == 6)
		{
			if (_mTime > 1.2f)
			{
				Destroy(this);
			}
		}
		if (_mCount!= 6)
		{
			if (_mTime > 0.25f)  // png¿œΩ√ 0.35
			{
				_mTime = 0.0f;
				PlayAnimation(_mCount);
			}
		}
		
	}

	void ElderWaveMgr::PlayAnimation(int cnt)
	{
		if (_mLeft)
		{
			ElderWave* wave = object::Instantiate<ElderWave>(eLayerType::MonsAtt, Vector2(_mPos.x - (160.f + cnt * xlength), _mPos.y + 60.f));
			wave->_mFloorTexture = Resources::Find<Texture>(L"bossfloor");
			ElderCorpseEff* CorpseEff = object::Instantiate<ElderCorpseEff>(eLayerType::Effect, Vector2(_mPos.x -(160.f + cnt * xlength), _mPos.y + 80.f));
			CorpseEff->PlayAnimation(true);
			ElderWave* wave2 = object::Instantiate<ElderWave>(eLayerType::MonsAtt, Vector2(_mPos.x - (230.f + cnt * xlength), _mPos.y + 60.f));
			wave2->_mFloorTexture = Resources::Find<Texture>(L"bossfloor");
			ElderCorpseEff* CorpseEff2 = object::Instantiate<ElderCorpseEff>(eLayerType::Effect, Vector2(_mPos.x - (230.f + cnt * xlength), _mPos.y + 50.f));
			CorpseEff2->PlayAnimation();
		}
		else
		{
			ElderWave* wave = object::Instantiate<ElderWave>(eLayerType::MonsAtt, Vector2(_mPos.x + (160.f + cnt * xlength), _mPos.y + 60.f));
			wave->_mFloorTexture = Resources::Find<Texture>(L"bossfloor");
			ElderCorpseEff* CorpseEff = object::Instantiate<ElderCorpseEff>(eLayerType::Effect, Vector2(_mPos.x + (160.f + cnt * xlength), _mPos.y + 80.f));
			CorpseEff->PlayAnimation();
			ElderWave* wave2 = object::Instantiate<ElderWave>(eLayerType::MonsAtt, Vector2(_mPos.x + (230.f + cnt * xlength), _mPos.y + 60.f));
			wave2->_mFloorTexture = Resources::Find<Texture>(L"bossfloor");
			ElderCorpseEff* CorpseEff2 = object::Instantiate<ElderCorpseEff>(eLayerType::Effect, Vector2(_mPos.x + (230.f + cnt * xlength), _mPos.y + 50.f));
			CorpseEff2->PlayAnimation(true);
		}
		_mCount++;
	}

	void ElderWaveMgr::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}