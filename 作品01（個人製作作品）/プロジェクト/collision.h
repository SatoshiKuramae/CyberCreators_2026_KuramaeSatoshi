// Collision.h
#pragma once
#include <d3dx9.h>

enum class CCollisionDir
{
    NONE,   // 当たっていない
    TOP,    // 上から当たった
    BOTTOM, // 下から当たった
    LEFT,   // 左から当たった
    RIGHT   // 右から当たった
};

//当たり判定
class CCollision
{
public:
    // AABB（軸平行矩形）の当たり判定(posA,sizeA=当たったか判定したいオブジェクト情報.posB,sizeB=当たったか判定したい相手の情報)
    static CCollisionDir CheckRectCollision(const D3DXVECTOR3& posA, const D3DXVECTOR3& sizeA,
        const D3DXVECTOR3& posB, const D3DXVECTOR3& sizeB);
};
