#pragma once
#include "skGameObject.h"
#include "skTexture.h"

namespace sk
{
	class BottonUI : public GameObject
	{
	public:
		enum class eState
		{
			Off,
			On,
			Selected,
			None
		};


		BottonUI();
		virtual ~BottonUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetSelect(eState State, Texture* texture) { _mSelect[(UINT)State] = texture; }
		void SetBottonState(eState state) { _mCurState = state; }
		eState GetBottonState() { return _mCurState; }


	private:
		eState _mCurState;
		eState _mPrvState;
		std::vector<Texture*> _mSelect;
	};
}
