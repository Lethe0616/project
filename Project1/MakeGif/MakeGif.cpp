#include "DuiLib/UIlib.h"
using namespace DuiLib;

#pragma comment(lib,"DuiLib_ud.lib")

#include <fstream>
class DuiWinWnd :public WindowImplBase
{
protected:
	virtual LPCTSTR GetWindowClassName(void) 
	{ 
		return _T("GIFMakeWnd"); 
	}
	virtual CDuiString GetSkinFile() 
	{ 
		return _T("gifMake.xml"); 
	}
	virtual CDuiString GetSkinFolder() 
	{ 
		return _T(" "); 
	}

	virtual void Notify(TNotifyUI& msg)
	{
		CDuiString strName = msg.pSender->GetName();
		if (msg.sType == _T("click"))
		{
			if (strName == _T("btn_close"))
			{
				Close();
			}

			else if (strName == _T("btn_min"))
			{
				MessageBox(NULL, _T("��С��"), _T("����"), IDOK);
			}

			else if (strName == _T("btn_load"))
				LoadFile();

			else if (strName == _T("btn_cut"))
				CutView();

			else if (strName == _T("ButtonUI5"))
			{
				GetSRTFile();
				LoadSRT();
			}

			else if (strName == _T("ButtonUI7"))
			{
				CListUI* pEdit = (CEditUI*)m_PaintManager.FindControl(_T("edit_word"));
				CDuiString strWord = pEdit->GetText();
				
				//д��list��
				//��ȡ�ռ�
				CListUI* pList = (CListUI*)m_PaintManager.FindControl(_T("list_srt"));
				
				//��ȡ��ǰѡ����
				CListTextElementUI* pListItemp = (CListTextElementUI*)pList->GetItemAt(pList->GetCurSel);
				pListItemp->SetText(1, strWord);
			}

			else if (strName == _T("ButtonUI7"))
			{
				WriteSRT();
			}

			else if (strName == _T("ButtonUI6"))
			{
				CComboBoxUI* pCombo = (CComboBoxUI*)m_PaintManager.FindControl(_T("combo_select"));
				if (0 == pCombo->GetCurSel())
				{
					GenerateGifWithPic();
				}
				else
				{
					GenerateGifWithView();
				}
			}
		}
		else if (msg.sType == _T("windowinit"))
		{
			SetControlEnable(false);
		}

		else if (msg.sType == _T("selectchanged"))
		{
			MessageBox(NULL, _T("Combo"), _T("Test"), IDOK);
		}
		else if (msg.sType == _T("itemselect"))
		{
			if (strName == _T("list_srt"))
			{
				//��ȡ�ռ�
				CListUI* pList = (CListUI*)m_PaintManager.FindControl(_T("list_srt"));
				//��ȡ��ǰѡ����
				CListTextElementUI* pListItemp = (CListTextElementUI *)pList->GetItemAt(pList->GetCurSel);
				//�ı���ӵ�edit��
				CListUI* pEdit = (CEditUI*)m_PaintManager.FindControl(_T("edit_word"));
				pEdit->SetText(pListItemp->GetText(1));
			}

			if (strName == _T("combo_select"))
			{
				CComboBoxUI* pComboUI = m_PaintManager.FindControl(_T("combo_select"));
				if (0 == pComboUI->GetCurSel())
				{
					SetControlEnable(false);
					/*
					((CEditUI*)m_PaintManager.FindControl(_T("edit_start")))->SetEnabled(false);
					((CButtonUI*)m_PaintManager.FindControl(_T("ButtonUI5")))->SetEnabled(false);
					((CButtonUI*)m_PaintManager.FindControl(_T("ButtonUI9")))->SetEnabled(false);
					((CButtonUI*)m_PaintManager.FindControl(_T("ButtonUI6")))->SetEnabled(false);
					((CButtonUI*)m_PaintManager.FindControl(_T("ButtonUI3")))->SetEnabled(false);
					((CButtonUI*)m_PaintManager.FindControl(_T("ButtonUI8")))->SetEnabled(false);
					((CButtonUI*)m_PaintManager.FindControl(_T("ButtonUI4")))->SetEnabled(false);
				*/
				}
				else
				{
					SetControlEnable(true);
					/*
					((CEditUI*)m_PaintManager.FindControl(_T("edit_start")))->SetEnabled(true);
					((CButtonUI*)m_PaintManager.FindControl(_T("ButtonUI5")))->SetEnabled(true);
					((CButtonUI*)m_PaintManager.FindControl(_T("ButtonUI9")))->SetEnabled(true);
					((CButtonUI*)m_PaintManager.FindControl(_T("ButtonUI6")))->SetEnabled(true);
					((CButtonUI*)m_PaintManager.FindControl(_T("ButtonUI3")))->SetEnabled(true);
					((CButtonUI*)m_PaintManager.FindControl(_T("ButtonUI8")))->SetEnabled(true);
					((CButtonUI*)m_PaintManager.FindControl(_T("ButtonUI4")))->SetEnabled(true);
				*/
				}

			}

			void SetControlEnable(bool IsValid)
			{
				((CEditUI*)m_PaintManager.FindControl(_T("edit_start")))->SetEnabled(IsValid);
				((CButtonUI*)m_PaintManager.FindControl(_T("ButtonUI5")))->SetEnabled(IsValid);
				((CButtonUI*)m_PaintManager.FindControl(_T("ButtonUI9")))->SetEnabled(IsValid);
				((CButtonUI*)m_PaintManager.FindControl(_T("ButtonUI6")))->SetEnabled(IsValid);
				((CButtonUI*)m_PaintManager.FindControl(_T("ButtonUI3")))->SetEnabled(IsValid);
				((CButtonUI*)m_PaintManager.FindControl(_T("ButtonUI8")))->SetEnabled(IsValid);
				((CButtonUI*)m_PaintManager.FindControl(_T("ButtonUI4")))->SetEnabled(IsValid);
			}

			CComboBoxUI* pComboSelect = (CComboUI*)m_PaintManager.FindControl(_T("combo_select"));
			int iSelect = pComboSelect->GetCurSel();
			
			if (0 == iSelect)
			{
				//MessageBox(NULL, _T("ѡ��ͼƬ"), _T("����"), IDOK);
			}
			else
			{
				//MessageBox(NULL, _T("ѡ����Ƶ"), _T("����"), IDOK);
			}
			
		}
	}
	void SendMessage(CDuiString strCMD)
	{
		SHELLEXECUTEINFO strSEInfo;
		memset(&strSEInfo, 0, sizeof(SHELLEXECUTEINFO));

		strSEInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		strSEInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
		strSEInfo.lpFile = _T("C:\\Windows\\System32\\cmd.exe");
		strSEInfo.lpParameters = strCMD;
		strSEInfo.nShow = SW_HIDE;

		ShellExecuteEx(&strSEInfo);

		WaitForSingleObject(strSEInfo.hProcess, INFINITE);

		MessageBox(NULL, _T("����������", _T(MakeGif), IDOK));
	}

