#include<Windows.h>
#include "DuiLib/UIlib.h"

#pragma comment(lib,"DuiLib_ud.lib")

using namespace DuiLib;


#if 0
//INotifyUI:duilib自己定义的类-->抽象类
class CDuiFramWnd : public CWindowWnd, public INotifyUI
{
public:
	// CWindowWnd类的纯虚函数，在该函数中必须返回用户所定义窗口的类名称，注册窗口时需要用到
	//返回窗口类的名字
	virtual LPCTSTR GetWindowClassName() const
	{
		return _T("DuiFramWnd");
	}
	// uMsg：获取到的消息ID--->区分捕获到的是什么类型的消息
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)//子类如果需要处理系统消息的时候，需要重写
	{
		if (WM_CREATE == uMsg)
		{
			m_PaintManager.Init(m_hWnd);

			CDialogBuilder builder;
			// duilib.xml需要放到exe目录下    
			CControlUI* pRoot = builder.Create(_T("duilib.xml"), (UINT)0, NULL, &m_PaintManager);
			m_PaintManager.AttachDialog(pRoot);
			m_PaintManager.AddNotifier(this);
			return 0;
		}
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

		//拦截绘画相关的消息
		LRESULT lRes = 0;
		if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
		{
			return lRes;
		}
		//其他消息
		//__super::指调用基类的
		return __super::HandleMessage(uMsg, wParam, lParam);
	}
	virtual void Notify(TNotifyUI& msg)  //如果需要拦截duilib自己维护的消息时，只需要在子类中重写Notify
	{
		//响应按钮点击消息
		if (msg.sType == _T("click"))
		{
			MessageBox(m_hWnd, _T("Hello World"), _T("DuiFramWnd"), IDOK);
		}
	}

private:
	CPaintManagerUI m_PaintManager;
};

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int
	nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	// 设置资源的默认路径（此处设置为和exe在同一目录）
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
	CDuiFramWnd framWnd;
	// Cashier即在窗口右上角显式的名字
	// UI_WNDSTYLE_FRAME: duilib封装的宏，代表窗口可视，具有标题栏，最大化最小化，关闭功能等
	// WS_EX_WINDOWEDGE: Win32的窗口风格，带有边框
	framWnd.Create(NULL, _T("Cashier"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	//显示窗口，激活消息循环
	framWnd.ShowModal();
	return 0;
}

#endif

class CDuiFramWnd : public WindowImplBase
{
	//通过xml文件描述窗口--窗口创建
public:
	virtual LPCTSTR    GetWindowClassName() const
	{
		return _T("DuiWin");
	}
	virtual CDuiString GetSkinFile()
	{
		return _T("duilib.xml");
	}
	virtual CDuiString GetSkinFolder()
	{
		return _T("");
	}
	virtual void Notify(TNotifyUI& msg)  //duilib所维护得空间所产生的消息
	{
		if (msg.sType == _T("click"))
		{
			CDuiString strName=msg.pSender->GetName();
			MessageBox(m_hWnd, _T("按钮单击"), _T("Test"), IDOK);
#if 0
			if (strName == _T("bun_close"))
			{
				Close();
			}
			else if (strName == _T("bun_min"))
			{
				MessageBox(NULL, _T("最小化"), _T("测试"), IDOK);
			}
			//MessageBox(m_hWnd, _T("按钮单击"), _T("Test"), IDOK);
		}
		else if (msg.sType == _T("itemselect"))
		{
			CComboBoxUI* pComboSelect=m_PaintManager.FindControl("combo_select");
			pComboSelect
		}
#endif
	}
};

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance); 
	// 设置资源的默认路径（此处设置为和exe在同一目录）
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
	CDuiFramWnd framWnd;
	// Cashier即在窗口右上角显式的名字
	// UI_WNDSTYLE_FRAME: duilib封装的宏，代表窗口可视，具有标题栏，最大化最小化，关闭功能等
	// WS_EX_WINDOWEDGE: Win32的窗口风格，带有边框
	framWnd.Create(NULL, _T("Cashier"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	//窗口居中
	framWnd.CenterWindow();
	//显示窗口，激活消息循环
	framWnd.ShowModal();
	return 0;
}