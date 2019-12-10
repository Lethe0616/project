#include<Windows.h>
#include "DuiLib/UIlib.h"

#pragma comment(lib,"DuiLib_ud.lib")

using namespace DuiLib;


#if 0
//INotifyUI:duilib�Լ��������-->������
class CDuiFramWnd : public CWindowWnd, public INotifyUI
{
public:
	// CWindowWnd��Ĵ��麯�����ڸú����б��뷵���û������崰�ڵ������ƣ�ע�ᴰ��ʱ��Ҫ�õ�
	//���ش����������
	virtual LPCTSTR GetWindowClassName() const
	{
		return _T("DuiFramWnd");
	}
	// uMsg����ȡ������ϢID--->���ֲ��񵽵���ʲô���͵���Ϣ
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)//���������Ҫ����ϵͳ��Ϣ��ʱ����Ҫ��д
	{
		if (WM_CREATE == uMsg)
		{
			m_PaintManager.Init(m_hWnd);

			CDialogBuilder builder;
			// duilib.xml��Ҫ�ŵ�exeĿ¼��    
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

		//���ػ滭��ص���Ϣ
		LRESULT lRes = 0;
		if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
		{
			return lRes;
		}
		//������Ϣ
		//__super::ָ���û����
		return __super::HandleMessage(uMsg, wParam, lParam);
	}
	virtual void Notify(TNotifyUI& msg)  //�����Ҫ����duilib�Լ�ά������Ϣʱ��ֻ��Ҫ����������дNotify
	{
		//��Ӧ��ť�����Ϣ
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
	// ������Դ��Ĭ��·�����˴�����Ϊ��exe��ͬһĿ¼��
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
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

class CDuiFramWnd : public WindowImplBase
{
	//ͨ��xml�ļ���������--���ڴ���
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
	virtual void Notify(TNotifyUI& msg)  //duilib��ά���ÿռ�����������Ϣ
	{
		if (msg.sType == _T("click"))
		{
			CDuiString strName=msg.pSender->GetName();
			MessageBox(m_hWnd, _T("��ť����"), _T("Test"), IDOK);
#if 0
			if (strName == _T("bun_close"))
			{
				Close();
			}
			else if (strName == _T("bun_min"))
			{
				MessageBox(NULL, _T("��С��"), _T("����"), IDOK);
			}
			//MessageBox(m_hWnd, _T("��ť����"), _T("Test"), IDOK);
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
	// ������Դ��Ĭ��·�����˴�����Ϊ��exe��ͬһĿ¼��
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
	CDuiFramWnd framWnd;
	// Cashier���ڴ������Ͻ���ʽ������
	// UI_WNDSTYLE_FRAME: duilib��װ�ĺ꣬�����ڿ��ӣ����б������������С�����رչ��ܵ�
	// WS_EX_WINDOWEDGE: Win32�Ĵ��ڷ�񣬴��б߿�
	framWnd.Create(NULL, _T("Cashier"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	//���ھ���
	framWnd.CenterWindow();
	//��ʾ���ڣ�������Ϣѭ��
	framWnd.ShowModal();
	return 0;
}