#include "PlayerHead.h"
#include "Engine/Model.h"


//コンストラクタ
PlayerHead::PlayerHead(GameObject* parent)
	:GameObject(parent, "PlayerHead")
{
}

//デストラクタ
PlayerHead::~PlayerHead()
{
}

//初期化
void PlayerHead::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("floor.fbx");
	assert(hModel_ >= 0);
}

//更新
void PlayerHead::Update()
{
}

//描画
void PlayerHead::Draw()
{
		Model::SetTransform(hModel_, transform_);
		Model::Draw(hModel_);
}

//開放
void PlayerHead::Release()
{
}