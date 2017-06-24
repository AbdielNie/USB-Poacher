// FDiskThiefDlg.h : header file
//

#if !defined(AFX_FDISKTHIEFDLG_H__C2F2D2C7_E9B5_4C6C_A9CF_554FCA8AD884__INCLUDED_)
#define AFX_FDISKTHIEFDLG_H__C2F2D2C7_E9B5_4C6C_A9CF_554FCA8AD884__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFDiskThiefDlg dialog

class CFDiskThiefDlg : public CDialog
{
// Construction
public:
	BOOL IsRun;
	void CopyFile(CString dir);
	CString FindFdisk();
	CString m_NewFdisk;
	CString m_OldFdisk;
	CString m_Path;
	CFDiskThiefDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFDiskThiefDlg)
	enum { IDD = IDD_FDISKTHIEF_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFDiskThiefDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFDiskThiefDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonOpen();
	afx_msg void OnButtonHide();
	afx_msg void OnHotKey(WPARAM wp,LPARAM lp);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonStart();
	afx_msg void OnButtonStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FDISKTHIEFDLG_H__C2F2D2C7_E9B5_4C6C_A9CF_554FCA8AD884__INCLUDED_)
