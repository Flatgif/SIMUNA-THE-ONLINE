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
	hModel_[0] = Model::Load("WallSample.fbx");
	assert(hModel_ >= 0);
}

//�X�V
void Map::Update()
{
}

//�`��
void Map::Draw()
{
	for (int i = 0; i < 1; i++)
	{
		Model::SetTransform(hModel_[i], transform_);
		Model::Draw(hModel_[i]);
	}
}

//�J��
void Map::Release()
{
}



