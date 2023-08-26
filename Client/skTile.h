#pragma once
#include "skGameObject.h"


namespace sk
{
	class Tile : public GameObject
	{
	public:
		Tile();
		~Tile();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}