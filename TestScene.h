#pragma once
#include "Engine/GameObject.h"
class TestScene
	:public GameObject
{
public:
    TestScene(GameObject* parent);
        //‰Šú‰»
        void Initialize() override;

    //XV
    void Update() override;

    //•`‰æ
    void Draw() override;

    //ŠJ•ú
    void Release() override;
};

