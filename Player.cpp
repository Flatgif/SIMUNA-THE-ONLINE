#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1),moveSpeed_(0.3f)
{
	camSpeed_.x = 2.5f;
	camSpeed_.y = 1.5f;
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
	//画像データのロード
}

//更新
void Player::Update()
{

	XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸で()度回転;
	XMMATRIX mRotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));   //x軸で()度回転;
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);//positionもベクトルに変換

	//マウスの移動量を正規化
	XMFLOAT3 mouseMove = Input::GetMouseMove();
	XMVECTOR vMouseMove = XMLoadFloat3(&mouseMove);
	vMouseMove = XMVector3Normalize(vMouseMove);
	XMStoreFloat3(&mouseMove, vMouseMove);

	//視点の回転（マウスの移動量）
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