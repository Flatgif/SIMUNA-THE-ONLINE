//#include "Map.h"
//#include<stdio.h>
//#include <stdlib.h>
//#include<time.h>
//#include <conio.h>
//#include <ctype.h>
//#include "Engine/Model.h"
//
//
////コンストラクタ
//Map::Map(GameObject* parent)
//	:GameObject(parent, "Map")
//{
//}
//
////デストラクタ
//Map::~Map()
//{
//}
//
////初期化
//void Map::Initialize()
//{
//	//モデルデータのロード
//	hModel_[0] = Model::Load("floor.fbx");
//	assert(hModel_ >= 0);
//	hModel_[1] = Model::Load("Wall.fbx");
//	assert(hModel_ >= 0);
//	transform_.scale_ = { 10,10,10 };
//}
//
////更新
//void Map::Update()
//{
//}
//
////描画
//void Map::Draw()
//{
//	for (int i = 0; i < 1; i++)
//	{
//		Model::SetTransform(hModel_[i], transform_);
//		Model::Draw(hModel_[i]);
//	}
//}
//
////開放
//void Map::Release()
//{
//}