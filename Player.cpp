#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Map.h"
#include "Bullet.h"
#include <corecrt_math_defines.h>

#define DEBUG


//�R���X�g���N�^
Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), second_(0),canJump(true)
	,moveSpeed_(0.1f), viewHeigt_(10.0f), bulletSpeed_(2.0f), recoil_(0.2f), defaultHeigt_(10.0f), jumpPowerDefault_(1.0f), gravity_(0.1f)
	, crouchDownHeigt_(defaultHeigt_ / 2), crouchDownSpeed_(moveSpeed_ / 2), runSpeed_(moveSpeed_ * 2)
	, vMove({ 0.0f, 0.0f, 0.0f, 0.0f }), vMoveX({ 0.0f, 0.0f, 0.0f, 0.0f }), vPos({ 0.0f, 0.0f, 0.0f, 0.0f }), move({ 0,0,0 }), moveX({ 0,0,0 })
{
	camSpeed_.x = 2.0f;
	camSpeed_.y = 1.0f;
	hMapModel = -1;
	jumpPower_ = jumpPowerDefault_;

}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("player1.fbx");
	assert(hModel_ >= 0);
	transform_.scale_ = { 0.5f,0.5f,0.5f };
}

//�X�V
void Player::Update()
{

		
	static int Count = 0;
	
	if (Count > 120)
	{
		second_++;
		Count = 0;
	}
	Count++;
	//Camera�̎�

	//Y����()�x��];
	XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	//x����()�x��];
	XMMATRIX mRotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
	//position���x�N�g���ɕϊ�
	vPos = XMLoadFloat3(&transform_.position_);


	//�ړ���
	move = { 0, 0, moveSpeed_ };
	moveX = { moveSpeed_, 0, 0 };

	//�ړ����͏���
	if (canJump && Input::IsKeyDown(DIK_SPACE))
	{
		canJump = false;
		jumpPower_ = jumpPowerDefault_;
	}
	if (canJump == false)
	{
		PlayerJump();
	}
	if (Input::IsKey(DIK_Q))
	{
		XMFLOAT3 a = { 0,1,0 };
	    MoveHit(&vPos, XMLoadFloat3(&a) , hMapModel);
	}
	if (Input::IsKey(DIK_E))
	{
		XMFLOAT3 a = { 0,-1,0 };
		MoveHit(&vPos, XMLoadFloat3(&a), hMapModel);
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
	default:
		viewHeigt_ = defaultHeigt_;
		//moveFlag_ = noMove;
		break;
	}
	//�|�W�V�������f
	vMove = XMLoadFloat3(&move);
	vMoveX = XMLoadFloat3(&moveX);

	vMove = XMVector3TransformCoord(vMove, mRotate);
	vMoveX = XMVector3TransformCoord(vMoveX, mRotate);
	RayCastData d;
	XMVECTOR normal = d.normal;

	XMStoreFloat3(&transform_.position_, vPos);

	//Camera�̏���

	XMFLOAT3 camPos;
	//�}�E�X�̈ړ���
	XMFLOAT3 mouseMove = Input::GetMouseMove();
	static float mouseZ = 0;
	mouseZ += mouseMove.z;
	//Camera�̈ʒu
	//XMVECTOR vCam = XMVectorSet(0, 0,-0.0000001 , 0);
	if (mouseZ > 0)
		mouseZ = 0;
	XMVECTOR vCam = XMVectorSet(0, 0, mouseZ/10 - 0.000001, 0);

	vCam = XMVector3TransformCoord(vCam, mRotateX);
	vCam = XMVector3TransformCoord(vCam, mRotate);


	//���_�̉�]�i�}�E�X�̈ړ��ʁj
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

	//Camera���f
	XMStoreFloat3(&camPos, vPos + vCam);
	XMVECTOR myself = XMLoadFloat3(&camPos);
	XMVECTOR target = XMLoadFloat3(&transform_.position_);
	Camera::SetPosition(camPos);
	Camera::SetTarget(transform_.position_);

	//�}�b�v�I�u�W�F�N�g��T��
	Map* pMap = (Map*)FindObject("Map");
	// ���̃��f���ԍ����擾
	hMapModel = pMap->GetModelHandle(0);

	RayCastData data;
	//���C�̔��ˈʒu
	XMFLOAT3 startPos = transform_.position_;
	startPos.y += 1;
	data.start = startPos;
	data.start.y = 0;
	//���C�̕���
	data.dir = XMFLOAT3(0, -1, 0);
	//���C�𔭎�
	Model::RayCast(hMapModel, &data);
	//if (!data.hit)
	//{
	//	//moveFlag_ = noMove;
	//	prePos = transform_.position_;
	//}
	//if (data.hit)
	//{
	//	if (canJump)
	//	{
	//		transform_.position_.y = -data.dist;

	//	}
	//}

	if (Input::IsMouseButton(0x00))
	{
		transform_.rotate_.x -= recoil_;
		Bullet* pBullet = Instantiate<Bullet>(GetParent()->GetParent());
		XMFLOAT3 bulletPos = transform_.position_;
		XMVECTOR move = (target - myself);
		//���̂܂܂��Ƒ�C�̒����Œe�̑��x�����܂�̂Ńx�N�g���𐳋K��
		move = XMVector3Normalize(move);
		//���K�����Ē���1�̒P�ʃx�N�g���ɂ����l�ɂ����Ă������肷�邱�ƂŒ����ł���
		move *= bulletSpeed_;
		XMStoreFloat3(&camPos, move);
		pBullet->SetPosition(transform_.position_);
		pBullet->SetMove(camPos);
	}
#ifdef DEBUG 
	static XMFLOAT3 inipos = transform_.position_;
	if (Input::IsKey(DIK_F))
	{
		transform_.position_ = inipos;
	}
	//�����I��
	if (Input::IsKey(DIK_ESCAPE))
	{
		PostQuitMessage(0);
	}

#endif // DEBUG Then


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

void Player::MovePlayerF()
{
	MoveHit(&vPos, vMove, hMapModel);
}

void Player::MovePlayerB()
{
	MoveHit(&vPos, -vMove, hMapModel);
}

void Player::MovePlayerR()
{
	MoveHit(&vPos, vMoveX, hMapModel);
}

void Player::MovePlayerL()
{
	MoveHit(&vPos, -vMoveX, hMapModel);
}

void Player::PlayerJump()
{
	XMFLOAT3 jump = { 0,jumpPower_,0 };
	XMVECTOR vJump = XMLoadFloat3(&jump);
	if (IsHit(vPos, vJump, hMapModel))
	{
		if (jumpPower_ >= 0)
		{
			jumpPower_ = -gravity_;
		}
		else
		{
			canJump = true;
		}
	}
	else
	{
		vPos += vJump;
		XMStoreFloat3(&transform_.position_, vPos);
		jumpPower_ -= gravity_;
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