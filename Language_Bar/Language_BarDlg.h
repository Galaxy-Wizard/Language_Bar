
// Language_BarDlg.h : header file
//

#pragma once

// CLanguageBarDlg dialog
class CLanguageBarDlg : public CDialogEx
{
// Construction
public:
	CLanguageBarDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LANGUAGE_BAR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON Icon;

	CWinThread *TimerThread;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();

	DECLARE_MESSAGE_MAP()
public:

	LPARAM KeyboardLayout;
};
