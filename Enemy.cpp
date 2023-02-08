#include "Enemy.h"
#include "Bullet.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy"),hModel_(-1)
{
}

//�f�X�g���N�^
Enemy::~Enemy()
{
}

//������
void Enemy::Initialize()
{
	transform_.position_ = XMFLOAT3(0, 0, 0);
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Player.fbx");
	assert(hModel_ >= 0);
}

//�X�V
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
	//��]������
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

//�`��
void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

}

//�J��
void Enemy::Release()
{
}

void Enemy::Reception()
{
}

float Enemy::Calculate()
{
	XMVECTOR dir = enemy.dir;
	//�p�x�����߂邽�߂ɒ������P�ɂ���i���K���j
	dir = XMVector3Normalize(dir);

	//��ƂȂ鉜�����̃x�N�g��
	XMVECTOR front = { 0, 0, 1, 0 };

	//front��move�̓��ς����߂�
	XMVECTOR vecDot = XMVector3Dot(front, dir);
	float dot = XMVectorGetX(vecDot);

	//�����Ă�p�x�����߂�i���W�A���j
	float angle = acos(dot);


	//front��move�̊O�ς����߂�
	XMVECTOR cross = XMVector3Cross(front, dir);

	//�O�ς̌��ʂ�Y���}�C�i�X�@���@�������@���@���ɐi��ł�
	if (XMVectorGetY(cross) < 0)
	{
		angle *= -1;
	}
	return angle;
}