		void GenerateGifWithPic()
		{
			CDuiString strPath = CPaintManagerUI:GetInstancePath();

			strPath += _T("ffmpeg\\");

			CDuiString strCMD;
			strCMD += _T("/c ");
			strCMD += strPath;
			strCMD += _T("/c ffmpeg -r 3 -i ");
			strCMD += strPath;
			strCMD += _T(".\\Pictrue\\%d.jpg ");
			strCMD += strPath;
			strCMD += _T("output.gif -y");

			SendMessage(strCMD);
		}

		void CutView()
		{
			CDuiString strCmd;
			CDuiString strPath = CPaintManagerUI:GetInstancePath();
			CDuiString strViewPath = ((CEditUI*)m_PaintManager.FindControl(_T("edit_path")));
			strPath += _T("ffmpeg\\");

			CDuiString strCMD;
			strCMD += _T("/c ");
			strCMD += strPath;
			strCMD += _T("ffmpeg -i ");
			if (! strViewPath.IsEmpty())
			{
				strCMD += strViewPath;
			}
			else
			{
				strCMD += strPath;
				strCMD += _T("input.mkv");
			}
			
			strCMD += _T("-vcodec copy -acodec copy -ss");
			strCMD += _T(" ");

			CDuiString strStartTime =((CEditUI)m_PaintManager.FindControl(_T("EditUI2")))->GetText();
			if (IsValieTime(strStartTime))
			{
				MessageBox(NULL, _T("��ʼʱ������"),_T("MakeGif"),IDOK);
				return;
			}

			CDuiString strEndTime = ((CEditUI)m_PaintManager.FindControl(_T("EditUI3")))->GetText();
			if (IsValieTime(strEndTime))
			{
				MessageBox(NULL, _T("��ֹʱ������"), _T("MakeGif"), IDOK);
				return;
			}

			strCMD += strStartTime;
			strCMD += _T("-to");
			strCMD += strEndTime;
			strCMD += _T(" ");

			strCMD += strPath;
			strCMD += _T("11.mkv -y");

			SendMessage(strCMD);
		}

