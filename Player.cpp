#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Map.h"
#include "Bullet.h"
#include <corecrt_math_defines.h>
#include "Math.h"

#define DEBUG


//コンストラクタ
Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), hMapModel_(-1), camDist_(0), dashSpeed_(0.1f),height_(10)
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
	hModel_ = Model::Load("player2.fbx");
	assert(hModel_ >= 0);
	//マップオブジェクトを探す
	Map* pMap = (Map*)FindObject("Map");
	// 床のモデル番号を取得
	hMapModel_ = pMap->GetModelHandle(0);
}

//更新
void Player::Update()
{

	vPos_ = XMLoadFloat3(&transform_.position_);

	//移動量
	XMVECTOR moveX = { 1, 0, 0, 0 };
	XMVECTOR moveZ = { 0, 0, 1, 0 };
	moveX = XMVector3TransformCoord(moveX, mRotate_);
	moveZ = XMVector3TransformCoord(moveZ, mRotate_);
	//移動入力処理
	if (Input::IsKey(DIK_LSHIFT) || Input::IsKey(DIK_RSHIFT))
	{
		playerstate_ = dash;
	}
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
	if (Input::IsMouseButton(0x00))
	{
		shoot();
	}



	switch (playerstate_)
	{
	case move:
		PlayerSlideMove();
		break;
	case dash:
		
	default:
		Math::EaseOut(&dashSpeed_, 0.01f, 0.1f);
		break;
	}
	XMStoreFloat3(&transform_.position_, vPos_);

	ViewRotate();
	CallCam();

	if (Input::IsKey(DIK_Q))
	{
		dashSpeed_ = 1.0f;
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

void Player::PlayerMove()
{
	vMove_ = XMVector3Normalize(vMove_);
	//vMove_ *= Math::EaseIn(&dashSpeed_,0.01f,3);
	vPos_ += vMove_;
	vMove_ = XMVectorSet(0, 0, 0, 0);
	playerstate_ = noMove;
	
}

void Player::PlayerSlideMove()
{
	RayCastData data;
	
	if (IsHit(hMapModel_, &data))
	{
		vMove_ = ScratchWall(data.normal, vMove_);
	}
	vPos_ += vMove_;
	vMove_ = XMVectorSet(0, 0, 0, 0);
	playerstate_ = noMove;


}

bool Player::IsHit(int h_model,RayCastData* data)
{

	XMVECTOR length = XMVector3Length(vMove_);
	float leng = XMVectorGetX(length);
	XMStoreFloat3(&data->start, vPos_);
	XMStoreFloat3(&data->dir, vMove_);
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

void Player::CallCam()
{
	//Cameraの処理

	XMFLOAT3 camPos;
	//Cameraの位置
	XMVECTOR vCam = XMVectorSet(0, transform_.position_.y+height_, -0.0001f + camDist_, 0);

	vCam = XMVector3TransformCoord(vCam, mRotateX_);
	vCam = XMVector3TransformCoord(vCam, mRotate_);

	XMStoreFloat3(&camPos, vPos_ + vCam);

	XMVECTOR myself = XMLoadFloat3(&camPos);
	XMVECTOR target = XMLoadFloat3(&transform_.position_);
	XMFLOAT3 tage = transform_.position_;
	tage.y = height_;
	Camera::SetPosition(camPos);
	Camera::SetTarget(tage);
}

void Player::ViewRotate()
{
	//マウスの移動量を正規化
	XMFLOAT3 mouseMove = Input::GetMouseMove();

	//視点の回転（マウスの移動量）
	transform_.rotate_.x += mouseMove.y ;
	transform_.rotate_.y += mouseMove.x ;
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


#ifdef DEBUG
	camDist_ += mouseMove.z/10;
	if (camDist_ > 0)camDist_ = 0;
#endif // DEBUG

}

XMVECTOR Player::ScratchWall(XMVECTOR normal, XMVECTOR pos)
{
	XMVECTOR delY = XMVectorSet( 1, 0, 1, 1 );
	normal = XMVector3Normalize(normal);
	XMVECTOR result =	XMVector3Normalize(pos - XMVector3Dot(pos, normal) * normal);
	result *= delY;
	return result;

}

void Player::shoot()
{
	XMFLOAT3 camPos = Camera::GetPosition();
	XMVECTOR vCam = XMLoadFloat3(&camPos);
	Bullet* pBullet = Instantiate<Bullet>(GetParent()->GetParent());
	XMFLOAT3 bulletPos = transform_.position_;
	XMVECTOR move = (XMLoadFloat3(&bulletPos) - vCam);
	//このままだと大砲の長さで弾の速度が決まるのでベクトルを正規化
	move = XMVector3Normalize(move);
	//正規化して長さ1の単位ベクトルにした値にかけてあげたりすることで調整できる
	move *= 0.8f;
	XMStoreFloat3(&camPos, move);
	pBullet->SetPosition(transform_.position_);
	pBullet->SetMove(camPos);

}
