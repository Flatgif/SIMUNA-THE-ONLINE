#include "TestScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "CamTarget.h"




#include "Stage.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	Instantiate<Stage>(this);
	//Instantiate<Map>(this);
	Instantiate<Player>(this); 
	Instantiate<Enemy>(this);
	//Instantiate<CamTarget>(this);





}

//�X�V
void TestScene::Update()
{
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}
