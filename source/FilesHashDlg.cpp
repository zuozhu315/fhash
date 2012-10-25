// MD5SUM03Dlg.cpp : ʵ���ļ�
//
#include "stdafx.h"

#include "FilesHash.h"
#include "FilesHashDlg.h"
#include "FindDlg.h"
#include "AboutDlg.h"
#include "Global.h"
#include "Functions.h"
#include "HashEngine.h"
#include "UIStrings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFilesHashDlg �Ի���
CFilesHashDlg::CFilesHashDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFilesHashDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CFilesHashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS, m_prog);
	DDX_Control(pDX, IDC_PROG_WHOLE, m_progWhole);
	DDX_Control(pDX, IDE_TXTMAIN, m_editMain);
	DDX_Control(pDX, IDC_OPEN, m_btnOpen);
	DDX_Control(pDX, IDC_STOP, m_btnStop);
	DDX_Control(pDX, IDC_EXIT, m_btnExit);
	DDX_Control(pDX, IDC_CLEAN, m_btnClr);
	DDX_Control(pDX, IDC_COPY, m_btnCopy);
	DDX_Control(pDX, IDC_CHECKUP, m_chkUppercase);
	DDX_Control(pDX, IDC_FIND, m_btnFind);
	DDX_Control(pDX, IDC_CONTEXT, m_btnContext);
}

BEGIN_MESSAGE_MAP(CFilesHashDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_OPEN, OnBnClickedOpen)
	ON_BN_CLICKED(IDC_STOP, OnBnClickedStop)
	ON_BN_CLICKED(IDC_EXIT, OnBnClickedExit)
	ON_BN_CLICKED(IDC_ABOUT, OnBnClickedAbout)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_CLEAN, OnBnClickedClean)
	ON_BN_CLICKED(IDC_COPY, OnBnClickedCopy)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_THREAD_INFO, OnThreadMsg)
	ON_BN_CLICKED(IDC_FIND, &CFilesHashDlg::OnBnClickedFind)
	ON_BN_CLICKED(IDC_CONTEXT, &CFilesHashDlg::OnBnClickedContext)
END_MESSAGE_MAP()


// CFilesHashDlg ��Ϣ��������

BOOL CFilesHashDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO���ڴ����Ӷ���ĳ�ʼ������
	m_bruEditBkg.CreateSolidBrush(RGB(255, 255, 255));

	PrepareAdvTaskbar();

	m_bFind = FALSE;
	m_btnClr.SetWindowText(_T(MAINDLG_CLEAR));

	m_bHandleNull = TRUE;
	m_waitingExit = FALSE;

	m_calculateTime = 0.0;
	m_timer = -1;

	m_prog.SetStep(1);

	CWnd* pWnd;
	pWnd = GetDlgItem(IDC_STATIC_SPEED);
	pWnd->SetWindowText("");
	pWnd = GetDlgItem(IDC_STATIC_TIME);
	pWnd->SetWindowText("");
	pWnd = GetDlgItem(IDC_STATIC_FILE);
	pWnd->SetWindowText(MAINDLG_FILE_PROGRESS);
	pWnd = GetDlgItem(IDC_STATIC_WHOLE);
	pWnd->SetWindowText(MAINDLG_TOTAL_PROGRESS);
	pWnd = GetDlgItem(IDC_STATIC_UPPER);
	pWnd->SetWindowText(MAINDLG_UPPER_HASH);
	pWnd = GetDlgItem(IDC_STATIC_UPPER);
	pWnd->SetWindowText(MAINDLG_UPPER_HASH);
	pWnd = GetDlgItem(IDC_STATIC_TIMETITLE);
	pWnd->SetWindowText(MAINDLG_TIME_TITLE);

	m_btnOpen.SetWindowText(MAINDLG_OPEN);
	m_btnStop.SetWindowText(MAINDLG_STOP);
	m_btnCopy.SetWindowText(MAINDLG_COPY);
	m_btnFind.SetWindowText(MAINDLG_VERIFY);
	m_btnExit.SetWindowText(MAINDLG_EXIT);
	pWnd = GetDlgItem(IDC_ABOUT);
	pWnd->SetWindowText(MAINDLG_ABOUT);
	

	m_thrdData.hWnd = m_hWnd;
	m_thrdData.uppercase = FALSE;

	m_thrdData.nFiles = 0;

	m_thrdData.strAll = "";
	m_thrdData.resultList.clear();
	
	pTl = NULL;

	m_editMain.SetLimitText(UINT_MAX);
	m_editMain.SetWindowText(MAINDLG_INITINFO);

	if(IsContextMenuAdded())
	{
		// �Ѿ������Ҽ��˵�
		m_btnContext.SetWindowText(MAINDLG_REMOVE_CONTEXT_MENU);
	}
	else
	{
		m_btnContext.SetWindowText(MAINDLG_ADD_CONTEXT_MENU);
	}
	pWnd = (CStatic*)GetDlgItem(IDC_STATIC_ADDRESULT);
	pWnd->SetWindowText(MAINDLG_CONTEXT_INIT);

	// �������л�ȡ�ļ�·��
	CStrVector Paras = ParseCmdLine();
	ClearFilePaths();
	for(CStrVector::iterator ite = Paras.begin(); ite != Paras.end(); ++ite)
	{
		m_thrdData.fullPaths.push_back(*ite);
		++m_thrdData.nFiles;
	}
	// �������л�ȡ�ļ�·������
	
	m_thrdData.threadWorking = FALSE;
	m_prog.SetRange(0, 99);
	m_progWhole.SetRange(0, 99);
	m_chkUppercase.SetCheck(0);

	if(m_thrdData.nFiles > 0)
		SetTimer(4, 50, NULL); // ʹ DoMD5() �� OnInitDialog() ֮��ִ��

	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

// �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFilesHashDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CFilesHashDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFilesHashDlg::OnDropFiles(HDROP hDropInfo)
{
	if(!m_thrdData.threadWorking)
	{
		unsigned int i;
		char DragFilename[MAX_PATH];
		DragAcceptFiles(FALSE);

		m_thrdData.nFiles = DragQueryFile(hDropInfo, -1, NULL, 0);
		ClearFilePaths();

		for(i=0; i < m_thrdData.nFiles; i++)
		{
			DragQueryFile(hDropInfo, i, DragFilename, sizeof(DragFilename));
			CString tmp;
			tmp.Format("%s", DragFilename);
			m_thrdData.fullPaths.push_back(tmp);
		}

		DragFinish(hDropInfo);
		DragAcceptFiles(TRUE);

		DoMD5();
	}
}

CStrVector CFilesHashDlg::ParseCmdLine()
{
	// �������л�ȡ�ļ�·��
	CStrVector Parameters;
	size_t cmdLen = strlen(theApp.m_lpCmdLine);
	if(cmdLen > 0)
	{
		for(size_t i = 0; i < cmdLen; ++i)
		{
			CString Parameter("");
			if(theApp.m_lpCmdLine[i] == '"')
			{
				++i;
				for(; theApp.m_lpCmdLine[i] != '"'; ++i)
					Parameter.AppendChar(theApp.m_lpCmdLine[i]);
				Parameters.push_back(Parameter);
				++i;
			}
			else
			{
				for(; theApp.m_lpCmdLine[i] != ' '; ++i)
					Parameter.AppendChar(theApp.m_lpCmdLine[i]);
				Parameters.push_back(Parameter);
			}
		}
	}
	// �������л�ȡ�ļ�·������
	return Parameters;
}

void CFilesHashDlg::PrepareAdvTaskbar()
{
	m_bAdvTaskbar = FALSE;
#ifndef _DEBUG
	VERIFY(CoCreateInstance(
			CLSID_TaskbarList, NULL, CLSCTX_ALL,
			IID_ITaskbarList3, (void**)&pTl));
	if(pTl)
		m_bAdvTaskbar = TRUE;
	else
		m_bAdvTaskbar = FALSE;
#endif
}

void CFilesHashDlg::OnClose()
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	if(m_thrdData.threadWorking)
	{
		m_waitingExit = TRUE;
		StopWorkingThread();

		return;
	}

	CDialog::OnClose();
}

void CFilesHashDlg::OnBnClickedOpen()
{
	if(!m_thrdData.threadWorking)
	{
		CString filter;
		char* nameBuffer;
		POSITION pos;
		nameBuffer = new char[MAX_FILES_NUM * MAX_PATH + 1];
		nameBuffer[0] = 0;
		filter = FILE_STRING;
		filter.Append("(*.*)|*.*|");
		CFileDialog dlgOpen(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT, filter, NULL, 0);
		dlgOpen.GetOFN().lpstrFile = nameBuffer;
		dlgOpen.GetOFN().nMaxFile = MAX_FILES_NUM;
		if(IDOK == dlgOpen.DoModal())
		{
			pos = dlgOpen.GetStartPosition();
			ClearFilePaths();
			for(m_thrdData.nFiles = 0; pos != NULL; m_thrdData.nFiles++)
				m_thrdData.fullPaths.push_back(dlgOpen.GetNextPathName(pos));

			DoMD5();
		}
		delete[] nameBuffer;
	}
}

