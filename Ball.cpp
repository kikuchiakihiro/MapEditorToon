#include "Ball.h"
#include "Engine/sprite.h"
#include "Engine/Model.h"
#include "Engine/Fbx.h"
#include "Engine/Transform.h"
//�R���X�g���N�^
Ball::Ball(GameObject* parent)
    :GameObject(parent, "Ball"),hModel_(-1)
{
}

//�f�X�g���N�^
Ball::~Ball()
{
}
Sprite* pSprite = nullptr;
//������
void Ball::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Assets/donut.fbx");
    assert(hModel_ >= 0);
    //transform_.position_.y = 1;
    transform_.scale_ = { 0.25,0.25,0.25 };
}

//�X�V
void Ball::Update()
{
    transform_.rotate_.y += 0.3;
}

//�`��
void Ball::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Ball::Release()
{
}