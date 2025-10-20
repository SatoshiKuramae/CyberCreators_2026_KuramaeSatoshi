#include "collision.h"

//�����蔻�菈��
CCollisionDir CCollision::CheckRectCollision(const D3DXVECTOR3& posA, const D3DXVECTOR3& sizeA,
    const D3DXVECTOR3& posB, const D3DXVECTOR3& sizeB)
{
    bool isHit =
        (posA.x - sizeA.x < posB.x + sizeB.x &&
            posA.x + sizeA.x > posB.x - sizeB.x &&
            posA.y - sizeA.y < posB.y + sizeB.y &&
            posA.y + sizeA.y > posB.y - sizeB.y);

    if (!isHit) return CCollisionDir::NONE;

    // ====== �e�����̉������ݗʂ��v�Z ======
    float overlapLeft = (posB.x + sizeB.x) - (posA.x - sizeA.x);
    float overlapRight = (posA.x + sizeA.x) - (posB.x - sizeB.x);
    float overlapTop = (posB.y + sizeB.y) - (posA.y - sizeA.y);
    float overlapBottom = (posA.y + sizeA.y) - (posB.y - sizeB.y);

    // �ŏ��̏d�Ȃ���������߂�
    float minOverlap = min(min(overlapLeft, overlapRight), min(overlapTop, overlapBottom));

    if (minOverlap == overlapTop)    return CCollisionDir::TOP;
    if (minOverlap == overlapBottom) return CCollisionDir::BOTTOM;
    if (minOverlap == overlapLeft)   return CCollisionDir::LEFT;
    if (minOverlap == overlapRight)  return CCollisionDir::RIGHT;

    return CCollisionDir::NONE;
}