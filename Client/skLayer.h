#pragma once
#include "skEntity.h"
#include "skGameObject.h"


namespace sk
{
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void AddGameObject(GameObject* gameObj)
		{
			_mGameObjects.push_back(gameObj);
		}

		std::vector<GameObject*>& GetGameObjects() { return _mGameObjects; }

	private:
		std::vector<GameObject*> _mGameObjects;
	};
}

