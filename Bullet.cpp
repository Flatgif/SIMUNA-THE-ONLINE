#include "Bullet.h"
#include "Item.h"

//�R���X�g���N�^
Bullet::Bullet(GameObject* parent)
    :GameObject(parent, "Bullet")
{
}

//�f�X�g���N�^
Bullet::~Bullet()
{
}

//������
void Bullet::Initialize()
{
    Instantiate<Item>(this);
}

//�X�V
void Bullet::Update()
{
}

//�`��
void Bullet::Draw()
{
}

//�J��
void Bullet::Release()
{
}