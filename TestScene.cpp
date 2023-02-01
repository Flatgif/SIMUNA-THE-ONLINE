#include "TestScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "CamTarget.h"




#include "Stage.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	Instantiate<Stage>(this);
	//Instantiate<Map>(this);
	Instantiate<Player>(this); 
	Instantiate<Enemy>(this);
	//Instantiate<CamTarget>(this);





}

//更新
void TestScene::Update()
{
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
