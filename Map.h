#pragma once
#include "Engine/GameObject.h"
#include <vector>

//���������Ǘ�����N���X
class Map : public GameObject
{
    int hModel_[2];

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

    //���f���ԍ��擾
    int GetModelHandle(int modelNum) { return hModel_[modelNum]; }
};