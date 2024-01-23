#pragma once
#include "GameObject.h"

enum SCENE_ID
{
    SCENE_ID_TEST = 0,
    SCENE_ID_PLAY,
};


class SceneManager :
    public GameObject
{

    SCENE_ID currentSceneID_;
    SCENE_ID nextSceneID_;

public:
    SceneManager(GameObject* parent);
    //‰Šú‰»
    void Initialize() override;

    //XV
    void Update() override;

    //•`‰æ
    void Draw() override;

    //ŠJ•ú
    void Release() override;

    void ChangeScene(SCENE_ID _next);
};