void CFilesHashDlg::OnBnClickedStop()
{
	if(m_thrdData.threadWorking)
	{
		//ֹͣ�����߳�
		StopWorkingThread();
	}
}

void CFilesHashDlg::OnBnClickedExit()
{
	PostMessage(WM_CLOSE);//OnCancel();
}

void CFilesHashDlg::OnBnClickedAbout()
{
	CAboutDlg About;
	About.DoModal();
}

void CFilesHashDlg::OnBnClickedClean()
{
	if(!m_thrdData.threadWorking)
	{
		CString strBtnText;
		m_btnClr.GetWindowText(strBtnText);
		if(strBtnText.Compare(_T(MAINDLG_CLEAR)) == 0)
		{
			m_thrdData.strAll = "";
			m_thrdData.resultList.clear();

			m_editMain.SetWindowText(m_thrdData.strAll);
			CStatic* pWnd =(CStatic *)GetDlgItem(IDC_STATIC_TIME);
			pWnd->SetWindowText("");
			pWnd = (CStatic*)GetDlgItem(IDC_STATIC_SPEED);
			pWnd->SetWindowText("");

			m_prog.SetPos(0);
			//m_progWhole.SetPos(0);
			SetWholeProgPos(0);
		}
		else if(strBtnText.Compare(_T(MAINDLG_CLEAR_VERIFY)) == 0)
		{
			m_bFind = FALSE; // �˳�����ģʽ
			m_btnClr.SetWindowText(_T(MAINDLG_CLEAR));
			RefreshMainText();
		}
	}
}

void CFilesHashDlg::OnBnClickedCopy()
{
	if(!m_thrdData.threadWorking)
	{
		m_editMain.SetSel(0, -1);
		m_editMain.Copy();
		m_editMain.SetSel(-1,0);
		m_editMain.LineScroll(m_editMain.GetLineCount()); // ���ı����������β
	}
}

void CFilesHashDlg::OnBnClickedFind()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	CFindDlg Find;
	Find.SetFindHash(_T(""));
	if(IDOK == Find.DoModal())
	{
		m_strFindHash = Find.GetFindHash().Trim();
		if(m_strFindHash.Compare(_T("")) != 0)
		{
			m_bFind = TRUE; // ��������ģʽ
			m_btnClr.SetWindowText(_T(MAINDLG_CLEAR_VERIFY));
			//m_editMain.SetWindowText(_T(""));
			m_editMain.SetWindowText(ResultFind(m_strFindFile, m_strFindHash));
			//m_editMain.LineScroll(m_editMain.GetLineCount()); // ���ı����������β
		}
	}
}

void CFilesHashDlg::OnBnClickedContext()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	CStatic* pWnd = (CStatic *)GetDlgItem(IDC_STATIC_ADDRESULT);
	CString buttonText = "";

	m_btnContext.GetWindowText(buttonText);

	if(buttonText.Compare(MAINDLG_ADD_CONTEXT_MENU) == 0)
	{

		if(AddContextMenu())
		{
			pWnd->SetWindowText(MAINDLG_ADD_SUCCEEDED);
			m_btnContext.SetWindowText(MAINDLG_REMOVE_CONTEXT_MENU);
		}
		else
		{
			pWnd->SetWindowText(MAINDLG_ADD_FAILED);
		}
	}
	else if(buttonText.Compare(MAINDLG_REMOVE_CONTEXT_MENU) == 0)
	{
		if(RemoveContextMenu())
		{
			pWnd->SetWindowText(MAINDLG_REMOVE_SUCCEEDED);
			m_btnContext.SetWindowText(MAINDLG_ADD_CONTEXT_MENU);
		}
		else
		{
			pWnd->SetWindowText(MAINDLG_REMOVE_FAILED);
		}
	}
}

void CFilesHashDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 1)
	{
		// ���㻨��ʱ��
		m_calculateTime += 0.1f;
		CStatic* pWnd = (CStatic*)GetDlgItem(IDC_STATIC_TIME);
		CString cstrTime;
		int i_calculateTime = (int)m_calculateTime;
		CString cstrFormat("%d ");
		cstrFormat.Append(SECOND_STRING);
		cstrTime.Format(cstrFormat, i_calculateTime);
		pWnd->SetWindowText(cstrTime);
	}
	else if(nIDEvent == 4)
	{
		// ͨ��������������
		DoMD5();
		KillTimer(4);
	}

	CDialog::OnTimer(nIDEvent);
}

