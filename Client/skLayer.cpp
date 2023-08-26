#include "skLayer.h"

namespace sk
{
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{
		for (GameObject* obj : _mGameObjects)
		{
			delete obj;
			obj = nullptr;
		}
	}
	void Layer::Initialize()
	{
	}
	void Layer::Update()
	{
		for (GameObject* obj : _mGameObjects)
		{
			if (obj->GetGameObjState() == GameObject::eState::Pause)
				continue;

			obj->Update();
		}
	}
	void Layer::Render(HDC hdc)
	{
		for (GameObject* obj : _mGameObjects)
		{
			if (obj->GetGameObjState() == GameObject::eState::Pause)
				continue;

			obj->Render(hdc);
		}

		for (std::vector<GameObject*>::iterator iter = _mGameObjects.begin()
			; iter != _mGameObjects.end()
			; )
		{
			if ((*iter)->GetGameObjState() == GameObject::eState::Dead)
			{
				GameObject* deadObj = *iter;
				delete deadObj;
				deadObj = nullptr;

				iter = _mGameObjects.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}
}