		void LoadFile()
		{
			OPENFILENAME ofn;
			memset(&ofn, 0, sizeof(OPENFILENAME));

			TCHAR strPeth[MAX_PATH] = {0};
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.lpstrFile = strPeth;
			ofn.nMaxFile = sizeof(strPeth);
			ofn.lpstrFilter = _T("All(*.*)\0 * .*\0mkv(*.mkv)\0 *.mkv\0;");
		
			if (GetOpenFileName(&ofn))
			{
				((CEditUI*)m_PaintManager, FindControl(_T("edit_path")))->SetText(strPeth);
				//MessageBox(NULL, _T("test"), _T("gif"), IDOK);
			}
		}

		void GetSRTFile()
		{
			CDuiString strCmd;
			CDuiString strPath = CPaintManagerUI:GetInstancePath();

			strPath += _T("ffmpeg\\");
			
			CDuiString strCMD;
			strCMD += _T("/c ");
			strCMD += strPath;
			strCMD += _T("ffmpeg -i ");
			strCMD += strPath;
			strCMD += _T("11.mkv ");
			strCMD += strPath;
			strCMD += _T("input.srt -y");

			SendMessage(strCMD);
		}

		void LoadSRT()
		{
			CDuiString strPath = CPaintManagerUI:GetInstancePath();
			strPath += _T("ffmpeg\\input.srt");
			std::ifstream fIn(strPath.GetData());

			char strSRTCon[521] = { 0 };
			CListUI* pList = (CListUI*)m_PaintManager.FindControl(_T("list_srt"));
			pList->RemoveAll();

			while (!fIn.eof())
			{
				//��Ļ���
				fIn.getline(strSRTCon,521);

				CListTextElementUI* pListItem = new CListTextElementUI;
				pList->Add(pListItem);

				//ʱ����
				fIn.getline(strSRTCon, 521);
				pListItem->SetText(0, UTF8ToUnicode(strSRTCon));

				//��Ļ
				fIn.getline(strSRTCon, 521);
				pListItem->SetText(1, UTF8ToUnicode(strSRTCon));

				//����
				fIn.getline(strSRTCon, 521);
			}
			fIn.close();
		}