void CFilesHashDlg::SetWholeProgPos(UINT pos)
{
	m_progWhole.SetPos(pos);
	if(m_bAdvTaskbar)
		pTl->SetProgressValue(this->m_hWnd, pos, 99);
}

void CFilesHashDlg::DoMD5()
{
	DWORD thredID;

	if(m_bHandleNull==FALSE)
	{
		CloseHandle(m_hWorkThread);
		m_bHandleNull = TRUE;
	}
	
	m_bFind = FALSE;
	m_btnClr.SetWindowText(_T(MAINDLG_CLEAR));

	PrepareAdvTaskbar();

	m_prog.SetPos(0);
	//m_progWhole.SetPos(0);
	SetWholeProgPos(0);

	m_thrdData.uppercase = m_chkUppercase.GetCheck();

	m_calculateTime = 0.0;
	m_timer = SetTimer(1, 100, NULL);
	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_STATIC_TIME);
	CString cstrZero("0 ");
	cstrZero.Append(SECOND_STRING);
	pWnd->SetWindowText(cstrZero);
	pWnd = (CStatic*)GetDlgItem(IDC_STATIC_SPEED);
	pWnd->SetWindowText("");

	m_thrdData.stop = FALSE;
	m_hWorkThread = CreateThread(NULL, 0, md5_file, &m_thrdData, 0, &thredID);
	m_bHandleNull = FALSE;

}

void CFilesHashDlg::StopWorkingThread()
{
	if(m_thrdData.threadWorking)
	{
		m_thrdData.stop = TRUE;
	}
}

HBRUSH CFilesHashDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	if(pWnd->GetDlgCtrlID() == IDE_TXTMAIN)
	{
		pDC->SetBkMode(TRANSPARENT);


		hbr = m_bruEditBkg;
	}
	return hbr;
}

void CFilesHashDlg::ClearFilePaths()
{
	m_thrdData.fullPaths.clear();
}

void CFilesHashDlg::SetCtrls(BOOL working)
{
	if(working)
	{
		DragAcceptFiles(FALSE);
		m_btnOpen.EnableWindow(FALSE);
		m_btnStop.EnableWindow(TRUE);
		m_btnClr.EnableWindow(FALSE);
		m_btnCopy.EnableWindow(FALSE);
		m_btnFind.EnableWindow(FALSE);
		m_chkUppercase.EnableWindow(FALSE);
		GotoDlgCtrl(&m_btnStop);
	}
	else
	{
		m_btnOpen.EnableWindow(TRUE);
		m_btnStop.EnableWindow(FALSE);
		m_btnClr.EnableWindow(TRUE);
		m_btnCopy.EnableWindow(TRUE);
		m_btnFind.EnableWindow(TRUE);
		m_chkUppercase.EnableWindow(TRUE);
		GotoDlgCtrl(&m_btnOpen);
		DragAcceptFiles();
	}
}

void CFilesHashDlg::RefreshMainText()
{
	m_editMain.SetWindowText(m_thrdData.strAll);
	m_editMain.LineScroll(m_editMain.GetLineCount()); // ���ı����������β
}

void CFilesHashDlg::CalcSpeed(ULONGLONG tsize)
{
	KillTimer(m_timer);
	double speed;
	if(m_calculateTime > 0.1)
	{
		speed = tsize / m_calculateTime;
		CString speedStr,measure = "B/s";
		if((speed / 1024) > 1)
		{
			speed /= 1024;
			measure = "KB/s";
			if((speed / 1024) > 1)
			{
				speed /= 1024;
				measure = "MB/s";
			}
		}
		speedStr.Format("%4.2f ", speed);
		CStatic* pWnd = (CStatic*)GetDlgItem(IDC_STATIC_SPEED);
		speedStr.Append(measure);
		pWnd->SetWindowText(speedStr);
	}
	else
	{
		CStatic* pWnd = (CStatic*)GetDlgItem(IDC_STATIC_SPEED);
		pWnd->SetWindowText("");
	}
}

