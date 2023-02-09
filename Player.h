#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"

class Player : public GameObject
{
    //���f���ԍ�
    int hModel_;
    int hMapModel_[4];
    //�v���C���[�̈ʒu�x�N�g��
    XMVECTOR vPos_;
    //�ړ��ʂ̃x�N�g��
    XMVECTOR vMove_;
    float dashSpeed_;
    float moveSpeed_;
    XMMATRIX mRotateX_;
    XMMATRIX mRotate_;
    float camDist_;
    //�v���C���[�̏�ԑJ��
    typedef enum state
    {
        noMove = 1<<0,
        move = 1<<1,
        dash = 1<<2,

    }playerState;
    playerState playerstate_;

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

    //�v���C���[���ړ�������
    void PlayerMove();

    void PlayerSlideMove();


    /// <summary>
    /// �ړ��ʂ��v���C���[�̃|�W�V�����ɒǉ����Ă���
    /// </summary>
    /// <param name="m">�ړ���</param>
    void AddMove(XMVECTOR m) { playerstate_ = move; vMove_ += m; }

    /// <summary>
    /// ���f���Ƃ̓����蔻��
    /// </summary>
    /// <param name="h_model">�����蔻������郂�f��</param>
    /// <returns></returns>
    bool IsHit(int h_model, RayCastData* data);

    //�v���C���[�ɒǏ]����J�����Ăяo��
    void CallCam();
    
    //�J�����̎��_�}�E�X�ɂ���
    void ViewRotate();

    XMVECTOR ScratchWall(XMVECTOR normal, XMVECTOR pos);

    void shoot();

};