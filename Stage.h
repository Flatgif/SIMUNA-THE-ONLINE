#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
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

    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //そこは壁？
    bool IsWall(int x, int z);

    //モデル番号取得
    int GetModelHandle(int modelNum) { return hModel_[modelNum]; }
    
    //リスポーン位置を返す
    int GetPointX() { return resPos.x; }
    int GetPointZ() { return resPos.z; }
};