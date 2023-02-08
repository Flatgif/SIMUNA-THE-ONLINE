#pragma once
#include "Engine/GameObject.h"
#include <vector>
#include <iostream>

//◆◆◆を管理するクラス
class Enemy : public GameObject
{
    int hModel_;
    typedef struct Status
    {
        XMFLOAT3 pos;
        XMVECTOR dir;
        bool shootFlag;
    }EnemyInfo;
    EnemyInfo enemy;
public:
    //コンストラクタ
    Enemy(GameObject* parent);

    //デストラクタ
    ~Enemy();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //受信
    void Reception();

    //向き方向に回転
    float Calculate();
};