LRESULT CFilesHashDlg::OnThreadMsg(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case WP_WORKING:
		SetCtrls(TRUE);
		break;
	case WP_REFRESH_TEXT:
		RefreshMainText();
		break;
	case WP_PROG:
		m_prog.SetPos((int)lParam);
		break;
	case WP_PROG_WHOLE:
		SetWholeProgPos((int)lParam);
		break;
	case WP_FINISHED:
		// ֹͣ�������ʱ�� �����ȡ�ٶ�
		CalcSpeed(m_thrdData.totalSize);
		// ֹͣ�������ʱ�� �����ȡ�ٶ�

		// �������� - ��ʼ
		SetCtrls(FALSE);
		// �������� - ����	

		m_prog.SetPos(99);
		SetWholeProgPos(99);
		break;
	case WP_STOPPED:
		KillTimer(1);

		m_calculateTime = 0.0;
		CStatic* pWnd = (CStatic*)GetDlgItem(IDC_STATIC_TIME);
		pWnd->SetWindowText("");

		//�������� - ��ʼ
		SetCtrls(FALSE);
		//�������� - ����
			
		m_thrdData.strAll.Append("\r\n");
		m_thrdData.strAll.Append(MAINDLG_CALCU_TERMINAL);
		m_thrdData.strAll.Append("\r\n\r\n");
		m_editMain.SetWindowText(m_thrdData.strAll);
		m_editMain.LineScroll(m_editMain.GetLineCount()); // ���ı����������β

		m_prog.SetPos(0);
		//m_progWhole.SetPos(0);
		SetWholeProgPos(0);
		
		if(m_waitingExit)
		{
			PostMessage(WM_CLOSE);//OnCancel();
		}
		break;
	}

	return 0;
}

CString CFilesHashDlg::ResultFind(CString strFile, CString strHash)
{
	CString strResult(MAINDLG_FIND_IN_RESULT);
	strResult.Append(_T("\r\n"));
	strResult.Append(HASHVALUE_STRING);
	strResult.Append(_T(" "));
	strResult.Append(strHash);
	strResult.Append(_T("\r\n\r\n"));
	strResult.Append(MAINDLG_RESULT);
	strResult.Append(_T("\r\n\r\n"));

	strHash.MakeUpper();
	strFile.MakeLower();

	size_t count = 0;
	CString strPathLower;
	ResultList::iterator itr = m_thrdData.resultList.begin();
	for(; itr != m_thrdData.resultList.end(); ++itr)
	{
		strPathLower = itr->strPath;
		strPathLower.MakeLower();
		if(strPathLower.Find(strFile) >= 0 && 
			(itr->strMD5.Find(strHash) >= 0 ||
			itr->strSHA1.Find(strHash) >= 0 ||
			itr->strSHA256.Find(strHash) >= 0 ||
			itr->strCRC32.Find(strHash) >= 0 ))
		{
			++count;

			strResult.Append(FILENAME_STRING);
			strResult.Append(" ");
			strResult.Append(itr->strPath);
			strResult.Append("\r\n");
			strResult.Append(FILESIZE_STRING);
			strResult.Append(" ");
			strResult.AppendFormat("%I64u ", itr->ulSize);
			strResult.Append(BYTE_STRING);
			strResult.Append(ConvertSizeToCStr(itr->ulSize));
			strResult.Append("\r\n");
			strResult.Append(MODIFYTIME_STRING);
			strResult.Append(" ");
			strResult.Append(itr->strMDate);
			if(itr->strVersion.Compare(_T("")) != 0)
			{
				strResult.Append("\r\n");
				strResult.Append(VERSION_STRING);
				strResult.Append(" ");
				strResult.Append(itr->strVersion);
			}
			strResult.Append("\r\n");

			CString strMD5(itr->strMD5);
			CString strSHA1(itr->strSHA1);
			CString strSHA256(itr->strSHA256);
			CString strCRC32(itr->strCRC32);

			if(m_thrdData.uppercase = m_chkUppercase.GetCheck())
			{
				strResult.Append("MD5: ");
				strResult.Append(strMD5.MakeUpper());
				strResult.Append("\r\nSHA1: ");
				strResult.Append(strSHA1.MakeUpper());
				strResult.Append("\r\nSHA256: ");
				strResult.Append(strSHA256.MakeUpper());
				strResult.Append("\r\nCRC32: ");
				strResult.Append(strCRC32.MakeUpper());
				strResult.Append("\r\n\r\n");
			}
			else
			{
				strResult.Append("MD5: ");
				strResult.Append(strMD5.MakeLower());
				strResult.Append("\r\nSHA1: ");
				strResult.Append(strSHA1.MakeLower());
				strResult.Append("\r\nSHA256: ");
				strResult.Append(strSHA256.MakeLower());
				strResult.Append("\r\nCRC32: ");
				strResult.Append(strCRC32.MakeLower());
				strResult.Append("\r\n\r\n");
			}
		}
	}

	if(count == 0)
		strResult.Append(MAINDLG_NORESULT);

	return strResult;
}