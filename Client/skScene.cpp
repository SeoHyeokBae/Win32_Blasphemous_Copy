#include "skScene.h"
#include "skPlayer.h"
#include "skSpriteRenderer.h"

namespace sk
{
	Scene::Scene()
	{
		_mLayers.resize((int)eLayerType::End);
	}
	Scene::~Scene()
	{
	}
	void Scene::Initialize()
	{

	}
	void Scene::Update()
	{
		for (Layer& layer : _mLayers)
		{
			layer.Update();
		}
	}
	void Scene::Render(HDC hdc)
	{
		for (/*Layer& layer : _mLayers*/int i=0;i < (int)eLayerType::End;i++)
		{
			Layer& layer = _mLayers[i];

			//if (i == (int)eLayerType::Background ||
			//	i == (int)eLayerType::Middleground ||
			//	i == (int)eLayerType::Floor ||
			//	i == (int)eLayerType::FrontBackground)
			//{
			//	BackGroundRender(hdc);
			//}
			//else
				layer.Render(hdc);
		}
	}
	void Scene::BackGroundRender(HDC hdc)
	{

	}
	void Scene::SceneEnter()
	{
	}
	void Scene::SceneOut()
	{
	}
}