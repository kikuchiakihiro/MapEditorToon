#include "Floor.h"
#include "Engine/Model.h"
#include "Engine/Fbx.h"
#include "Engine/Transform.h"
//コンストラクタ
Floor::Floor(GameObject* parent)
    :GameObject(parent, "Floor"), hModel_(-1)
{
}

//デストラクタ
Floor::~Floor()
{
}
//Sprite* pSprite = nullptr;
//初期化
void Floor::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Assets/BoxDefault.fbx");
    assert(hModel_ >= 0);
    /*transform_.position_.z = 3;
    transform_.position_.y = -2;*/
   
}

//更新
void Floor::Update()
{
    transform_.rotate_.z += 0.1;
    transform_.rotate_.y += 0.1;
}

//描画
void Floor::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Floor::Release()
{
}