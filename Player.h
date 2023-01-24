#pragma once
#include "Engine/GameObject.h"

class Player : public GameObject
{
    //モデル番号
    int hModel_;
    int hGroundModel;
    //移動スピード
    float moveSpeed_;
    float runSpeed_;
    float crouchDownSpeed_;

    float jumpPower_;
    float jumpPowerDefault_;
    float gravity_;
    //視点高さ
    float viewHeigt_;
    //弾のスピード
    float bulletSpeed_;
    float recoil_;
    float defaultHeigt_;
    float crouchDownHeigt_;
    typedef struct
    {
        float x;
        float y;
    }CamSpeed;
    //カメラ感度設定
    CamSpeed camSpeed_;

    enum MoveFlag
    {
        noMove = 1<<0,
        walk = 1<<1,
        run = 1<<2,    
        jump = 1<<3,   
        crouchDown = 1<<4,
    };
    int  moveFlag_;
    XMFLOAT3 prePos;
    XMFLOAT3 move;
    XMFLOAT3 moveX;
    XMFLOAT3 jump_;
    XMVECTOR vMove;
    XMVECTOR vMoveX;
    XMVECTOR vPos;
    XMVECTOR vJump;
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


    void MovePlayerF();
    void MovePlayerB();
    void MovePlayerR();
    void MovePlayerL();
    void CrouchDown();
    void Run();
    void JumpPlayer();
    bool IsHit(XMVECTOR pos, XMVECTOR move, int h_model);
    void MoveHit(XMVECTOR *pos, XMVECTOR move, int h_model);
    XMVECTOR ScratchWall(XMVECTOR normal, XMVECTOR pos);



};