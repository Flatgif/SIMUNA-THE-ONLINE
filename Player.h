#pragma once
#include "Engine/GameObject.h"

class Player : public GameObject
{

    const FLOAT JUMPSPEED = 5.0f;   //�W�����v���x
    const FLOAT GRAVITY = 0.5f;     //�d��


    //���f���ԍ�
    int hModel_;
    //�ړ��X�s�[�h
    float moveSpeed_;
    //���_����
    float viewHeigt_;
    //�e�̃X�s�[�h
    float bulletSpeed_;
    typedef struct
    {
        float x;
        float y;
    }CamSpeed;
    //�J�������x�ݒ�
    CamSpeed camSpeed_;

    
    //�W�����v�֘A
    bool jumpFlg;   //�W�����v�t���O
    float initVec = JUMPSPEED;//�W�����v�̏����x 
    float checkYG;          //�W�����v����y���W��ۑ�����ϐ�



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