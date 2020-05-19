#include <windows.h> //������ ��� ����
#include "resource.h"

#define FIGURESIZE 30 //������ ������
#define BOARDSIZE 10 //���� ũ��
#define BOARDCORRECTION 60 //�� ũ��� ��ġ ����
static int GameBoard[3][BOARDSIZE][BOARDSIZE]= //������
{
	{//���� [0][10][10]
		{1,1,1,1,1,1,1,1,1,1},
		{0,0,1,0,1,0,1,0,1,1},
		{1,0,1,0,1,0,1,0,0,1},
		{1,0,1,0,1,0,1,1,0,1},
		{1,0,1,0,1,0,1,0,0,1},
		{1,0,1,0,1,0,1,0,1,1},
		{1,0,1,0,1,0,1,0,0,1},
		{1,0,1,0,1,0,1,1,0,1},
		{1,0,0,0,0,0,0,0,0,2},
		{1,1,1,1,1,1,1,1,1,1}
	},
	{//���� [1][10][10]
		{1,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,1},
		{1,1,1,0,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,1,0,1},
		{1,0,1,1,1,1,1,1,0,1},
		{1,0,1,0,0,0,1,1,0,1},
		{1,0,0,0,1,0,0,1,0,1},
		{1,0,1,1,1,1,0,1,0,1},
		{1,0,0,0,0,1,0,0,0,2},
		{1,1,1,1,1,1,1,1,1,1}
	},
	{//����� [2][10][10]
		{1,1,1,1,1,1,1,1,1,1},
		{0,0,0,1,0,1,0,0,0,1},
		{1,0,1,0,0,0,0,1,0,1},
		{1,0,0,0,1,1,0,1,1,1},
		{1,0,1,0,1,0,1,0,0,1},
		{1,1,0,0,1,0,0,0,1,1},
		{1,0,0,0,1,0,1,0,0,1},
		{1,0,1,0,1,0,0,1,0,1},
		{1,0,1,0,0,0,1,0,0,2},
		{1,1,1,1,1,1,1,1,1,1}
	}
};



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //CALLBACK ��ũ��
HINSTANCE g_hInst; //�ν���Ʈ �ڵ�
HWND hWndMain;
LPCTSTR lpszClass = TEXT("������_16032048"); //���� ǥ���� ����

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) //�����Լ�
{
	HWND hWnd;				//������ �ڵ� ����
	MSG Message;			//�޼��� ����ü ���� ����
	WNDCLASS WndClass;		//Windows Class ����ü ���� ����
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//������ ��� ����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//���콺 ������ ���
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//Ŀ�� ���
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);			//���α׷� â ũ�� ����
	ShowWindow(hWnd, nCmdShow);

	//�޼��� ���� ����
	while (GetMessage(&Message, NULL, 0, 0)) {
		if ((Message.message == WM_KEYDOWN || Message.message == WM_KEYUP) && Message.hwnd != hWnd)
		{
			PostMessage(hWnd, Message.message, Message.wParam, Message.lParam);
		}
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;			//Ż�� �ڵ� ���α׷� ����
}

