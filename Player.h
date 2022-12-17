#pragma once
#include "Engine/GameObject.h"

class Player : public GameObject
{

    const FLOAT JUMPSPEED = 5.0f;   //ジャンプ速度
    const FLOAT GRAVITY = 0.5f;     //重力


    //モデル番号
    int hModel_;
    //移動スピード
    float moveSpeed_;
    //視点高さ
    float viewHeigt_;
    //弾のスピード
    float bulletSpeed_;
    typedef struct
    {
        float x;
        float y;
    }CamSpeed;
    //カメラ感度設定
    CamSpeed camSpeed_;

    
    //ジャンプ関連
    bool jumpFlg;   //ジャンプフラグ
    float initVec = JUMPSPEED;//ジャンプの初速度 
    float checkYG;          //ジャンプ時のy座標を保存する変数



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