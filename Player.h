#pragma once
#include "Engine/GameObject.h"

class Player : public GameObject
{
    //モデル番号
    int hModel_;
    //移動スピード
    float moveSpeed_;
  
    typedef struct
    {
        float x;
        float y;
    }CamSpeed;//カメラ感度設定
    CamSpeed camSpeed_;
public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};