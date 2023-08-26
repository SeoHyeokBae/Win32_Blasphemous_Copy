#include "skCollisionMgr.h"
#include "skScene.h"
#include "skSceneMgr.h"

namespace sk
{
	std::map<UINT64, bool> CollisionMgr::_mCollisionMap = {};
	std::bitset<LAYER_MAX> CollisionMgr::_mLayerMasks[LAYER_MAX] = {};

	void CollisionMgr::Initialize()
	{
	}
	void CollisionMgr::Update()
	{
		Scene* activeScene = SceneMgr::GetActiveScene();
		for (size_t row = 0; row < LAYER_MAX; row++)
		{
			for (size_t col = 0; col < LAYER_MAX; col++)
			{
				if (_mLayerMasks[row][col] == true)
				{
					LayerCollision(activeScene, (eLayerType)row, (eLayerType)col);
				}
			}
		}
	}
	void CollisionMgr::Render(HDC hdc)
	{
	}
	void CollisionMgr::Release()
	{
	}
	void CollisionMgr::Clear()
	{
		_mLayerMasks->reset();
		_mCollisionMap.clear();
	}
	void CollisionMgr::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
	{
		int row = -1;
		int col = -1;

		if (left > right)
		{
			row = (UINT)left;
			col = (UINT)right;
		}
		else
		{
			col = (UINT)left;
			row = (UINT)right;
		}

		_mLayerMasks[row][col] = enable;
	}
	void CollisionMgr::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
	{
		// finds left layer objects
		Layer& leftLayer = scene->GetLayer(left);
		std::vector<GameObject*>& lefts = leftLayer.GetGameObjects();

		// finds right layer Objects
		Layer& rightLayer = scene->GetLayer(right);
		std::vector<GameObject*>& rights = rightLayer.GetGameObjects();

		// finds right layer Objects
		for (GameObject* left:lefts)
		{
			Collider* leftCol = left->GetComponent<Collider>();
			if (leftCol == nullptr)
				continue;

			for (GameObject* right : rights)
			{
				Collider* rightCol = right->GetComponent<Collider>();
				if (rightCol == nullptr)
					continue;
				if (left == right)
					continue;

				ColliderCollision(leftCol, rightCol);
			}
		}

	}
	void CollisionMgr::ColliderCollision(Collider* left, Collider* right)
	{
		// 두 충돌체의 ID를 확인
		COlliderID ID;
		ID.left = (UINT)left->GetCollisionNumber();
		ID.right = (UINT)right->GetCollisionNumber();


		// 이전 충돌체의 정보를 가져와서 확인한다.
		std::map<UINT64, bool>::iterator iter
			= _mCollisionMap.find(ID.id);

		// 혹시 충돌정보가 없다면 생성해주면된다
		if (iter == _mCollisionMap.end())
		{
			_mCollisionMap.insert(std::make_pair(ID.id, false));
			iter = _mCollisionMap.find(ID.id);
		}


			//충돌함수 호출
			if (Intersect(left, right))
			{
				// 충돌 중인상태
				if (iter->second == false)
				{
					left->OnCollisionEnter(right);
					right->OnCollisionEnter(left);

					iter->second = true;

				}
				else // 처음 충돌하는 상태
				{
					left->OnCollisionStay(right);
					right->OnCollisionStay(left);
				}
			}
			else
			{
				// 충돌을 빠져나간상태
				if (iter->second == true)
				{
					left->OnCollisionExit(right);
					right->OnCollisionExit(left);

					iter->second = false;
				}
			}
	}

	bool CollisionMgr::Intersect(Collider* left, Collider* right)
	{
		Vector2 leftPos = left->GetPosition();
		Vector2 rightPos = right->GetPosition();

		Vector2 leftSize = left->GetSize();
		Vector2 rightSize = right->GetSize();

		if (fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2.0f + rightSize.x / 2.0f)
			&& fabs(leftPos.y - rightPos.y) < fabs(leftSize.y / 2.0f + rightSize.y / 2.0f))
		{
			return true;
		}

		return false;
	}
}