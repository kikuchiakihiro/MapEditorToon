#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Ball : public GameObject
{
    int hModel_;    //モデル番号
public:
    //コンストラクタ
    Ball(GameObject* parent);

    //デストラクタ
    ~Ball();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};