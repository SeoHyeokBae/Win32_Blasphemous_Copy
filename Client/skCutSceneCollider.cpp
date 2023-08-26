#include "skCutSceneCollider.h"
#include "skPlayer.h"
#include "skCollider.h"
#include "skRigidbody.h"
#include "skTransform.h"
#include "skSceneMgr.h"
#include "skTimeMgr.h"
#include "skCamera.h"
#include "skInput.h"
#include"skSceneMgr.h"
#include "skElderBroPrivateCutScene.h"
#include "skAnimator.h"

#include "skFirstBossScene.h"

namespace sk
{
	CutSceneCollider::CutSceneCollider()
		: _mTime(0.f)
		, _mPlayer(nullptr)
		, _mStart(false)
	{
	}
	CutSceneCollider::~CutSceneCollider()
	{
	}
	void CutSceneCollider::Initialize()
	{
	}
	void CutSceneCollider::Update()
	{
		GameObject::Update();

		if (_mStart)
		{
			_mTime += TimeMgr::DeltaTime();
		}

		if (_mTime > 6.0f)
		{
			if (_mPlayer != nullptr)
			{
				_mPlayer->SetState(Player::eState::IDLE);
			}

			Destroy(this);
		}
	}
	void CutSceneCollider::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


	void CutSceneCollider::PlayFirstBossScene()
	{
		Camera::SetTarget(nullptr);						// 카메라 고정 해제
		Camera::SetPrvLookPos(Camera::GetLookPos());	// 카메라 현위치 저장
		FirstBossScene::_mbCutSceneOn = true;			// 씬에서 컷씬 모드
		Camera::SetLookPosTime(Vector2(1420.f, 360.f));	// 컷씬 타겟지점까지 카메라이동 계산
		Camera::SetCutSceneMode(true);					// 카메라에서 컷씬 모드 적용
		ElderBroPrivateCutScene::SetCanPlay(true);		// 컷신 오브젝트 play
	}


	void CutSceneCollider::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		_mPlayer = player;

		_mStart = true;

		if (player != nullptr)
		{
			Transform* tr = player->GetComponent<Transform>();

			float len = fabs(other->GetPosition().x - this->GetComponent<Collider>()->GetPosition().x);
			float scale = fabs(other->GetSize().x / 2.0f + this->GetComponent<Collider>()->GetSize().x / 2.0f);

			if (len < scale)
			{
				Vector2 playerPos = tr->GetPosition();
				playerPos.x -= (scale - len) + 1.f;
				tr->SetPosition(playerPos);
			}

			if (SceneMgr::GetActiveScene()->GetName() == L"FirstBossScene")
			{
				// TODO
				player->GetComponent<Animator>()->PlayAnimation(L"Idle_right", true);
				player->SetState(Player::eState::CUTSCENE);
				PlayFirstBossScene();
			}
		}
	}
	void CutSceneCollider::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Transform* tr = player->GetComponent<Transform>();

			float len = fabs(other->GetPosition().x - this->GetComponent<Collider>()->GetPosition().x);
			float scale = fabs(other->GetSize().x / 2.0f + this->GetComponent<Collider>()->GetSize().x / 2.0f);

			if (len < scale)
			{
				Vector2 playerPos = tr->GetPosition();
				playerPos.x -= (scale - len) + 1.f;
				tr->SetPosition(playerPos);
			}
			player->GetComponent<Animator>()->PlayAnimation(L"Idle_right",true);
			
		}
	}
	void CutSceneCollider::OnCollisionExit(Collider* other)
	{
	}
}

