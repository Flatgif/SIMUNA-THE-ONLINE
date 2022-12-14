#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Map.h"
#include "Bullet.h"

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1),moveSpeed_(0.9f),viewHeigt_(10.0f), bulletSpeed_(0.8f)
{
	camSpeed_.x = 2.0f;
	camSpeed_.y = 1.0f;
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
	//マップオブジェクトを探す
	Map* pMap = (Map*)FindObject("Map");    
	// 床のモデル番号を取得
	int hGroundModel = pMap->GetModelHandle(0);    
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
	if (data.hit)
	{
		transform_.position_.y = -data.dist + viewHeigt_;
	}

	//Cameraの軸
	 
	//Y軸で()度回転;
	XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   
	//x軸で()度回転;
	XMMATRIX mRotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));   
	//positionもベクトルに変換
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

	//移動量
	XMFLOAT3 move = { 0, 0, moveSpeed_};
	XMFLOAT3 moveX = { moveSpeed_, 0, 0 };

	XMVECTOR vMove = XMLoadFloat3(&move);
	XMVECTOR vMoveX = XMLoadFloat3(&moveX);
	vMove = XMVector3TransformCoord(vMove, mRotate);
	vMoveX = XMVector3TransformCoord(vMoveX, mRotate);


	//移動入力処理
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
	//ポジション反映
	XMStoreFloat3(&transform_.position_, vPos);


	//Cameraの処理

	XMFLOAT3 camPos;
	//Cameraの位置
	XMVECTOR vCam = XMVectorSet(0, 0, -0.0001, 0);
	vCam = XMVector3TransformCoord(vCam, mRotateX);
	vCam = XMVector3TransformCoord(vCam, mRotate);

	//マウスの移動量を正規化
	XMFLOAT3 mouseMove = Input::GetMouseMove();
	XMVECTOR vMouseMove = XMLoadFloat3(&mouseMove);
	vMouseMove = XMVector3Normalize(vMouseMove);
	XMStoreFloat3(&mouseMove, vMouseMove);

	//視点の回転（マウスの移動量）
	transform_.rotate_.x += mouseMove.y * camSpeed_.y;
	transform_.rotate_.y += mouseMove.x * camSpeed_.x;
	if (transform_.rotate_.x >= 89)
	{
		transform_.rotate_.x = 89;
	}
	if (transform_.rotate_.x <= -89)
	{
		transform_.rotate_.x = -89;
	}

	XMStoreFloat3(&camPos, vPos + vCam);
	XMVECTOR myself = XMLoadFloat3(&camPos);
	XMVECTOR target = XMLoadFloat3(&transform_.position_);




	Camera::SetPosition(camPos);
	Camera::SetTarget(transform_.position_);


	if (Input::IsMouseButton(0))
	{
		transform_.rotate_.x -= 0.15f;
		Bullet* pBullet = Instantiate<Bullet>(GetParent()->GetParent());
		XMFLOAT3 bulletPos= transform_.position_;
		XMVECTOR move = (target- myself);
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