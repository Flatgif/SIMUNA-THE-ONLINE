#pragma once
#include "Engine/GameObject.h"
#include <vector>
#include <iostream>

//���������Ǘ�����N���X
class Enemy : public GameObject
{
    typedef struct Status
    {
        XMFLOAT3 pos;
        XMVECTOR dir;
        bool shootFlag;
    }EnemyInfo;
    std::vector<EnemyInfo> enemy;
public:
    //�R���X�g���N�^
    Enemy(GameObject* parent);

    //�f�X�g���N�^
    ~Enemy();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //��M
    void Reception();
};