#include "SceneManager.h"
#include "../TestScene.h"
#include "Direct3D.h"
#include "Model.h"

SceneManager::SceneManager(GameObject* parent):GameObject(parent, "SceneManager")
{

}

void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_TEST;
	nextSceneID_ = currentSceneID_;
	Instantiate<TestScene>(this);
}

void SceneManager::Update()
{

	if (currentSceneID_ != nextSceneID_) {

		auto scene = childList_.begin();
		(*scene)->ReleaseSub();
		SAFE_DELETE(*scene);
		childList_.clear();

		Model::Release();
		//å„ï–ïtÇØèIóπ
		switch (nextSceneID_)
		{
		case SCENE_ID_TEST:
			Instantiate<TestScene>(this);
			break;
		
		}
		currentSceneID_ = nextSceneID_;
	}

	

}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

void SceneManager::ChangeScene(SCENE_ID _next)
{
	nextSceneID_ = _next;
}
