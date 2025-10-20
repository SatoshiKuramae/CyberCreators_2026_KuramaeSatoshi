// Collision.h
#pragma once
#include <d3dx9.h>

enum class CCollisionDir
{
    NONE,   // �������Ă��Ȃ�
    TOP,    // �ォ�瓖������
    BOTTOM, // �����瓖������
    LEFT,   // �����瓖������
    RIGHT   // �E���瓖������
};

//�����蔻��
class CCollision
{
public:
    // AABB�i�����s��`�j�̓����蔻��(posA,sizeA=�������������肵�����I�u�W�F�N�g���.posB,sizeB=�������������肵��������̏��)
    static CCollisionDir CheckRectCollision(const D3DXVECTOR3& posA, const D3DXVECTOR3& sizeA,
        const D3DXVECTOR3& posB, const D3DXVECTOR3& sizeB);
};
