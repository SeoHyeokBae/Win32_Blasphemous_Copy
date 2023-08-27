#include "skSceneMgr.h"
#include "skTitleScene.h"

#include "skPlayScene1.h"
#include "skTutorialScene.h"
#include "skFirstBossScene.h"
#include "skScene04.h"
#include "skScene05.h"
#include "skInput.h"

namespace sk
{
	std::map<std::wstring, Scene*> SceneMgr::_mScenes = {};
	Scene* SceneMgr::_mActiveScenes = nullptr;

	void SceneMgr::Initialize()
	{
		CreateScene<TitleScene>(L"TitleScene");
		//CreateScene<TitleScene>(L"ToolScene");
		CreateScene<PlayScene1>(L"PlayScene1");
		CreateScene<TutorialScene>(L"TutorialScene");
		CreateScene<FirstBossScene>(L"FirstBossScene");
		CreateScene<Scene04>(L"Scene04");
		CreateScene<Scene05>(L"Scene05");

		LoadScene(L"TitleScene");
	}
	void SceneMgr::Update()
	{
		_mActiveScenes->Update();
	}
	void SceneMgr::Render(HDC hdc)
	{
		_mActiveScenes->Render(hdc);
	}

	void SceneMgr::Release()
	{
		for (auto iter : _mScenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	Scene* SceneMgr::LoadScene(const std::wstring& name)
	{
		_mActiveScenes->SceneOut();
		std::map<std::wstring, Scene*>::iterator iter
			= _mScenes.find(name);

		if (iter == _mScenes.end())
			return nullptr;
		
		_mActiveScenes = iter->second;

		_mActiveScenes->SceneEnter();
		return iter->second;
	}

}