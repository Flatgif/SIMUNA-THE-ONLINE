#include "TestScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	Instantiate<Map>(this);
	Instantiate<Player>(this); 
	Instantiate<Enemy>(this);
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
