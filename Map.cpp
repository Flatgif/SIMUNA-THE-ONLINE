#include "Map.h"
#include<stdio.h>
#include <stdlib.h>
#include<time.h>
#include <conio.h>
#include <ctype.h>
#include "Engine/Model.h"


//�R���X�g���N�^
Map::Map(GameObject* parent)
	:GameObject(parent, "Map")
{
}

//�f�X�g���N�^
Map::~Map()
{
}

//������
void Map::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_[0] = Model::Load("Floor.fbx");
	assert(hModel_ >= 0);
}

//�X�V
void Map::Update()
{
}

//�`��
void Map::Draw()
{
		Model::SetTransform(hModel_[0], transform_);
		Model::Draw(hModel_[0]);
}

//�J��
void Map::Release()
{
}



