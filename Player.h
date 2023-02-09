#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"

class Player : public GameObject
{
    //モデル番号
    int hModel_;
    int hMapModel_[4];
    //プレイヤーの位置ベクトル
    XMVECTOR vPos_;
    //移動量のベクトル
    XMVECTOR vMove_;
    float dashSpeed_;
    float moveSpeed_;
    XMMATRIX mRotateX_;
    XMMATRIX mRotate_;
    float camDist_;
    //プレイヤーの状態遷移
    typedef enum state
    {
        noMove = 1<<0,
        move = 1<<1,
        dash = 1<<2,

    }playerState;
    playerState playerstate_;

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

    //プレイヤーを移動させる
    void PlayerMove();

    void PlayerSlideMove();


    /// <summary>
    /// 移動量をプレイヤーのポジションに追加していく
    /// </summary>
    /// <param name="m">移動量</param>
    void AddMove(XMVECTOR m) { playerstate_ = move; vMove_ += m; }

    /// <summary>
    /// モデルとの当たり判定
    /// </summary>
    /// <param name="h_model">当たり判定をするモデル</param>
    /// <returns></returns>
    bool IsHit(int h_model, RayCastData* data);

    //プレイヤーに追従するカメラ呼び出し
    void CallCam();
    
    //カメラの視点マウスにする
    void ViewRotate();

    XMVECTOR ScratchWall(XMVECTOR normal, XMVECTOR pos);

    void shoot();

};