//#include "Arrow.h"
//
//#include "Engine/Model.h"
//#include "Engine/Fbx.h"
//#include "Engine/Transform.h"
////�R���X�g���N�^
//Arrow::Arrow(GameObject* parent)
//    :GameObject(parent, "Arrow"), hModel_(-1)
//{
//}
//
////�f�X�g���N�^
//Arrow::~Arrow()
//{
//}
////Sprite* pSprite = nullptr;
////������
//void Arrow::Initialize()
//{
//    //���f���f�[�^�̃��[�h
//    hModel_ = Model::Load("Assets/Arrow.fbx");
//    assert(hModel_ >= 0);
//    transform_.position_.x = 3;
//    transform_.scale_ = { 0.25 ,0.25 ,0.25 };
//}
//
////�X�V
//void Arrow::Update()
//{
//    transform_.rotate_.y += 0.5;
//}
//
////�`��
//void Arrow::Draw()
//{
//    Model::SetTransform(hModel_, transform_);
//    Model::Draw(hModel_);
//}
//
////�J��
//void Arrow::Release()
//{
//}