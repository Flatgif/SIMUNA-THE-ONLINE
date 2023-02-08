#pragma once
#include "Engine/GameObject.h"
#include "Map.h"
#include "Engine/Model.h"

//���������Ǘ�����N���X
class Bullet : public GameObject
{
    //���f���ԍ�
    int hModel_;    
    //�ړ���
    XMFLOAT3 move_; 
    float bulletLanding_;
    int hMapModel_;
public:
    //�R���X�g���N�^
    Bullet(GameObject* parent);

    //�f�X�g���N�^
    ~Bullet();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�ړ��ʃZ�b�g
    void SetMove(XMFLOAT3 move) { move_ = move; }

    bool Hit(XMVECTOR move ,int h_model, RayCastData* data);

};