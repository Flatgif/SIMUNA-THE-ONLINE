#include "PlayerHead.h"
#include "Engine/Model.h"


//�R���X�g���N�^
PlayerHead::PlayerHead(GameObject* parent)
	:GameObject(parent, "PlayerHead")
{
}

//�f�X�g���N�^
PlayerHead::~PlayerHead()
{
}

//������
void PlayerHead::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("floor.fbx");
	assert(hModel_ >= 0);
}

//�X�V
void PlayerHead::Update()
{
}

//�`��
void PlayerHead::Draw()
{
		Model::SetTransform(hModel_, transform_);
		Model::Draw(hModel_);
}

//�J��
void PlayerHead::Release()
{
}