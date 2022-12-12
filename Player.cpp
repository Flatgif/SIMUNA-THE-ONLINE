#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1)
{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{	
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("player.fbx");
	assert(hModel_ >= 0);
	Camera::SetPosition(XMFLOAT3(transform_.position_));
	Camera::SetTarget(XMFLOAT3(transform_.position_.x, transform_.position_.y, 1));

}

//�X�V
void Player::Update()
{
	XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y����()�x��];
	XMMATRIX mRotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));   //x����()�x��];
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);//position���x�N�g���ɕϊ�
	XMFLOAT3 move = { 0, 0, 2.0f };
	XMFLOAT3 moveX = { 2.0f, 0, 0 };
	XMVECTOR vMove = XMLoadFloat3(&move);
	XMVECTOR vMoveX = XMLoadFloat3(&moveX);
	vMove = XMVector3TransformCoord(vMove, mRotate);
	vMoveX = XMVector3TransformCoord(vMoveX, mRotate);
	XMFLOAT3 targetPos = transform_.position_;
	XMVECTOR vTargetPos = XMLoadFloat3(&targetPos);
	if (Input::IsKey(DIK_D))
	{
		vTargetPos += vMove;
		XMStoreFloat3(&targetPos, vTargetPos);
		Camera::SetTarget(XMFLOAT3(targetPos));
		vPos += vMoveX;
	}
	if (Input::IsKey(DIK_A))
	{
		vTargetPos += vMove;
		XMStoreFloat3(&targetPos, vTargetPos);
		Camera::SetTarget(XMFLOAT3(targetPos));
		vPos -= vMoveX;
	}	
	if (Input::IsKey(DIK_W))
	{
		vTargetPos += vMove;
		XMStoreFloat3(&targetPos, vTargetPos);
		Camera::SetTarget(XMFLOAT3(targetPos));
		vPos += vMove;
	}
	if (Input::IsKey(DIK_S))
	{
		vTargetPos += vMove;
		XMStoreFloat3(&targetPos, vTargetPos);
		Camera::SetTarget(XMFLOAT3(targetPos));
		vPos -= vMove;
	}
	Camera::SetPosition(XMFLOAT3(transform_.position_));
	XMFLOAT3 camPos;
	XMVECTOR vCam = XMVectorSet(0, 0, -0.0001, 0);
	vCam = XMVector3TransformCoord(vCam, mRotateX);
	vCam = XMVector3TransformCoord(vCam, mRotate);

	XMStoreFloat3(&camPos, vPos + vCam);

	XMVECTOR myself = XMLoadFloat3(&camPos);
	XMVECTOR target = XMLoadFloat3(&transform_.position_);

	if (!Input::IsKey(DIK_Q))
	{

		Camera::SetPosition(camPos);
		Camera::SetTarget(transform_.position_);

	}

}

//�`��
void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Player::Release()
{
}