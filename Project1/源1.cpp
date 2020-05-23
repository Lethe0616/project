#include<Windows.h>
#include "DuiLib/UIlib.h"

#pragma comment(lib,"DuiLib_ud.lib")

using namespace DuiLib;


class CDuiFramWnd : public CWindowWnd, public INotifyUI
{
public:
	// CWindow Wnd类的纯虚函数，在该函数中必须返回用户所定义窗口的类名称，注册窗口时需要用到
	virtual LPCTSTR GetWindowClassName() const
	{
		return _T("DuiFramWnd");
	}

public:
	virtual LRESULT MessageHandle(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lRes = 0;

		if (uMsg == WM_CREATE)
		{
			m_PaintManager.Init(m_hWnd);

			//创建一个按钮
			CControlUI* pBTN = new CButtonUI;
			pBTN->SetText(_T("hello"));
			pBTN->SetBkColor(0xFF00FF00);

			m_PaintManager.AttachDialog(pBTN);
			m_PaintManager.AddNotifier(this);
			return 0;
		}

		//拦截回话相关信息
		LRESULT lRES = 0;
		if (m_PaintManager.MessageHander(uMsg, wParam, lParam, lRes);
		{
			return lRES;
		}
		return _super::HandleMessage(uMsg, wParam, lParam);

			//其他消息	
			m_PaintManager.Init(m_hWnd);

			CDialogBuilder builder;
			// duilib.xml需要放到exe目录下
			CControlUI* pRoot = builder.Create(_T("duilib.xml"), (UINT)0, NULL, &m_PaintManager);
		m_PaintManager.AttachDialog(pBTN);
		m_PaintManager.AddNotifier(this);
		return lRes;


		// 以下3个消息WM_NCACTIVATE、WM_NCCALCSIZE、WM_NCPAINT用于屏蔽系统标题栏
		else if (uMsg == WM_NCACTIVATE)
		{
			if (!::IsIconic(m_hWnd))
			{
				return (wParam == 0) ? TRUE : FALSE;
			}
		}
		else if (uMsg == WM_NCCALCSIZE)
		{
			return 0;
		}
		else if (uMsg == WM_NCPAINT)
		{
			return 0;
		}

		if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
		{
			return lRes;
		}

		return __super::HandleMessage(uMsg, wParam, lParam);
	}

	virtual void Notify(TNotifyUI& msg)
	{
		if (msg.sType == _T("click"))
		{
			MessageBox(m_hWnd, _T("按钮点击"), _T("Test"), IDOK);
		}
	}

private:
	CPaintManagerUI m_PaintManager;
};

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CDuiFramWnd framWnd;
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

	// Cashier即在窗口右上角显式的名字
	// UI_WNDSTYLE_FRAME: duilib封装的宏，代表窗口可视，具有标题栏，最大化最小化，关闭功能等
	// WS_EX_WINDOWEDGE: Win32的窗口风格，带有边框
	framWnd.Create(NULL, _T("DuilibTest"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);

	//显示窗口，激活消息循环
	framWnd.ShowModal();
	return 0;
}