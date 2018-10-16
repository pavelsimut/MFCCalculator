// calc1MFCDlg.h : header file
//
#pragma once
// Ccalc1MFCDlg dialog
class Ccalc1MFCDlg : public CDialogEx
{
	bool isshiftpress = false;
	BOOL PreTranslateMessage(MSG * pMsg)
	{
		int X = (int)pMsg->wParam;
		if (pMsg->message == WM_KEYUP) {
			if (X == 16) { isshiftpress = false; }
		}
		if (pMsg->message == WM_KEYDOWN) {
			if (X == 16) { isshiftpress = true; }
		}
		if(isshiftpress&&pMsg->message == WM_KEYDOWN)
		{
			if (X == 187)
			plus();
			if (X == 56) { ori(); }
			if (X == 54) { pow(); }
		}
		else
		if (pMsg->message == WM_KEYDOWN) {
			if (X == 13) { Egalu(); }
			if (X == 189) { minus(); }
			if (X == 191) { diviziune(); }
			if (X == 8) { deleteInput(); }
			if (X == 46) { OnBnClickedbtdeletehisandimput(); }
			if (X == 190) { btEnterPunct(); }
			if (X == 187) { Egalu(); }
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
		return CDialog::PreTranslateMessage(pMsg);
	}
	int m_OkCount;
	char A[100];
	char B[1000];
	char C[1000];
	double primul;
	double doi;
// Construction
public:
	void binop(char i);
	Ccalc1MFCDlg(CWnd* pParent = nullptr);	// standard constructor
	void buttonNumeric(char i);
	void zerolainceput(char i);
	void afiscasuta(int marime, CString &casuta, char A[]);
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
	CString m_EchoText;
private:
	CString count2;
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
	afx_msg void plus();
	afx_msg void Egalu();
	afx_msg void ori();
	afx_msg void pow();
	afx_msg void sqr();
	afx_msg void sqrt();
	afx_msg void OnBnClickedbtdeletehisandimput();
	afx_msg void radiobasic();
	afx_msg void radioscientific();
	CButton btradical;
	afx_msg void deleteInput();
	afx_msg void minus();
	afx_msg void diviziune();
	afx_msg void invers();
	afx_msg void opus();
};
