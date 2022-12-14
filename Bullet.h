#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Bullet : public GameObject
{
    //モデル番号
    int hModel_;    
    //移動量
    XMFLOAT3 move_; 
    float bulletLanding_;
public:
    //コンストラクタ
    Bullet(GameObject* parent);

    //デストラクタ
    ~Bullet();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //移動量セット
    void SetMove(XMFLOAT3 move) { move_ = move; }

};