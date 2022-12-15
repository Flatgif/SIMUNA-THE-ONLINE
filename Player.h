#pragma once
#include "Engine/GameObject.h"

class Player : public GameObject
{
    //���f���ԍ�
    int hModel_;
    //�ړ��X�s�[�h
    float moveSpeed_;
    //���_����
    float viewHeigt_;
    //�e�̃X�s�[�h
    float bulletSpeed_;
    float recoil_;
    float runSpeed_;
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
        noMove = 0x000,
        run = 0x001,    
        jamp = 0x002,    
        crouchDown = 0x004,   
    };
    int  moveFlag_;
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
};