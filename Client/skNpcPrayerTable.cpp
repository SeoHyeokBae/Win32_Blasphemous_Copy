#include "skNpcPrayerTable.h"
#include "skResources.h"
#include "skAnimator.h"
#include "skCollisionMgr.h"
#include "skSpriteRenderer.h"
#include "skPlayer.h"
#include "skTransform.h"
#include "skGuideBotton.h"
#include "skObject.h"
#include "skInput.h"
#include "skTimeMgr.h"

namespace sk
{
	NpcPrayerTable::NpcPrayerTable() :
		_mAnimator(nullptr)
		,_mTime(0.f)
		, _mbCanLight(false)
	{
	}
	NpcPrayerTable::~NpcPrayerTable()
	{
	}
	void NpcPrayerTable::Initialize()
	{
		_mAnimator= AddComponent<Animator>();
		SpriteRenderer* sr = AddComponent<SpriteRenderer>();
		Collider* col = AddComponent<Collider>();

		Texture* PrayerTable = Resources::Load<Texture>(L"PrayerTable", L"..\\Resources\\image\\npc\\priedieu_stand_and_liton_anim.bmp");
		Texture* PrayerTable0 = Resources::Load<Texture>(L"PrayerTable0", L"..\\Resources\\image\\npc\\priedieu_stand_and_liton_anim0.bmp");

		sr->SetImage(PrayerTable0);
		sr->SetScale(Vector2(2.0f, 2.0f));

		col->SetSize(Vector2(500.0f, 200.0f));
		col->SetOffset(Vector2(0.0f, 0.0f));

		_mAnimator->CreateAnimation(L"PrayerTable", PrayerTable, Vector2(0.0f, 0.0f), Vector2(66.f, 145.f), 6, Vector2(0.0f, 0.0f), 0.08f);
		_mAnimator->SetScale(Vector2(2.0f, 2.0f));
	}
	void NpcPrayerTable::Update()
	{
		GameObject::Update();

		if (_mbCanLight)
		{
			_mTime += TimeMgr::DeltaTime();
			if (_mTime > 1.7f)
			{
				_mbCanLight = false;
				SpriteRenderer* sr = GetComponent<SpriteRenderer>();
				sr->SetImage(nullptr);
				_mAnimator->PlayAnimation(L"PrayerTable", true);
			}
		}
	}
	void NpcPrayerTable::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void NpcPrayerTable::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Transform* tr = player->GetComponent<Transform>();

			float len = fabs(other->GetPosition().x - this->GetComponent<Collider>()->GetPosition().x);
			float scale = fabs(other->GetSize().x / 2.0f + this->GetComponent<Collider>()->GetSize().x / 2.0f);

			if (len < scale)
			{
				GuideBotton* PrssE = object::Instantiate<GuideBotton>(eLayerType::UI);
				Transform* buttontr = PrssE->GetComponent<Transform>();
				buttontr->SetPosition(Vector2(2050.0f, 375.0f));
			}
		}
	}
	void NpcPrayerTable::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Transform* tr = player->GetComponent<Transform>();

			float len = fabs(other->GetPosition().x - this->GetComponent<Collider>()->GetPosition().x);
			float scale = fabs(other->GetSize().x / 2.0f + this->GetComponent<Collider>()->GetSize().x / 2.0f);

			if (len < scale)
			{
				if (Input::GetKeyDown(eKeyCode::E))
				{

					player->GetComponent<Animator>()->PlayAnimation(L"pray", false);
					player->SetState(Player::eState::PRAY);

					_mbCanLight = true;
				}
			}
		}
	}
	void NpcPrayerTable::OnCollisionExit(Collider* other)
	{
	}
}