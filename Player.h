#pragma once
#include "Engine/GameObject.h"

class Player : public GameObject
{
    //モデル番号
    int hModel_;
    //移動スピード
    float moveSpeed_;
    //視点高さ
    float viewHeigt_;
    //弾のスピード
    float bulletSpeed_;
    float recoil_;
    typedef struct
    {
        float x;
        float y;
    }CamSpeed;
    //カメラ感度設定
    CamSpeed camSpeed_;

    enum MoveFlag
    {
        run = 0x001,    
        jamp = 0x002,    
        crouchDown = 0x004,   
    };
    MoveFlag moveFlag_;
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