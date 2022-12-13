#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1),moveSpeed_(0.3f)
{
	camSpeed_.x = 2.5f;
	camSpeed_.y = 1.5f;
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
	//�摜�f�[�^�̃��[�h
}

//�X�V
void Player::Update()
{

	XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y����()�x��];
	XMMATRIX mRotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));   //x����()�x��];
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);//position���x�N�g���ɕϊ�

	//�}�E�X�̈ړ��ʂ𐳋K��
	XMFLOAT3 mouseMove = Input::GetMouseMove();
	XMVECTOR vMouseMove = XMLoadFloat3(&mouseMove);
	vMouseMove = XMVector3Normalize(vMouseMove);
	XMStoreFloat3(&mouseMove, vMouseMove);

	//���_�̉�]�i�}�E�X�̈ړ��ʁj
	transform_.rotate_.x += mouseMove.y * camSpeed_.y;
	transform_.rotate_.y += mouseMove.x * camSpeed_.x;
	if (transform_.rotate_.x >= 90)
	{
		transform_.rotate_.x = 90;
	}

	XMFLOAT3 move = { 0, 0, moveSpeed_};
	XMFLOAT3 moveX = { moveSpeed_, 0, 0 };
	XMVECTOR vMove = XMLoadFloat3(&move);
	XMVECTOR vMoveX = XMLoadFloat3(&moveX);
	vMove = XMVector3TransformCoord(vMove, mRotate);
	vMoveX = XMVector3TransformCoord(vMoveX, mRotate);
	if (Input::IsKey(DIK_D))
	{
		vPos += vMoveX;
	}
	if (Input::IsKey(DIK_A))
	{
		vPos -= vMoveX;
	}	
	if (Input::IsKey(DIK_W))
	{
		vPos += vMove;
	}
	if (Input::IsKey(DIK_S))
	{
		vPos -= vMove;
	}
	XMStoreFloat3(&transform_.position_, vPos);
	XMFLOAT3 camPos;
	XMVECTOR vCam = XMVectorSet(0, 0, -0.0001, 0);
	vCam = XMVector3TransformCoord(vCam, mRotateX);
	vCam = XMVector3TransformCoord(vCam, mRotate);

	XMStoreFloat3(&camPos, vPos + vCam);
	XMVECTOR myself = XMLoadFloat3(&camPos);
	XMVECTOR target = XMLoadFloat3(&transform_.position_);
	Camera::SetPosition(camPos);
	Camera::SetTarget(transform_.position_);
	if (Input::IsKey(DIK_ESCAPE))
	{
	PostQuitMessage(0);
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