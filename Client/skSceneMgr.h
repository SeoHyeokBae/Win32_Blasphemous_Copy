#pragma once
#include "skScene.h"

namespace sk
{
	class SceneMgr
	{
	public: 
		static void Initialize() ;
		static void Update() ;
		static void Render(HDC hdc) ;
		static void Release();

		template<typename T>
		static T* CreateScene(const std::wstring& name)
		{
			T* scene = new T();
			scene->SetName(name);
			_mScenes.insert(std::make_pair(name, scene));
			_mActiveScenes = scene;
			scene->Initialize();

			return scene;
		}

		static Scene* LoadScene(const std::wstring& name);
		static Scene* GetActiveScene() { return _mActiveScenes; }

	private:
		static std::map<std::wstring, Scene*>_mScenes;
		static Scene* _mActiveScenes;

	};
}


