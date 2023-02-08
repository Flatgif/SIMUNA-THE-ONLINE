#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class PlayerHead: public GameObject
{
    float heigt_;
    int hModel_;
    int hStageModel_;
public:

    //コンストラクタ
    PlayerHead(GameObject* parent);

    //デストラクタ
    ~PlayerHead();

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

    //プレイヤーに追従するカメラ呼び出し
    void CallCam();

    //カメラの視点マウスにする
    void ViewRotate();

};