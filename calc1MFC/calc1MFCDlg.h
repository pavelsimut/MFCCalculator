// calc1MFCDlg.h : header file
//
#pragma once
// Ccalc1MFCDlg dialog
class Ccalc1MFCDlg : public CDialogEx
{
	bool isshiftpress = false;
	bool buttonpressed=false;
	BOOL Ccalc1MFCDlg::PreTranslateMessage(MSG* pMsg)
	{
		BOOL Result = FALSE;

		int X = (int)pMsg->wParam;
		if (pMsg->message == WM_KEYUP) {
			if (X == 16) { isshiftpress = false; }
		}
		if (pMsg->message == WM_KEYDOWN) {
			if (X == 16) { isshiftpress = true; }
		}
		if(isshiftpress&&pMsg->message == WM_KEYDOWN)
		{
			Result = TRUE;
			if (X == 187)
			btPlus();
			if (X == 56) { btOri(); }
			if (X == 54) { btPow(); }
		}
		else
		if (pMsg->message == WM_KEYDOWN) {
			Result = TRUE;
			if (X == 13) { btEgal(); }
			if (X == 189) { btMinus(); }
			if (X == 191) { btDiviziune(); }
			if (X == 8) { btDeleteInput(); }
			if (X == 46) { btdeleteHistoryAndImput(); }
			if (X == 190) { btEnterPunct(); }
			if (X == 187) { btEgal(); }
			if (X == 48) { btEnter0(); }
			if (X == 49) { btEnter1(); }
			if (X == 50) { btEnter2(); }
			if (X == 51) { btEnter3(); }
			if (X == 52) { btEnter4(); }
			if (X == 53) { btEnter5(); }
			if (X == 54) { btEnter6(); }
			if (X == 55) { btEnter7(); }
			if (X == 56) { btEnter8(); }
			if (X == 57) { btEnter9(); }
		}
		if(Result==false)
		return CDialog::PreTranslateMessage(pMsg);
		return Result;
	}
	int imputSize;
	int equationSize = 0;
	int historySize = 0;
	const static int maxImputSize=100;
	const static int maxHistorySize = 1000;
	const static int maxLineSize = 39;
	char rezultatEquatie[maxImputSize];
	char currentImput[maxImputSize];
	char currentEquation[maxHistorySize];
	char currentHistory[maxHistorySize];
// Construction
public:
	void binOp(char i);
	Ccalc1MFCDlg(CWnd* pParent = nullptr);	// standard constructor
	void btNumeric(char i);
	void caseZeroLaInceput(char i);
	void afiseazaInStaticText(int marime, CString &casuta, char A[]);
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALC1MFC_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString casutaHistory;
private:
	CString casutaImput;
public:
	afx_msg void btEnter1();
	afx_msg void btEnter2();
	afx_msg void btEnter3();
	afx_msg void btEnter4();
	afx_msg void btEnter5();
	afx_msg void btEnter6();
	afx_msg void btEnter7();
	afx_msg void btEnter8();
	afx_msg void btEnter9();
	afx_msg void btEnter0();
	afx_msg void btEnterPunct();
	afx_msg void btPlus();
	afx_msg void btEgal();
	afx_msg void btOri();
	afx_msg void btPow();
	afx_msg void btSqr();
	afx_msg void btSqrt();
	afx_msg void btdeleteHistoryAndImput();
	afx_msg void radioBasic();
	afx_msg void radioScientific();
	CButton btradical;
	afx_msg void btDeleteInput();
	afx_msg void btMinus();
	afx_msg void btDiviziune();
	afx_msg void btInvers();
	afx_msg void btOpus();
};
