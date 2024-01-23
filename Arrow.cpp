//#include "Arrow.h"
//
//#include "Engine/Model.h"
//#include "Engine/Fbx.h"
//#include "Engine/Transform.h"
////コンストラクタ
//Arrow::Arrow(GameObject* parent)
//    :GameObject(parent, "Arrow"), hModel_(-1)
//{
//}
//
////デストラクタ
//Arrow::~Arrow()
//{
//}
////Sprite* pSprite = nullptr;
////初期化
//void Arrow::Initialize()
//{
//    //モデルデータのロード
//    hModel_ = Model::Load("Assets/Arrow.fbx");
//    assert(hModel_ >= 0);
//    transform_.position_.x = 3;
//    transform_.scale_ = { 0.25 ,0.25 ,0.25 };
//}
//
////更新
//void Arrow::Update()
//{
//    transform_.rotate_.y += 0.5;
//}
//
////描画
//void Arrow::Draw()
//{
//    Model::SetTransform(hModel_, transform_);
//    Model::Draw(hModel_);
//}
//
////開放
//void Arrow::Release()
//{
//}