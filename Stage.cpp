#include "Stage.h"
#include "Engine/CsvReader.h"
#include "Engine/Model.h"


//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{
    for (int i = 0; i < 4; i++)
    {
        hModel_[i] = -1;
    }

}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    hModel_[0] = Model::Load("Tile.fbx");
    assert(hModel_ >= 0);

    hModel_[1] = Model::Load("Wall.fbx");
    assert(hModel_ >= 0);

    hModel_[2] = Model::Load("Wall2.fbx");
    assert(hModel_ >= 0);

    hModel_[3] = Model::Load("resporn.fbx");
    assert(hModel_ >= 0);


    CsvReader csv;
    csv.Load("MapCSV.csv");


    for (int i = 0; i < MAP_ROW; i++)
    {
        for (int j = 0; j < MAP_COL; j++)
        {
            map_[i][MAP_SIZE - 1 - j] = csv.GetValue(i, j);

            if (map_[i][MAP_SIZE - 1 - j] == 3)
            {
                resPos.x = i;
                resPos.z = MAP_SIZE - 1 - j;
            }
        }
    }

}

//�X�V
void Stage::Update()
{
}

//�`��
void Stage::Draw()
{
    for (int x = 0; x < MAP_ROW; x++)                               //Wall�̏o���̏���
    {
        transform_.position_.x = x;                    //�`�}�X�ǔz�u

        for (int z = 0; z < MAP_COL; z++)                        //Wall�̏o���̏���

        {
            int type = map_[x][z]; //&&�ǂ������������� �}�b�v�Ƀu���b�N�̏���
            transform_.position_.x = x;                    //�`�}�X�ǔz�u
            transform_.position_.z = z;                   //�`�}�X�ǔz�u
            Model::SetTransform(hModel_[type], transform_); //�z��[0]��[1]�ŕǂ����������ł���
            Model::Draw(hModel_[type]);                    //�z��[0]��[1]�ŕǂ����������ł���
        }
    }
}

//�J��
void Stage::Release()
{
}

//�����͕ǂ��ǂ���
bool Stage::IsWall(int x, int z)
{
    //return map_[x][z] == 0 ? false : true;       �O�����Z�q

    return map_[x][z] == 1; //x z ���Preturn�ŕԂ�

    if (map_[x][z] == 1) //�܂��Ղ̂��A������[1]��������yes��no��return�Ԃ�
    {
        return false;
    }
    else
    {
        return true;
    }
}