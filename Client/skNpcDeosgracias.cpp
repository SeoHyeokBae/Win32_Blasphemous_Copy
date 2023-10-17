#include "skNpcDeosgracias.h"
#include "skResources.h"
#include "skAnimator.h"
#include "skCollisionMgr.h"
#include "skPlayer.h"
#include "skTransform.h"
#include "skGuideBotton.h"
#include "skObject.h"
#include "skInput.h"
#include "skSkillBook.h"


namespace sk
{
	bool NpcDeosgracias::_mCanActive = false;
	NpcDeosgracias::NpcDeosgracias()
		: _mPlayer(nullptr)
	{
	}
	NpcDeosgracias::~NpcDeosgracias()
	{
	}
	void NpcDeosgracias::Initialize()
	{
		Animator* ani = AddComponent<Animator>();
		Collider* col = AddComponent<Collider>();

		Texture* Deosgracias = Resources::Load<Texture>(L"Deosgracias", L"..\\Resources\\image\\npc\\Deosgracias_idle.bmp");

		ani->CreateAnimation(L"Deosgracias_idle", Deosgracias, Vector2(0.0f, 0.0f), Vector2(256.f, 512.f), 19, Vector2(0.0f, 0.0f), 0.1f);

		ani->PlayAnimation(L"Deosgracias_idle", true);

		col->SetSize(Vector2(400.0f, 200.0f));
		col->SetOffset(Vector2(-100.0f, 75.0f));

	}
	void NpcDeosgracias::Update()
	{
		GameObject::Update();

		if (_mCanActive)
		{
			_mCanActive = false;
			_mPlayer->Active();
			_mPlayer->SetCargeAtt(true);
		}
	}
	void NpcDeosgracias::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void NpcDeosgracias::OnCollisionEnter(Collider* other)
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
				buttontr->SetPosition(Vector2(1250.0f, 375.0f));
			}
		}
	}
	void NpcDeosgracias::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			_mPlayer = player;
			Transform* tr = player->GetComponent<Transform>();

			float len = fabs(other->GetPosition().x - this->GetComponent<Collider>()->GetPosition().x);
			float scale = fabs(other->GetSize().x / 2.0f + this->GetComponent<Collider>()->GetSize().x / 2.0f);

			if (len < scale)
			{
				if (Input::GetKeyDown(eKeyCode::E))
				{
					SkillBook* skill = object::Instantiate<SkillBook>(eLayerType::UI);
					Transform* skilltr = skill->GetComponent<Transform>();
					skilltr->SetPosition(Vector2(640.f, 360.0f));
					player->Pause();
				}
			}
		}
	}
	void NpcDeosgracias::OnCollisionExit(Collider* other)
	{
	}
}