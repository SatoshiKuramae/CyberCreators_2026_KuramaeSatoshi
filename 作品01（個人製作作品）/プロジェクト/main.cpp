//=======================
//
//�E�B���h�E�\������:main.cpp
//Author Kuramaesatoshi
//
//=======================
#include<Windows.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
//�O���[�o���ϐ�

int nFPS = 0;
CManager* g_pManager = nullptr;

//===============
//���C���֐�
//===============
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	DWORD dwFrameCount;
	DWORD dwFPSLastTime;
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)
	};

	HWND hWnd;
	MSG msg;

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//	�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,						//�g���E�B���h�E�X�^�C��
		CLASS_NAME,				//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,			//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,	//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,			//�E�B���h�E�̍���X���W
		CW_USEDEFAULT,			//�E�B���h�E�̍���Y���W
		(rect.right - rect.left),			//�E�B���h�E�̕�
		(rect.bottom - rect.top),			//�E�B���h�E�̍���
		NULL,					//�e�E�B���h�E�̃n���h��
		NULL,					//���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,				//�C���X�^���g�n���h��
		NULL);					//�E�B���h�E�쐬�f�[�^



	//�S�I�u�W�F�N�g����
	g_pManager = new CManager();
	//����������
	g_pManager->Init(hInstance, hWnd, TRUE);

	if (g_pManager == nullptr)
	{
		return-1;
	}
	//����\��ݒ�
	{
		timeBeginPeriod(1);
		dwCurrentTime = 0;
		dwExecLastTime = timeGetTime();
		dwFrameCount = 0;
		dwFPSLastTime = timeGetTime();
	}
	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W�O���[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
			//FPS���v��
				nFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;	//FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;					//�t���[���J�E���g���N���A
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60����1�b�̌o��
				dwExecLastTime = dwExecLastTime;
				//���X�̏���
				g_pManager->Update();
				g_pManager->Draw();
				dwFrameCount++;
			}
		}
	}

	//�I������
	g_pManager->Uninit();
	delete g_pManager;


	//����\��߂�
	timeEndPeriod(1);
	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}



//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static POINT pos = { 100,100 };
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	int nID;
	static HWND hWndEditOutput;

	switch (uMsg)
	{

	case WM_DESTROY:
		//WM_QUIT�Ƀ��b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:

			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
			if (nID == IDYES)
			{
				//�E�B���h�E�����
				DestroyWindow(hWnd);
			}
			break;
		}
		break;


	case WM_CLOSE:				//����{�^������������
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
		if (nID == IDYES)
		{
			//�E�B���h�E��j��
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//FPS�l��Ԃ�
int GetFPS()
{
	return nFPS;
}

