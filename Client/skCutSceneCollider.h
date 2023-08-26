#pragma once
#include "skGameObject.h"

namespace sk
{
	class Player;
	class CutSceneCollider : public GameObject
	{
	public:
		CutSceneCollider();
		virtual ~CutSceneCollider();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		class ElderBroPrivateCutScene* _mElderBroCutScene;

		void PlayFirstBossScene();

	private:
		float _mTime;
		Player* _mPlayer;
		bool _mStart;
	};
}