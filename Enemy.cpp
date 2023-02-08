#include "Enemy.h"
#include "Bullet.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

//コンストラクタ
Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy"),hModel_(-1)
{
}

//デストラクタ
Enemy::~Enemy()
{
}

//初期化
void Enemy::Initialize()
{
	transform_.position_ = XMFLOAT3(0, 0, 0);
	//モデルデータのロード
	hModel_ = Model::Load("Player.fbx");
	assert(hModel_ >= 0);
}

//更新
void Enemy::Update()
{
	if (Input::IsKey(DIK_SPACE))
	{
		enemy.shootFlag = true;
	}
	else
	{
		enemy.shootFlag = false;
	}

	if (Input::IsKey(DIK_UP))
	{
		transform_.position_.z += 1;
		enemy.dir = XMVectorSet(0, 0, 1, 0);
	}
	if (Input::IsKey(DIK_DOWN))
	{
		transform_.position_.z -= 1;
		enemy.dir = XMVectorSet(0, 0, -1, 0);

	}
	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.position_.x += 1;
		enemy.dir = XMVectorSet(1, 0, 0, 0);

	}
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.position_.x -= 1;
		enemy.dir = XMVectorSet(-1, 0, 0, 0);
	}

	//transform_.position_ = enemy.pos;
	//回転させる
	transform_.rotate_.y = Calculate() * 180.0f / 3.14f;
	if (enemy.shootFlag)
	{
		XMVECTOR vDir = enemy.dir;
		Bullet* pBullet = Instantiate<Bullet>(GetParent()->GetParent());
		vDir = XMVector3Normalize(vDir);
		vDir *= 0.8f;
		XMFLOAT3 dir= XMFLOAT3(0,0,0);
		pBullet->SetPosition(transform_.position_);
		XMStoreFloat3(&dir, vDir);
		pBullet->SetMove(dir);
	}

}

//描画
void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

}

//開放
void Enemy::Release()
{
}

void Enemy::Reception()
{
}

float Enemy::Calculate()
{
	XMVECTOR dir = enemy.dir;
	//角度を求めるために長さを１にする（正規化）
	dir = XMVector3Normalize(dir);

	//基準となる奥向きのベクトル
	XMVECTOR front = { 0, 0, 1, 0 };

	//frontとmoveの内積を求める
	XMVECTOR vecDot = XMVector3Dot(front, dir);
	float dot = XMVectorGetX(vecDot);

	//向いてる角度を求める（ラジアン）
	float angle = acos(dot);


	//frontとmoveの外積を求める
	XMVECTOR cross = XMVector3Cross(front, dir);

	//外積の結果のYがマイナス　＝　下向き　＝　左に進んでる
	if (XMVectorGetY(cross) < 0)
	{
		angle *= -1;
	}
	return angle;
}
