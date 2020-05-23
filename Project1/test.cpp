#include <Windows.h>
#include <tchar.h>
//��Ϣ�ص�����
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		if (IDOK == MessageBox(hWnd, _T("��ȷ���˳���"), _T("�˳�"), MB_OKCANCEL))
		{
			DestroyWindow(hWnd);
			return 0;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int
	nCmdShow)
{

	//Step1:ע��һ��������
	HWND hwnd; //���ڵľ��
	WNDCLASSEX wc; //������ṹ
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = _T("Win32");
	wc.lpfnWndProc = WinProc; //��Ϣ�ص�����
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.hIconSm = NULL;
	RegisterClassEx(&wc); //ע�ᴰ��

	//Step2:����һ������
	hwnd = CreateWindow(
		_T("Win32"), // ���������ƣ�������ע��ʱ������һ��
		_T("�ҵĵ�һ��Win32����"), // ���ڵı���
		WS_OVERLAPPEDWINDOW, // ����style
		500, // ����λ��x����
		300, // ����λ��y����
		800, // ���ڿ��
		600, // ���ڸ߶�
		NULL, // �����ھ����û��ʱ����ΪNULL
		NULL, // �˵����, û��ʱ����ΪNULL
		hInstance, // ��ǰӦ�ó����ʵ�����
		NULL // û�и�������ʱ������ΪNULL
	);
	if (!hwnd)
	{
		return FALSE;
	}
	ShowWindow(hwnd, SW_SHOW); //��ʾ����
	UpdateWindow(hwnd); //ˢ��

	//Step3:��Ϣѭ��
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}