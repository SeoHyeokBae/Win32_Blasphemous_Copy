#include "skAnimator.h"
#include "skResources.h"
#include "skTexture.h"
#include "skTimeMgr.h"

namespace sk
{
	Animator::Animator()
		: Component(eComponentType::Animator)
		, _mAlpha(1.0f)
		, _mScale(Vector2::One)
		, _mWaiting(0.0f)
		, _mWTime(0.0f)
	{
	}
	Animator::~Animator()
	{
		for (auto iter : _mAnimations)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
	void Animator::Initialize()
	{
	}
	void Animator::Update()
	{
		if (_mActiveAnimation)
		{
			_mActiveAnimation->Update();
			if (_mActiveAnimation->IsComplete() && _mbLoop)
			{
				if (_mWaiting != 0.0f)
				{
					_mWTime += TimeMgr::DeltaTime();
					if (_mWaiting <= _mWTime)
					{
						_mActiveAnimation->Reset();
						_mWTime = 0.0f;
					}
				}
				else
					_mActiveAnimation->Reset();
			}
		}
	}
	void Animator::Render(HDC hdc)
	{
		if (_mActiveAnimation)
			_mActiveAnimation->Render(hdc);
	}
	Animation* Animator::CreateAnimation(const std::wstring& name
		, Texture* texture, Vector2 leftTop, Vector2 size,UINT spriteLength, Vector2 offset, float duration)
	{
		Animation* animation = nullptr;
		animation = FindAnimation(name);
		if (animation != nullptr)
			return animation;

		animation = new Animation();
		animation->Create(name, texture
			, leftTop, size, offset
			, spriteLength, duration);
		animation->SetAnimator(this);


		_mAnimations.insert(std::make_pair(name, animation));
		//Resources::Insert<Animation>(name, animation);			//캐릭터마다 리소스 따로 보유
		
		return animation;
	}

	void Animator::CreateAnimationFolder(const std::wstring& name
		, const std::wstring path, Vector2 offset , float duration)
	{
		UINT width = 0;
		UINT height = 0;
		UINT fileCount = 0;

		std::filesystem::path fs(path);
		std::vector<Texture*> images = {};

		for (auto& p:std::filesystem::recursive_directory_iterator(path)) // 이미지 하나씩 받아서 저장
		{
			std::wstring fileName = p.path().filename();
			std::wstring fullName = p.path();

			Texture* image = Resources::Load<Texture>(fileName, fullName);
			images.push_back(image);

			if (width < image->GetWidth())
				width = image->GetWidth();

			if (height < image->GetHeight())
				height = image->GetHeight();

			fileCount++;
		}
		
		std::wstring spriteSheetName = name + L"SpriteSheet" ;
		Texture* spriteSheet = Texture::Create(spriteSheetName, width * fileCount, height); // 도화지 만들어주기

		spriteSheet->SetType(eTextureType::Bmp);

		int idx = 0;
		for (Texture* image: images) // 도화지에 이미지 하나씩 
		{
			BitBlt(spriteSheet->GetHdc(), width * idx, 0
				, image->GetWidth(), image->GetHeight()
				, image->GetHdc(), 0, 0, SRCCOPY);

			idx++;
		}

		CreateAnimation(name
			, spriteSheet, Vector2(0.0f, 0.0f)
			, Vector2(width, height), fileCount
			, offset, duration);
	}



	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		auto iter = _mAnimations.find(name);
		if (iter == _mAnimations.end())
			return nullptr;

		return iter->second;
	}

	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		Animation* animation = FindAnimation(name);
		if (animation == nullptr)
			return;

		_mActiveAnimation = animation;
		_mActiveAnimation->Reset();
		_mbLoop = loop;
	}
}