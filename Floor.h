#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Floor : public GameObject
{
    int hModel_;    //���f���ԍ�
public:
    //�R���X�g���N�^
    Floor(GameObject* parent);

    //�f�X�g���N�^
    ~Floor();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};