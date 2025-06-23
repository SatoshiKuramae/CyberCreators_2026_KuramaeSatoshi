//===============================================================================
//
//main.h
//Author Kuramaesatoshi
//===============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_
#include"d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"
#include <Windows.h>
#include "renderer.h"

constexpr int MAX_NUM(256);
#define CLASS_NAME		"�|�[���[�A�N�Z��"			//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME		"�|�[���[�A�N�Z��"	//�E�B���h�E�̖��O�i�L���v�V�����ɕ\���j


//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")		//�`�揈���ɕK�v
#pragma	comment(lib,"d3dx9.lib")	//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")	//DirectX�R���|�[�l���g�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")	//�V�X�e�������擾���ɕK�v
#pragma comment(lib,"dinput8.lib")	//���͏����ɕK�v

//�}�N����`
constexpr int  SCREEN_WIDTH(1280);
constexpr int  SCREEN_HEIGHT(720);
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)
//RGBA
constexpr int RED(255);
constexpr int GREEN(255);
constexpr int BLUE(255);
constexpr int A(255);
constexpr int NUMOBJECT(51200);
constexpr float MAXPOS_X(1280.0f);
constexpr float MAXPOS_Y(720.0f);
constexpr float MINPOS(0.0f);
constexpr float PLAYER_SPEED(18.0f);
constexpr float BLOCK_X(80.0f);
constexpr float BLOCK_Y(80.0f);
constexpr float PLAYERCOLL(40.0f);
constexpr float BLOCKCOLLISION_X(BLOCK_X - 5.0f);
constexpr float BLOCKCOLLISION_Y(BLOCK_X - 5.0f);
constexpr float RESETPOS((BLOCK_X + PLAYERCOLL) + 0.1f);
constexpr float CAMERAPOS_V_Y(400.0f);
constexpr float CAMERAPOS_V_Z(1200.0f);
constexpr int NUM_MODEL(15);
constexpr int NUMBLOCK(60);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int GetFPS();

typedef struct
{
	D3DXVECTOR3 pos;	//���_���
	float rhw;			//���W�ϊ��p�W��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;
}VERTEX_2D;
#endif




