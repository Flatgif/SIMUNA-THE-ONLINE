#pragma once
#include "Engine/GameObject.h"
#include <vector>

//���������Ǘ�����N���X
class Map : public GameObject
{
    int hModel_[1];
    int width_;
    struct
    {
        int type;
    }map_[100][100];

   // std::vector<std::vector<map_>> map;

public:
    //�R���X�g���N�^
    Map(GameObject* parent);

    //�f�X�g���N�^
    ~Map();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void Make();
};