		void WriteSRT()
		{
			//��ȡ·��
			CDuiString strPath = CPaintManagerUI:GetInstancePath();
			strPath += _T("ffmpeg\\input.srt");
			std::ofstream fOut(strPath.GetData());

			//��ȡ�ı�����
			CListUI* pList = (CListUI*)m_PaintManager.FindControl(_T(list_srt));
			int szCount = pList->GetCount();

			for (int i = 0; i < szCount; ++i)
			{
				CListTextElementUI* pListItem =(CListTextElementUI*) pList->GetItemAt(i);

				//���
				CDuiString strNo;
				strNo.Format(_T("%d"), i + 1);

				//ʱ����
				CDuiString strTime = pListItem->GetText(0);

				//�ı�����
				CDuiString strWord = pListItem->GetText(1);

				//��ȡ����д��src
				string strNewLine = Unicode2ANSI(_T("\n"));
				
				//�к�
				string itemNo = Unicode2ANSI(strNo);
				fOut.write(itemNo.c_str(),itemNo.size());
				fOut.write(strNewLine.c_str(), strNewLine.size());
				
				//ʱ����
				string itemTime = Unicode2ANSI(strTime);
				fOut.write(itemTime.c_str(), itemTime.size());
				fOut.write(strNewLine.c_str(), strNewLine.size());
				
				//�ı�
				string itemWord = Unicode2ANSI(strWord);
				fOut.write(itemWord.c_str(), itemWord.size());
				fOut.write(strNewLine.c_str(), strNewLine.size());

				//��Ļ֮�任��
				fOut.write(strNewLine.c_str(), strNewLine.size());
			}
			fOut.close();
		}

		void GenerateView()
		{
			CDuiString strCmd;
			CDuiString strPath = CPaintManagerUI:GetInstancePath();

			strPath += _T("ffmpeg\\");

			CDuiString strCMD;
			strCMD += _T("/c ");
			strCMD += strPath;
			strCMD += _T("ffmpeg -i ");
			strCMD += strPath;
			strCMD += _T("11.mkv -vcodec copy -an -sn ");
			strCMD += strPath;
			strCMD += _T("22.mkv -y");

			SendMessage(strCMD);
		}

		void BornSRT2View()
		{
			CDuiString strCmd;
			CDuiString strPath = CPaintManagerUI:GetInstancePath();

			strPath += _T("ffmpeg\\");

			CDuiString strCMD;
			strCMD += _T("/c ");
			strCMD += strPath;
			strCMD += _T("ffmpeg -i ");
			strCMD += strPath;
			strCMD += _T("22.mkv -vf subtitles=11.srt ");
			strCMD += strPath;
			strCMD += _T("33.mkv -y");

			SendMessage(strCMD);
		}

		void GenerateGifWithView()
		{
			CDuiString strCmd;
			CDuiString strPath = CPaintManagerUI:GetInstancePath();

			strPath += _T("ffmpeg\\");

			CDuiString strCMD;
			strCMD += _T("/c ");
			strCMD += strPath;
			strCMD += _T("ffmpeg -i ");
			strCMD += strPath;
			strCMD += _T("33.mkv -vf scale=iw/2:ih/2 -f gif ");
			strCMD += strPath;
			strCMD += _T("output.gif -y");

			SendMessage(strCMD);
		}

		CDuiString UTF8ToUnicode(const char* str)
		{
			int szLen = ::MultiByteToWideChar(CP_UTF8,0,str,strlen(str),NULL,0);
		
			wchar_t* pContent = new wchar_t[szLen];

			::MultiByteToWideChar(CP_UTF8, 0, str, strlen(str), pContent, szLen);
			pContent[szLen] = '\0';

			CDuiString s(pContent);
			delete[] pContent;
			return s;
		}

		bool IsValieTime(CDuiString strTime)
		{
			if (strTime.GetLength() != 8)
			{
				return false;
			}

			for (int i = 0; i < strTime.GetLength(); ++i)
			{
				if (strTime[i] == ':')
					continue;

				if (!(strTime[i] >= '0' && strTime[i] <= '9'))
					return false;
			}

			return true;
		}

		string Unicode2ANSI(CDuiString str)
		{
			int szLen = ::WideCharToMultiByte(CP_ACP, 0, str.GetData() ,- 1, NULL,0,NULL, FALSE);
			char* pBuff = new char[szLen + 1];
			::WideCharToMultiByte(CP_ACP, 0, str.GetData(),str.GetLength(),pBuff,szLen, NULL, FALSE);
		    pBuff[szLen] = '\0';
			string s(pBuff);
			delete[] pBuff;
			return s;
		}
};

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int
	nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
	DuiWinWnd wnd;

	wnd.Create(NULL, _T("MakeGif"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	wnd.CenterWindow();
	wnd.ShowModal();
	return 0;
}