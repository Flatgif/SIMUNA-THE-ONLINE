#include "Bullet.h"
#include "Item.h"

//コンストラクタ
Bullet::Bullet(GameObject* parent)
    :GameObject(parent, "Bullet")
{
}

//デストラクタ
Bullet::~Bullet()
{
}

//初期化
void Bullet::Initialize()
{
    Instantiate<Item>(this);
}

//更新
void Bullet::Update()
{
}

//描画
void Bullet::Draw()
{
}

//開放
void Bullet::Release()
{
}