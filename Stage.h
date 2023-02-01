#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Stage : public GameObject
{

    const int MAP_ROW = 30;
    const int MAP_COL = 30;
    const int MAP_SIZE = 30;


    int hModel_[4];
    int map_[30][30];

    struct Resporn
    {
        int x;
        int z;
    };
    Resporn resPos;
    
public:

    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

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

    //���f���ԍ��擾
    int GetModelHandle(int modelNum) { return hModel_[modelNum]; }
    
    //���X�|�[���ʒu��Ԃ�
    int GetPointX() { return resPos.x; }
    int GetPointZ() { return resPos.z; }
};