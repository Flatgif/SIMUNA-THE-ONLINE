#include "Map.h"
#include<stdio.h>
#include <stdlib.h>
#include<time.h>
#include <conio.h>
#include <ctype.h>
#include "Engine/Model.h"


//コンストラクタ
Map::Map(GameObject* parent)
	:GameObject(parent, "Map"), width_(31)
{
}

//デストラクタ
Map::~Map()
{
}

//初期化
void Map::Initialize()
{
	//モデルデータのロード
	hModel_[0] = Model::Load("sikaku.fbx");

	Make();
}

//更新
void Map::Update()
{
}

//描画
void Map::Draw()
{
	for (int i = 0; i < width_; i++)
	{
		for (int j = 0; j < width_ ; j++)
		{
			int type = map_[i][j].type;
			transform_.position_.x = i;
			transform_.position_.z = j;
			transform_.position_.y = 0;
			Model::SetTransform(hModel_[type], transform_);
			Model::Draw(hModel_[type]);

		}
	}

}

//開放
void Map::Release()
{
}

void Map::Make()
{
	for (int i = 0; i < width_; i++)
	{
		for (int j = 0; j < width_; j++)
		{
			map_[i][j].type = 0;
		}
	}

}



