#pragma once
#include "Engine/GameObject.h"

class Player : public GameObject
{
    //���f���ԍ�
    int hModel_;
    //�ړ��X�s�[�h
    float moveSpeed_;
  
    typedef struct
    {
        float x;
        float y;
    }CamSpeed;//�J�������x�ݒ�
    CamSpeed camSpeed_;
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