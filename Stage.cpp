

#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "axisClass.h"


namespace {
    const XMFLOAT4 DEF_LIGHT_POSITION{ 1, 2, 1, 0 };
}

void Stage::IntConstantBuffer()
{
    D3D11_BUFFER_DESC cb;
    cb.ByteWidth = sizeof(CBUFF_STAGESCENE);
    cb.Usage = D3D11_USAGE_DEFAULT;
    cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cb.CPUAccessFlags = 0;
    cb.MiscFlags = 0;
    cb.StructureByteStride = 0;

    // コンスタントバッファの作成
    HRESULT hr;
    hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pCBStageScene_);
    if (FAILED(hr))
    {
        MessageBox(NULL, "コンスタントバッファの作成に失敗しました", "エラー", MB_OK);
    }

}

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),  lightSourcePosition_(DEF_LIGHT_POSITION)
{
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    hLightBall_ = Model::Load("assets/Ballkyu.fbx");
    assert(hLightBall_ >= 0);
    Camera::SetPosition(XMVECTOR{ 0, 10, -20, 0 });
    Camera::SetTarget(XMVECTOR{ 0, 2, 0, 0 });
   

    trLightBall.position_ = { 0, 0, 0 };
    trLightBall.rotate_ = { 0, 0, 0 };
    trLightBall.scale_ = { 0.05, 0.05, 0.05};
    Instantiate<axisClass>(this);
    IntConstantBuffer();
}

//更新
void Stage::Update()
{

    //transform_.rotate_.y += 0.5f;
    // trDonuts.rotate_.y += 0.5f;
    if (Input::IsKey(DIK_RIGHT))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x + 0.1f, p.y + 0.0f, p.z + 0.0f, p.w + 0.0f };

        //Model::GetModel(hModel_)->SetLightPos(margin);
        SetLightPos(margin);
    }
    if (Input::IsKey(DIK_LEFT))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.1f, p.y - 0.0f, p.z - 0.0f, p.w - 0.0f };

        /// Model::GetModel(hModel_)->SetLightPos(margin);
        SetLightPos(margin);
    }
    if (Input::IsKey(DIK_UP))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f, p.y + 0.1f, p.z - 0.0f, p.w - 0.0f };

        //Model::GetModel(hModel_)->SetLightPos(margin);
        SetLightPos(margin);
    }
    if (Input::IsKey(DIK_DOWN))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f, p.y - 0.1f, p.z - 0.0f, p.w - 0.0f };

        //Model::GetModel(hModel_)->SetLightPos(margin);
        SetLightPos(margin);
    }
    if (Input::IsKey(DIK_W))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f, p.y - 0.0f, p.z + 0.1f, p.w + 0.0f };

        //Model::GetModel(hModel_)->SetLightPos(margin);
        SetLightPos(margin);
    }
    if (Input::IsKey(DIK_S))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f, p.y - 0.0f, p.z - 0.1f, p.w - 0.0f };

        //Model::GetModel(hModel_)->SetLightPos(margin);
        SetLightPos(margin);
    }
    XMFLOAT4 tmp{ GetLightPos() };
    trLightBall.position_ = { tmp.x, tmp.y,tmp.z };

    CBUFF_STAGESCENE cb;
    cb.lightPosition = lightSourcePosition_;
    XMStoreFloat4(&cb.eyePos, Camera::GetEyePosition());

    Direct3D::pContext_->UpdateSubresource(pCBStageScene_,
        0, NULL, &cb, 0, 0);

    Direct3D::pContext_->VSSetConstantBuffers(1, 1, &pCBStageScene_);	//頂点シェーダー用	
    Direct3D::pContext_->PSSetConstantBuffers(1, 1, &pCBStageScene_);	//ピクセルシェーダー用
}

//描画
void Stage::Draw()
{
    //q->Draw(transform_);
    //Model::SetTransform(hModel_, trDonuts);
    //Model::Draw(hModel_);
    ////Model::SetTransform(hGround_, trGround);
    ////Model::Draw(hGround_);
    Model::SetTransform(hLightBall_, trLightBall);
    Model::Draw(hLightBall_);
}

//開放
void Stage::Release()
{
}