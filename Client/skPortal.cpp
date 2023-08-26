#include "skPortal.h"
#include "skPlayer.h"
#include "skCollider.h"
#include "skRigidbody.h"
#include "skTransform.h"
#include "skSceneMgr.h"
#include "skTimeMgr.h"
#include "skCamera.h"
#include "skInput.h"
#include"skSceneMgr.h"

namespace sk
{
	Portal::Portal()
		: _mTime(0.f)
	{
	}
	Portal::~Portal()
	{
	}
	void Portal::Initialize()
	{
	}
	void Portal::Update()
	{
		GameObject::Update();
	}
	void Portal::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


	void Portal::OnCollisionEnter(Collider* other)
	{
	}
	void Portal::OnCollisionStay(Collider* other)
	{
		
		if (Input::GetKey(eKeyCode::D) || Input::GetKey(eKeyCode::A))
		{
			_mTime += TimeMgr::DeltaTime();
			if (_mTime >= 0.5f)
			{
				_mTime = 0.0f;
				Camera::SetTarget(nullptr);
				Camera::Initialize();
				if (SceneMgr::GetActiveScene()->GetName() == L"PlayScene1")
				{
					SceneMgr::LoadScene(L"TutorialScene");
				}
				else if (SceneMgr::GetActiveScene()->GetName() == L"TutorialScene")
				{
					SceneMgr::LoadScene(L"FirstBossScene");
				}
				//else if (SceneMgr::GetActiveScene()->GetName() == L"PlayScene1")
				//{

				//}
			}
		}

	}
	void Portal::OnCollisionExit(Collider* other)
	{
	}
}