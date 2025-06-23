//=======================
//
//ウィンドウ表示処理:main.cpp
//Author Kuramaesatoshi
//
//=======================
#include<Windows.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
//グローバル変数

int nFPS = 0;
CManager* g_pManager = nullptr;

//===============
//メイン関数
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

	//	ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成
	hWnd = CreateWindowEx(0,						//拡張ウィンドウスタイル
		CLASS_NAME,				//ウィンドウクラスの名前
		WINDOW_NAME,			//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,	//ウィンドウスタイル
		CW_USEDEFAULT,			//ウィンドウの左上X座標
		CW_USEDEFAULT,			//ウィンドウの左上Y座標
		(rect.right - rect.left),			//ウィンドウの幅
		(rect.bottom - rect.top),			//ウィンドウの高さ
		NULL,					//親ウィンドウのハンドル
		NULL,					//メニューハンドルまたは子ウィンドウID
		hInstance,				//インスタントハンドル
		NULL);					//ウィンドウ作成データ



	//全オブジェクト生成
	g_pManager = new CManager();
	//初期化処理
	g_pManager->Init(hInstance, hWnd, TRUE);

	if (g_pManager == nullptr)
	{
		return-1;
	}
	//分解能を設定
	{
		timeBeginPeriod(1);
		dwCurrentTime = 0;
		dwExecLastTime = timeGetTime();
		dwFrameCount = 0;
		dwFPSLastTime = timeGetTime();
	}
	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージグループを抜ける
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
			//FPSを計測
				nFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;	//FPSを測定した時刻を保存
				dwFrameCount = 0;					//フレームカウントをクリア
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60分の1秒の経過
				dwExecLastTime = dwExecLastTime;
				//諸々の処理
				g_pManager->Update();
				g_pManager->Draw();
				dwFrameCount++;
			}
		}
	}

	//終了処理
	g_pManager->Uninit();
	delete g_pManager;


	//分解能を戻す
	timeEndPeriod(1);
	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}



//ウィンドウプロシージャ
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static POINT pos = { 100,100 };
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	int nID;
	static HWND hWndEditOutput;

	switch (uMsg)
	{

	case WM_DESTROY:
		//WM_QUITにメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:

			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);
			if (nID == IDYES)
			{
				//ウィンドウを閉じる
				DestroyWindow(hWnd);
			}
			break;
		}
		break;


	case WM_CLOSE:				//閉じるボタンを押した時
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);
		if (nID == IDYES)
		{
			//ウィンドウを破棄
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


//FPS値を返す
int GetFPS()
{
	return nFPS;
}

