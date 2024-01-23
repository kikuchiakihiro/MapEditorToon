#include "RootJob.h"

#include "SceneManager.h"


RootJob::RootJob(GameObject* parent) :GameObject(parent, "RootJob")
{
}

RootJob::~RootJob()
{
}

void RootJob::Initialize()
{
	Instantiate<SceneManager>(this);
	//Instantiate<PlayScene>(this);
	/*PlayScene* pPlayScene;
	pPlayScene = new PlayScene(this);
	pPlayScene->Initialize();
	childList_.push_back(pPlayScene);*/
}


void RootJob::Update()
{
	
}

void RootJob::Draw()
{
	/*for (auto& e : childList_)
		e->Draw();*/
}

void RootJob::Release()
{
}

void RootJob::OnCollision(GameObject* pTarget)
{
}
