#include "Bullet.h"
#include "Item.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

//コンストラクタ
Bullet::Bullet(GameObject* parent)
    :GameObject(parent, "Bullet"), hModel_(-1), move_(XMFLOAT3(0.1f, 0, 0)), bulletLanding_(0.001f)
{
}

//デストラクタ
Bullet::~Bullet()
{
}

//初期化
void Bullet::Initialize()
{    
    //モデルデータのロード
    hModel_ = Model::Load("player.fbx");
    assert(hModel_ >= 0);
    transform_.scale_ = XMFLOAT3(0.05f, 0.05f, 0.05f);
   // Instantiate<Item>(this);
}

//更新
void Bullet::Update()
{
    XMVECTOR vMove = XMLoadFloat3(&move_);
    XMMATRIX mRotate =XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    move_.y -= bulletLanding_;
    vPos += vMove;
    if (Input::IsKey(DIK_RSHIFT) || Input::IsKey(DIK_LSHIFT))
    {
        vPos += vMove;
    }
    XMStoreFloat3(&transform_.position_, vPos);

    if (transform_.position_.y <= -20 || transform_.position_.y >= 200 ||
        transform_.position_.x <= -1000 || transform_.position_.x >= 1000 ||
        transform_.position_.z <= -1000 || transform_.position_.z >= 1000)
    {
        KillMe();
    }

}

//描画
void Bullet::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

}

//開放
void Bullet::Release()
{
}