bool Check(int x, int y,int boardtype) //�տ� ���� �ִ��� Ȯ���ϴ� �Լ�
{
	if (GameBoard[boardtype][y][x] == 1)//��
	{
		return true;
	}
	return false;
}
bool GameClear(int x, int y, int boardtype) //���� ��ǥ�� �޼��ߴ��� Ȯ���ϴ� �Լ�
{
	if (GameBoard[boardtype][y][x] == 2)//��������
	{
		return true;
	}
	return false;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	static int BoardType;
	static int x_pos; //x��ǥ
	static int y_pos;//y��ǥ

	switch (iMessage) {
	case WM_CREATE: //�ʱⰪ����
	{
		BoardType = 0;
		x_pos = 0;
		y_pos = 1;
		break;
	}

	case WM_COMMAND: //�޴� ����
		switch (LOWORD(wParam)) 
		{
		case ID_LV1: //����
			BoardType = 0;
			x_pos = 0;
			y_pos = 1;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_LV2: //����
			BoardType = 1;
			x_pos = 0;
			y_pos = 1;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_LV3://�����
			BoardType = 2;
			x_pos = 0;
			y_pos = 1;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}


	case WM_PAINT:
	{
		HDC hdc;
		PAINTSTRUCT ps;
		HBRUSH hBrush, oldBrush;//�귯�� ����

		hdc = BeginPaint(hWnd, &ps);
		//������
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		for (int i = 0; i < BOARDSIZE; i++) //������ �׷��ֱ�
		{
			for (int j = 0; j < BOARDSIZE; j++)
			{
				if (GameBoard[BoardType][i][j] == 1)//�� ����
				{
					Rectangle(hdc, j * BOARDCORRECTION - FIGURESIZE+ BOARDCORRECTION, i * BOARDCORRECTION - FIGURESIZE + BOARDCORRECTION, j * BOARDCORRECTION + FIGURESIZE + BOARDCORRECTION, i * BOARDCORRECTION + FIGURESIZE + BOARDCORRECTION);
				}
				if (GameBoard[BoardType][i][j] == 2)//Ŭ���� ��ġ
				{
					hBrush = CreateSolidBrush(RGB(0, 0, 255));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Rectangle(hdc, j * BOARDCORRECTION - FIGURESIZE + BOARDCORRECTION, i * BOARDCORRECTION - FIGURESIZE + BOARDCORRECTION, j * BOARDCORRECTION + FIGURESIZE + BOARDCORRECTION, i * BOARDCORRECTION + FIGURESIZE + BOARDCORRECTION);
					SelectObject(hdc, oldBrush);// ������ �귯���� ���ư�
					DeleteObject(hBrush);
				}
			}
		}
		SelectObject(hdc, oldBrush);// ������ �귯���� ���ư�
		DeleteObject(hBrush);

		hBrush = CreateSolidBrush(RGB(0, 255, 0));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		//�̵��ϴ� �� �׷��ֱ�
		Ellipse(hdc, x_pos * BOARDCORRECTION - FIGURESIZE + BOARDCORRECTION, y_pos * BOARDCORRECTION - FIGURESIZE + BOARDCORRECTION, x_pos * BOARDCORRECTION + FIGURESIZE + BOARDCORRECTION, y_pos * BOARDCORRECTION + FIGURESIZE + BOARDCORRECTION);
		SelectObject(hdc, oldBrush);// ������ �귯���� ���ư�
		DeleteObject(hBrush);
		// ���� ����
		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		TextOut(hdc, 750, 150, TEXT("�� ������ ��ǥ�� �ʷϻ����� ��ǥ��������"), 40);
		TextOut(hdc, 750, 180, TEXT("�̵��ϴ� �̷� �����Դϴ�."), 25);
		TextOut(hdc, 820, 230, TEXT("<< �Ķ��� �簢���� ��ǥ�����Դϴ�."), 34);
		Rectangle(hdc, 12 * BOARDCORRECTION - FIGURESIZE + BOARDCORRECTION, 3 * BOARDCORRECTION - FIGURESIZE + BOARDCORRECTION, 12 * BOARDCORRECTION + FIGURESIZE + BOARDCORRECTION, 3 * BOARDCORRECTION + FIGURESIZE + BOARDCORRECTION);
		SelectObject(hdc, oldBrush);// ������ �귯���� ���ư�
		DeleteObject(hBrush);
		EndPaint(hWnd, &ps);
		return 0;
	}
	case WM_KEYDOWN: //Ű���� ��Ʈ��
	{
		switch (wParam)
		{
		case VK_LEFT:
			if(Check(x_pos-1,y_pos,BoardType)!=true) //���� �ִ��� Ȯ���� �̵�
			x_pos--;
			break;
		case VK_RIGHT:
			if (Check(x_pos+1, y_pos, BoardType) != true)//���� �ִ��� Ȯ���� �̵�
			x_pos++;
			break;
		case VK_UP:
			if (Check(x_pos, y_pos-1, BoardType) != true)//���� �ִ��� Ȯ���� �̵�
			y_pos--;
			break;
		case VK_DOWN:
			if (Check(x_pos, y_pos+1, BoardType) != true)//���� �ִ��� Ȯ���� �̵�
			y_pos++;
			
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		if (GameClear(x_pos, y_pos, BoardType))//�̵��Ŀ� ��ǥ������ �����޴��� üũ
			MessageBox(hWnd, TEXT("��ǥ ������ �����߽��ϴ�."), TEXT("Ŭ����!"), MB_OK);
		break;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
