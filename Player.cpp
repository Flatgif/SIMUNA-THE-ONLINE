#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Map.h"
#include "Bullet.h"


//コンストラクタ
Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1),
	moveSpeed_(0.1f), viewHeigt_(10.0f), bulletSpeed_(2.0f), recoil_(0.2f), defaultHeigt_(10.0f), jumpPowerDefault_(1.0f), gravity_(0.05f)
	, crouchDownHeigt_(defaultHeigt_ / 2), crouchDownSpeed_(moveSpeed_ / 2), runSpeed_(moveSpeed_ * 2)
	, vMove({ 0.0f, 0.0f, 0.0f, 0.0f }), vMoveX({ 0.0f, 0.0f, 0.0f, 0.0f }), vPos({ 0.0f, 0.0f, 0.0f, 0.0f }), move({ 0,0,0 }), moveX({ 0,0,0 })
{
	camSpeed_.x = 2.0f;
	camSpeed_.y = 1.0f;
	jumpPower_ = jumpPowerDefault_;
	hGroundModel = -1;

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

	if (moveFlag_ != jump)
	{
		prePos = transform_.position_;
	}
	//Cameraの軸

	//Y軸で()度回転;
	XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	//x軸で()度回転;
	XMMATRIX mRotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
	//positionもベクトルに変換
	vPos = XMLoadFloat3(&transform_.position_);


	//移動量
	move = { 0, 0, moveSpeed_ };
	moveX = { moveSpeed_, 0, 0 };

	//移動入力処理
	if (Input::IsKeyDown(DIK_SPACE))
	{
		moveFlag_ = jump;
		jumpPower_ = jumpPowerDefault_;
		JumpPlayer();
	}

	if (Input::IsKey(DIK_D))
	{
		MovePlayerR();
	}
	if (Input::IsKey(DIK_A))
	{
		MovePlayerL();
	}
	if (Input::IsKey(DIK_W))
	{
		MovePlayerF();
	}
	if (Input::IsKey(DIK_S))
	{
		MovePlayerB();

	}
	//if (Input::IsKey(DIK_LSHIFT))
	//{
	//	moveFlag_ = run;
	//}
	//if (Input::IsKey(DIK_LCONTROL) || Input::IsKey(DIK_RCONTROL))
	//{
	//	moveFlag_ = crouchDown;
	//}


	switch (moveFlag_)
	{
		//case run:
		//	Run();
		//	break;
		//case crouchDown:
		//	CrouchDown();
		//	break;
	case jump:
		
		break;
	case jump + run:
		Run();
		JumpPlayer();
	default:
		viewHeigt_ = defaultHeigt_;
		moveFlag_ = noMove;
		break;
	}
	//ポジション反映
	vMove = XMLoadFloat3(&move);
	vMoveX = XMLoadFloat3(&moveX);

	vMove = XMVector3TransformCoord(vMove, mRotate);
	vMoveX = XMVector3TransformCoord(vMoveX, mRotate);
	RayCastData d;
	XMVECTOR normal = d.normal;




	XMStoreFloat3(&transform_.position_, vPos);

	//Cameraの処理

	XMFLOAT3 camPos;
	//Cameraの位置
	XMVECTOR vCam = XMVectorSet(0, 0, -0.0001, 0);
	vCam = XMVector3TransformCoord(vCam, mRotateX);
	vCam = XMVector3TransformCoord(vCam, mRotate);

	//マウスの移動量を正規化
	XMFLOAT3 mouseMove = Input::GetMouseMove();

	//視点の回転（マウスの移動量）
	transform_.rotate_.x += mouseMove.y / 10 * camSpeed_.y;
	transform_.rotate_.y += mouseMove.x / 10 * camSpeed_.x;
	if (transform_.rotate_.x >= 89)
	{
		transform_.rotate_.x = 89;
	}
	if (transform_.rotate_.x <= -89)
	{
		transform_.rotate_.x = -89;
	}

	//Camera反映
	XMStoreFloat3(&camPos, vPos + vCam);
	XMVECTOR myself = XMLoadFloat3(&camPos);
	XMVECTOR target = XMLoadFloat3(&transform_.position_);
	Camera::SetPosition(camPos);
	Camera::SetTarget(transform_.position_);

	//マップオブジェクトを探す
	Map* pMap = (Map*)FindObject("Map");
	// 床のモデル番号を取得
	hGroundModel = pMap->GetModelHandle(0);

	RayCastData data;
	//レイの発射位置
	XMFLOAT3 startPos = transform_.position_;
	startPos.y += 1;
	data.start = startPos;
	data.start.y = 0;
	//レイの方向
	data.dir = XMFLOAT3(0, -1, 0);
	//レイを発射
	Model::RayCast(hGroundModel, &data);
	if (!data.hit)
	{
		moveFlag_ = noMove;
		prePos = transform_.position_;
	}
	if (data.hit)
	{
		if (moveFlag_ != jump)
		{
			transform_.position_.y = -data.dist + viewHeigt_;

		}
	}

	if (Input::IsMouseButton(0x00))
	{
		transform_.rotate_.x -= recoil_;
		Bullet* pBullet = Instantiate<Bullet>(GetParent()->GetParent());
		XMFLOAT3 bulletPos = transform_.position_;
		XMVECTOR move = (target - myself);
		//このままだと大砲の長さで弾の速度が決まるのでベクトルを正規化
		move = XMVector3Normalize(move);
		//正規化して長さ1の単位ベクトルにした値にかけてあげたりすることで調整できる
		move *= bulletSpeed_;
		XMStoreFloat3(&camPos, move);
		pBullet->SetPosition(transform_.position_);
		pBullet->SetMove(camPos);
	}

	//強制終了
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

void Player::MovePlayerF()
{
	MoveHit(&vPos, vMove, hGroundModel);
}

void Player::MovePlayerB()
{
	MoveHit(&vPos, -vMove, hGroundModel);
}

void Player::MovePlayerR()
{
	MoveHit(&vPos, vMoveX, hGroundModel);
}

void Player::MovePlayerL()
{
	MoveHit(&vPos, -vMoveX, hGroundModel);
}

void Player::JumpPlayer(){
	moveFlag_ = noMove;
	jump_ = { 0,jumpPower_,0 };
	vJump = XMLoadFloat3(&jump_);
	if (!IsHit(&vPos, vJump, hModel_))
	{
		vPos += vJump;
		XMStoreFloat3(&transform_.position_, vPos);
		jumpPower_ -= gravity_;

		wchar_t buffer[256];
		swprintf_s(buffer, L"★変数の値は%d\n", jumpPower_);
		OutputDebugString((LPCSTR)buffer);

	}
	else
	{
		moveFlag_ = noMove;

	}

}
bool Player::IsHit(XMVECTOR pos, XMVECTOR move, int h_model)
{
	pos += move;
	XMVECTOR v = XMVector3Length(move);
	float length = XMVectorGetX(v);
	XMFLOAT3 dir;
	XMStoreFloat3(&dir, pos);
	RayCastData data;
	data.start = transform_.position_;
	data.dir = dir;
	Model::RayCast(h_model, &data);
	if (data.hit && data.dist <= length && data.dist != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;

}
void Player::CrouchDown()
{
	viewHeigt_ = crouchDownHeigt_;
	move = { 0, 0, crouchDownSpeed_ };
	moveX = { crouchDownSpeed_, 0, 0 };
}
void Player::MoveHit(XMVECTOR *pos, XMVECTOR move, int h_model)
{
	XMVECTOR Pos = *pos;
	
	
	Pos += move;
	XMVECTOR v = XMVector3Length(move);
	float length = XMVectorGetX(v);
	XMFLOAT3 dir;
	XMStoreFloat3(&dir, Pos);
	RayCastData data;
	data.start = transform_.position_;
	data.dir = dir;
	Model::RayCast(h_model, &data);
	if (data.hit && data.dist <= length && data.dist != 0)
	{
		*pos += ScratchWall(data.normal, vPos);
	}
	else
	{
		*pos += move;
	}
}

XMVECTOR Player::ScratchWall(XMVECTOR normal, XMVECTOR pos)
{
	XMVECTOR FixPos = { 1,0,1,0 };
	return XMVector3Normalize(pos - XMVector3Dot(pos, normal) * normal) * FixPos;
}

void Player::Run()
{
	move = { 0, 0, runSpeed_ };
	moveX = { runSpeed_, 0, 0 };
	viewHeigt_ = defaultHeigt_;
}