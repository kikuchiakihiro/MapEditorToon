#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"


class axisClass :
    public GameObject
{
    Fbx* pFbx;
    int hModel_;//モデル番号
public:
    //コンストラクタ
    axisClass(GameObject* parent);

    //デストラクタ
    ~axisClass();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};