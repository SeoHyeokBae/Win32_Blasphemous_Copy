#pragma once
#include "skEntity.h"
#include "skLayer.h"


namespace sk
{
	using namespace sk::enums;
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		void BackGroundRender(HDC hdc);

		virtual void SceneEnter();
		virtual void SceneOut();

		void AddGameObject(eLayerType type, GameObject* gameObj)
		{
			_mLayers[(int)type].AddGameObject(gameObj);
		}

		Layer& GetLayer(eLayerType type) { return _mLayers[(UINT)type]; }

	public:
		std::vector<Layer> _mLayers;
	};

}

