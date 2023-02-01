#pragma once
#include "Engine/GameObject.h"

class Player : public GameObject
{
    //���f���ԍ�
    int hModel_;
    int hMapModel;
    int second_;
    //�ړ��X�s�[�h
    float moveSpeed_;
    float runSpeed_;
    float crouchDownSpeed_;

    bool canJump;
    float jumpPower_;
    float jumpPowerDefault_;
    float gravity_;
    //���_����
    float viewHeigt_;
    float defaultHeigt_;
    float crouchDownHeigt_;

    //�e�̃X�s�[�h
    float bulletSpeed_;
    float recoil_;

    typedef struct
    {
        float x;
        float y;
    }CamSpeed;
    //�J�������x�ݒ�
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
    XMVECTOR prePos;
    XMFLOAT3 move;
    XMFLOAT3 moveX;
    XMVECTOR vMove;
    XMVECTOR vMoveX;
    XMVECTOR vPos;
public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void MovePlayerF();
    void MovePlayerB();
    void MovePlayerR();
    void MovePlayerL();
    void CrouchDown();
    void Run();
    void PlayerJump();
    bool IsHit(XMVECTOR pos, XMVECTOR move, int h_model);
    void MoveHit(XMVECTOR *pos, XMVECTOR move, int h_model);
    XMVECTOR ScratchWall(XMVECTOR normal, XMVECTOR pos);


};