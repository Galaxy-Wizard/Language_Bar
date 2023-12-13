
// Language_BarDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Language_Bar.h"
#include "Language_BarDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLanguageBarDlg dialog

UINT CDECL timer_thread(void* data);

CLanguageBarDlg::CLanguageBarDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LANGUAGE_BAR_DIALOG, pParent)
{
	TimerThread = nullptr;

	KeyboardLayout = 0x0000;

	Icon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLanguageBarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLanguageBarDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLanguageBarDlg message handlers

BOOL CLanguageBarDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(Icon, TRUE);			// Set big icon
	SetIcon(Icon, FALSE);			// Set small icon


	int x = 0;
	int y = 0;

	CLanguageBarApp* application = (CLanguageBarApp*)AfxGetApp();

	if (application != nullptr)
	{
		x = application->x;
		y = application->y;
	}

	SetWindowPos(nullptr, x, y, 0, 0, SWP_NOSIZE);

	TimerThread = AfxBeginThread(timer_thread, this);
	if (TimerThread != nullptr)
	{
		TimerThread->m_bAutoDelete = true;
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLanguageBarDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, Icon);
	}
	else
	{
		CPaintDC dc(this);

		HWND Window = ::GetForegroundWindow();
		DWORD Process;
		DWORD Thread = GetWindowThreadProcessId(Window, &Process);

		KeyboardLayout = ((LPARAM)GetKeyboardLayout(Thread)) & 0xFFFF;


		//KeyboardLayoutName = ((LPARAM)GetKeyboardLayout(0)) & 0xFFFF;

		LPARAM KeyboardLayoutNeutral = 0x0000;
		LPARAM KeyboardLayoutEnglish = 0x0409;
		LPARAM KeyboardLayoutRussian = 0x0419;

		CStringW LanguageName(L"Unknown language");
		CStringW LanguageCode;

		CStringW Neutral(L"Neutral");
		CStringW English(L"English");
		CStringW Russian(L"Russian");

		if (KeyboardLayout == KeyboardLayoutNeutral)
		{
			LanguageName = Neutral;
		}
		else
		{
			if (KeyboardLayout == KeyboardLayoutEnglish)
			{
				LanguageName = English;
			}
			else
			{
				if (KeyboardLayout == KeyboardLayoutRussian)
				{
					LanguageName = Russian;
				}
				else
				{
					;
				}
			}
		}

		LanguageCode.Format(L"Keyboard Layout code is 0x%.4x", KeyboardLayout);

		dc.TextOutW(0, 0, LanguageName);

		dc.TextOutW(0, 20, LanguageCode);

		CTime Time = CTime::GetCurrentTime();

		CStringW TimerThreadText = Time.Format(L"%d %B %Y %A %H:%M:%S");

		dc.TextOutW(0, 40, TimerThreadText);


		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLanguageBarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(Icon);
}



UINT CDECL timer_thread(void* data)
{
	while (data != nullptr)
	{
		Sleep(100);

		CLanguageBarDlg* LanguageBarDialog = (CLanguageBarDlg*)data;

		if (LanguageBarDialog != nullptr)
		{
			LanguageBarDialog->RedrawWindow();
		}
	}

	return 0;
}


void CLanguageBarDlg::OnClose()
{
	int x = 0;
	int y = 0;

	auto main_window = AfxGetMainWnd();

	if (main_window != nullptr)
	{
		RECT window_rectangle = {};
		main_window->GetWindowRect(&window_rectangle);

		x = window_rectangle.left;
		y = window_rectangle.top;
	}

	CLanguageBarApp* application = (CLanguageBarApp*)AfxGetApp();

	if (application != nullptr)
	{
		application->x = x;
		application->y = y;
	}

	CDialogEx::OnClose();
}
