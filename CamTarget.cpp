//#include "CamTarget.h"
//#include "Engine/Input.h"
//#include "Engine/Model.h"
//#include "Engine/Camera.h"
//
////コンストラクタ
//CamTarget::CamTarget(GameObject* parent)
//	:GameObject(parent, "CamTarget"), hModel_(-1)
//{
//}
//
////デストラクタ
//CamTarget::~CamTarget()
//{
//}
//
////初期化
//void CamTarget::Initialize()
//{
//	//モデルデータのロード
//	hModel_ = Model::Load("player.fbx");
//	assert(hModel_ >= 0);
//	Camera::SetPosition(XMFLOAT3(transform_.position_));
//	Camera::SetTarget(XMFLOAT3(transform_.position_.x, transform_.position_.y, 1));
//	Input::SetMousePosition(0, 0);
//
//}
//
////更新
//void CamTarget::Update()
//{
//	XMFLOAT3 preCamPos = Input::GetMousePosition();
//
//	XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸で()度回転
//	XMMATRIX mRotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));   //x軸で()度回転
//
//	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);//positionもベクトルに変換	
//	XMFLOAT3 tar = Input::GetMouseMove();
//	transform_.rotate_.x += tar.y;
//	transform_.rotate_.y += tar.x;
//	if (transform_.rotate_.x >= 90)
//	{
//		transform_.rotate_.x = 90;
//	}
//
//	XMFLOAT3 move = { 0, 0, 1.0f };
//	XMFLOAT3 moveX = { 1.0f, 0, 0 };
//	XMVECTOR vMove = XMLoadFloat3(&move);
//	XMVECTOR vMoveX = XMLoadFloat3(&moveX);
//	vMove = XMVector3TransformCoord(vMove, mRotate);
//	vMoveX = XMVector3TransformCoord(vMoveX, mRotate);
//	XMFLOAT3 targetPos = transform_.position_;
//	XMVECTOR vTargetPos = XMLoadFloat3(&targetPos);
//	Camera::SetPosition(XMFLOAT3(transform_.position_));
//
//
//
//
//	//vPos += vMove;
//	XMFLOAT3 camPos;
//	XMVECTOR vCam = XMVectorSet(0, 0, -0.0001, 0);
//	vCam = XMVector3TransformCoord(vCam, mRotateX);
//	vCam = XMVector3TransformCoord(vCam, mRotate);
//
//	XMStoreFloat3(&camPos, vPos + vCam);
//	XMVECTOR myself = XMLoadFloat3(&camPos);
//	XMVECTOR target = XMLoadFloat3(&transform_.position_);
//	Camera::SetPosition(camPos);
//	Camera::SetTarget(transform_.position_);
//
//
//}
//
////描画
//void CamTarget::Draw()
//{
//	Model::SetTransform(hModel_, transform_);
//	Model::Draw(hModel_);
//}
//
////開放
//void CamTarget::Release()
//{
//}