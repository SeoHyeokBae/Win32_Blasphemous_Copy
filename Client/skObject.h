#pragma once
#include "skScene.h"
#include "skGameObject.h"
#include "skSceneMgr.h"
#include "skTransform.h"

namespace sk::object
{
	template<typename T>
	static __forceinline T* Instantiate(eLayerType type)
	{
		T* gameObject = new T();
		Scene* scene = SceneMgr::GetActiveScene();
		scene->AddGameObject(type, gameObject);
		gameObject->Initialize();

		return gameObject;
	}

	template <typename T>
	static __forceinline T* Instantiate(eLayerType type, Vector2 position)
	{
		T* gameObject = new T();
		Scene* scene = SceneMgr::GetActiveScene();
		scene->AddGameObject(type, gameObject);
		gameObject->Initialize();
		gameObject->GetComponent<Transform>()->SetPosition(position);

		return gameObject;
	}

	template <typename T>
	static __forceinline void Instantiate(eLayerType type, GameObject* obj)
	{
		Scene* scene = SceneMgr::GetActiveScene();
		scene->AddGameObject(type, obj);
	}
}