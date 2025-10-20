#include "collision.h"

//“–‚½‚è”»’èˆ—
CCollisionDir CCollision::CheckRectCollision(const D3DXVECTOR3& posA, const D3DXVECTOR3& sizeA,
    const D3DXVECTOR3& posB, const D3DXVECTOR3& sizeB)
{
    bool isHit =
        (posA.x - sizeA.x < posB.x + sizeB.x &&
            posA.x + sizeA.x > posB.x - sizeB.x &&
            posA.y - sizeA.y < posB.y + sizeB.y &&
            posA.y + sizeA.y > posB.y - sizeB.y);

    if (!isHit) return CCollisionDir::NONE;

    // ====== Še•ûŒü‚Ì‰Ÿ‚µ‚İ—Ê‚ğŒvZ ======
    float overlapLeft = (posB.x + sizeB.x) - (posA.x - sizeA.x);
    float overlapRight = (posA.x + sizeA.x) - (posB.x - sizeB.x);
    float overlapTop = (posB.y + sizeB.y) - (posA.y - sizeA.y);
    float overlapBottom = (posA.y + sizeA.y) - (posB.y - sizeB.y);

    // Å¬‚Ìd‚È‚è•ûŒü‚ğ‹‚ß‚é
    float minOverlap = min(min(overlapLeft, overlapRight), min(overlapTop, overlapBottom));

    if (minOverlap == overlapTop)    return CCollisionDir::TOP;
    if (minOverlap == overlapBottom) return CCollisionDir::BOTTOM;
    if (minOverlap == overlapLeft)   return CCollisionDir::LEFT;
    if (minOverlap == overlapRight)  return CCollisionDir::RIGHT;

    return CCollisionDir::NONE;
}