#pragma once
#include "Engine/GameObject.h"

class Player : public GameObject
{
    //���f���ԍ�
    int hModel_;
    int hGroundModel;
    //�ړ��X�s�[�h
    float moveSpeed_;
    float runSpeed_;
    float crouchDownSpeed_;

    float jumpPower_;
    float jumpPowerDefault_;
    float gravity_;
    //���_����
    float viewHeigt_;
    //�e�̃X�s�[�h
    float bulletSpeed_;
    float recoil_;
    float defaultHeigt_;
    float crouchDownHeigt_;
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
    XMFLOAT3 prePos;
    XMFLOAT3 move;
    XMFLOAT3 moveX;
    XMFLOAT3 jump_;
    XMVECTOR vMove;
    XMVECTOR vMoveX;
    XMVECTOR vPos;
    XMVECTOR vJump;
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
    void JumpPlayer();
    bool IsHit(XMVECTOR pos, XMVECTOR move, int h_model);
    void MoveHit(XMVECTOR *pos, XMVECTOR move, int h_model);
    XMVECTOR ScratchWall(XMVECTOR normal, XMVECTOR pos);



};