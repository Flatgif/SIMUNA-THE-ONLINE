#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1)
{
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{	
	//モデルデータのロード
	hModel_ = Model::Load("player.fbx");
	assert(hModel_ >= 0);
	Camera::SetPosition(XMFLOAT3(transform_.position_));
	Camera::SetTarget(XMFLOAT3(transform_.position_.x, transform_.position_.y, 1));

}

//更新
void Player::Update()
{
	XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸で()度回転;
	XMMATRIX mRotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));   //x軸で()度回転;
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);//positionもベクトルに変換
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

//描画
void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Player::Release()
{
}