#include "DuiLib/UIlib.h"
using namespace DuiLib;

#pragma comment (lib,"DuiLib_ud.lib")

#if 0
class CDuiFramWnd : public CWindowWnd
{
public:
	// CWindowWnd��Ĵ��麯�����ڸú����б��뷵���û������崰�ڵ������ƣ�ע�ᴰ��ʱ��Ҫ�õ�
	virtual LPCTSTR GetWindowClassName() const
	{
		return _T("DuiFramWnd");
	}
};
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int
	nCmdShow)
{
	CDuiFramWnd framWnd;
	// Cashier���ڴ������Ͻ���ʽ������
	// UI_WNDSTYLE_FRAME: duilib��װ�ĺ꣬�����ڿ��ӣ����б������������С�����رչ��ܵ�
	// WS_EX_WINDOWEDGE: Win32�Ĵ��ڷ�񣬴��б߿�
	framWnd.Create(NULL, _T("Cashier"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	//��ʾ���ڣ�������Ϣѭ��
	framWnd.ShowModal();
	return 0;
}
#endif

class CDuiFramWnd :public WindowImplBase
{
protected:
	virtual CDuiString GetSkinFolder()
	{
		return _T("");
	}
	virtual CDuiString GetSkinFile()
	{
		return _T("duilib.xml");
	}
	virtual LPCTSTR GetWindowClassName(void)
	{
		return _T("DuiWnd");
	}

	virtual void Notify(TNotifyUI& msg)
	{
		if (msg.sType == _T("click"))
		{
			MessageBox(m_hWnd, _T("��ť���"), _T("Test"), IDOK);
		}
	}
};

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CDuiFramWnd framWnd;
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

	// Cashier���ڴ������Ͻ���ʽ������
	// UI_WNDSTYLE_FRAME: duilib��װ�ĺ꣬�����ڿ��ӣ����б������������С�����رչ��ܵ�
	// WS_EX_WINDOWEDGE: Win32�Ĵ��ڷ�񣬴��б߿�
	framWnd.Create(NULL, _T("DuilibTest"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	framWnd.CenterWindow();

	//��ʾ���ڣ�������Ϣѭ��
	framWnd.ShowModal();
	return 0;
}