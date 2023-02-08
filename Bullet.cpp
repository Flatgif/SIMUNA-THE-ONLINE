#include "Bullet.h"
#include "Item.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Stage.h"
//�R���X�g���N�^
Bullet::Bullet(GameObject* parent)
    :GameObject(parent, "Bullet"), hModel_(-1), move_(XMFLOAT3(0.1f, 0, 0)), bulletLanding_(0.00001f)
{
}

//�f�X�g���N�^
Bullet::~Bullet()
{
}

//������
void Bullet::Initialize()
{    
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("player.fbx");
    assert(hModel_ >= 0);
    transform_.scale_ = XMFLOAT3(0.5f, 0.5f, 0.5f);
   // Instantiate<Item>(this);
    Stage* pStage = (Stage*)FindObject("Stage");
    // ���̃��f���ԍ����擾
    hMapModel_ = pStage->GetModelHandle(0);
}

//�X�V
void Bullet::Update()
{
    XMVECTOR vMove = XMLoadFloat3(&move_);
    XMMATRIX mRotate =XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    move_.y -= bulletLanding_;
    RayCastData data;
    if (Hit(vMove, hMapModel_, &data))
    {
        vMove = XMVector3Normalize(data.normal);
        XMStoreFloat3(&move_, vMove);

    }
    vPos += vMove;
    XMStoreFloat3(&transform_.position_, vPos);
    int num = 200;
    if (transform_.position_.y <= -num || transform_.position_.y >= num ||
        transform_.position_.x <= -num || transform_.position_.x >= num ||
        transform_.position_.z <= -num || transform_.position_.z >= num)
    {
        KillMe();
    }

}

//�`��
void Bullet::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

}

//�J��
void Bullet::Release()
{
}

bool Bullet::Hit(XMVECTOR move,int h_model, RayCastData* data)
{
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    XMVECTOR length = XMVector3Length(move);
    float leng = XMVectorGetX(length);
    XMStoreFloat3(&data->start, vPos);
    XMStoreFloat3(&data->dir, move);
    Model::RayCast(h_model, &*data);
    if (data->dist * leng <= leng)
    {
        return true;
    }
    else
    {
        return false;
    }
}

