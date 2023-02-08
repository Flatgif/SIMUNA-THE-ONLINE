#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class PlayerHead: public GameObject
{
    float heigt_;
    int hModel_;
    int hStageModel_;
public:

    //�R���X�g���N�^
    PlayerHead(GameObject* parent);

    //�f�X�g���N�^
    ~PlayerHead();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�����͕ǁH
    bool IsWall(int x, int z);

    //�v���C���[�ɒǏ]����J�����Ăяo��
    void CallCam();

    //�J�����̎��_�}�E�X�ɂ���
    void ViewRotate();

};