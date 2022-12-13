#pragma once
#include "Engine/GameObject.h"
#include <vector>

//◆◆◆を管理するクラス
class Map : public GameObject
{
    int hModel_[2];

   // std::vector<std::vector<map_>> map;

public:
    //コンストラクタ
    Map(GameObject* parent);

    //デストラクタ
    ~Map();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //モデル番号取得
    int GetModelHandle(int modelNum) { return hModel_[modelNum]; }
};