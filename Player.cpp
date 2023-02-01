#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Map.h"
#include "Bullet.h"
#include <corecrt_math_defines.h>

#define DEBUG


//コンストラクタ
Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), hMapModel_(-1)
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
	//マップオブジェクトを探す
	Map* pMap = (Map*)FindObject("Map");
	// 床のモデル番号を取得
	hMapModel_ = pMap->GetModelHandle(1);
}

//更新
void Player::Update()
{
	//Y軸で()度回転;
	mRotate_ = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	//x軸で()度回転;
	mRotateX_ = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));


	vPos_ = XMLoadFloat3(&transform_.position_);


	//移動量
	XMVECTOR moveX = { 1, 0, 0, 0 };
	XMVECTOR moveZ = { 0, 0, 1, 0 };

	//移動入力処理
	if (Input::IsKey(DIK_W))
	{
		AddMove(moveZ);
	}
	if (Input::IsKey(DIK_A))
	{
		AddMove(-moveX);

	}
	if (Input::IsKey(DIK_S))
	{
		AddMove(-moveZ);
	}
	if (Input::IsKey(DIK_D))
	{
		AddMove(moveX);

	}
	switch (playerstate_)
	{
	case move:
		if (IsHit(hMapModel_))
		{
			playerstate_ = noMove;
		}
		PlayerMove();
	default:
		break;
	}
	XMStoreFloat3(&transform_.position_, vPos_);


	ViewRotate();
	CallCam();
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

void Player::PlayerMove()
{
	vMove_ = XMVector3Normalize(vMove_);
	vPos_ += vMove_;
	vMove_ = XMVectorSet(0, 0, 0, 0);
	playerstate_ = noMove;
}
bool Player::IsHit(int h_model)
{
	float length = XMVectorGetX(vMove_);
	RayCastData data;
	XMStoreFloat3(&data.start, vPos_);
	XMStoreFloat3(&data.dir, vMove_);
	Model::RayCast(h_model, &data);
	if (data.hit && data.dist < length)
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

void Player::CallCam()
{
	XMFLOAT3 camPos;
	static XMVECTOR vCam = XMVectorSet(0, 0, -0.0000001f, 0);

	vCam = XMVector3TransformCoord(vCam, mRotateX_);
	vCam = XMVector3TransformCoord(vCam, mRotate_);

	XMStoreFloat3(&camPos, (vPos_ + vCam));


	Camera::SetPosition(camPos);
	Camera::SetTarget(transform_.position_);

}

void Player::ViewRotate()
{
	//Cameraの処理
//マウスの移動量
	XMFLOAT3 mouseMove = Input::GetMouseMove();
	static float mouseZ = 0;
	mouseZ += mouseMove.z;
	//Cameraの位置
	if (mouseZ > 0)
		mouseZ = 0;

	//視点の回転（マウスの移動量）
	transform_.rotate_.x += mouseMove.y / 10;
	transform_.rotate_.y += mouseMove.x / 10;


	if (transform_.rotate_.x >= 89)
	{
		transform_.rotate_.x = 89;
	}
	if (transform_.rotate_.x <= -89)
	{
		transform_.rotate_.x = -89;
	}
	//Y軸で()度回転;
	mRotate_ = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	//x軸で()度回転;
	mRotateX_ = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

}