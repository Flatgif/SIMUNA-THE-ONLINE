#include "Stage.h"
#include "Engine/CsvReader.h"
#include "Engine/Model.h"


//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{
    for (int i = 0; i < 4; i++)
    {
        hModel_[i] = -1;
    }

}

//デストラクタ
Stage::~Stage()
{
}

//初期化
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

//更新
void Stage::Update()
{
}

//描画
void Stage::Draw()
{
    for (int x = 0; x < MAP_ROW; x++)                               //Wallの出現の処理
    {
        transform_.position_.x = x;                    //～個マス壁配置

        for (int z = 0; z < MAP_COL; z++)                        //Wallの出現の処理

        {
            int type = map_[x][z]; //&&どっちも揃ったら マップにブロックの処理
            transform_.position_.x = x;                    //～個マス壁配置
            transform_.position_.z = z;                   //～個マス壁配置
            Model::SetTransform(hModel_[type], transform_); //配列[0]か[1]で壁か床か調整できる
            Model::Draw(hModel_[type]);                    //配列[0]か[1]で壁か床か調整できる
        }
    }
}

//開放
void Stage::Release()
{
}

//そこは壁かどうか
bool Stage::IsWall(int x, int z)
{
    //return map_[x][z] == 0 ? false : true;       三項演算子

    return map_[x][z] == 1; //x z が１returnで返す

    if (map_[x][z] == 1) //まっぷのｘ、ｚが壁[1]だったらyesかnoでreturn返す
    {
        return false;
    }
    else
    {
        return true;
    }
}