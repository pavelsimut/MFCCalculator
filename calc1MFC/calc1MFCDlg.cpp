// calc1MFCDlg.cpp : implementation file
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "calc1MFC.h"
#include "calc1MFCDlg.h"
#include "afxdialogex.h"
#include <string>
#include <sstream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Parser.h"
Ccalc1MFCDlg::Ccalc1MFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALC1MFC_DIALOG, pParent)
	, m_EchoText(_T(""))
	, count2(_T(""))	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void Ccalc1MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ECHO_AREA, m_EchoText);
	DDX_Text(pDX, IDC_ECHO_AREA1, count2);
	DDX_Control(pDX, IDC_BUTTON17, btradical);
}
BEGIN_MESSAGE_MAP(Ccalc1MFCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON4, &Ccalc1MFCDlg::btEnter1)
	ON_BN_CLICKED(IDC_BUTTON5, &Ccalc1MFCDlg::btEnter2)
	ON_BN_CLICKED(IDC_BUTTON10, &Ccalc1MFCDlg::btEnter3)
	ON_BN_CLICKED(IDC_BUTTON6, &Ccalc1MFCDlg::btEnter4)
	ON_BN_CLICKED(IDC_BUTTON7, &Ccalc1MFCDlg::btEnter5)
	ON_BN_CLICKED(IDC_BUTTON11, &Ccalc1MFCDlg::btEnter6)
	ON_BN_CLICKED(IDC_BUTTON8, &Ccalc1MFCDlg::btEnter7)
	ON_BN_CLICKED(IDC_BUTTON9, &Ccalc1MFCDlg::btEnter8)
	ON_BN_CLICKED(IDC_BUTTON12, &Ccalc1MFCDlg::btEnter9)
	ON_BN_CLICKED(IDC_BUTTON13, &Ccalc1MFCDlg::btEnter0)
	ON_BN_CLICKED(btdepunct, &Ccalc1MFCDlg::btEnterPunct)
	ON_BN_CLICKED(IDC_BUTTON2, &Ccalc1MFCDlg::plus)
	ON_BN_CLICKED(IDC_BUTTON3, &Ccalc1MFCDlg::Egalu)
	ON_BN_CLICKED(IDC_BUTTON14, &Ccalc1MFCDlg::ori)
	ON_BN_CLICKED(IDC_BUTTON15, &Ccalc1MFCDlg::pow)
	ON_BN_CLICKED(IDC_BUTTON16, &Ccalc1MFCDlg::sqr)
	ON_BN_CLICKED(IDC_BUTTON17, &Ccalc1MFCDlg::sqrt)
	ON_BN_CLICKED(btDeleteHisandImput, &Ccalc1MFCDlg::OnBnClickedbtdeletehisandimput)
	ON_BN_CLICKED(IDC_RADIO9, &Ccalc1MFCDlg::radiobasic)
	ON_BN_CLICKED(IDC_RADIO10, &Ccalc1MFCDlg::radioscientific)
	ON_BN_CLICKED(IDC_BUTTON18, &Ccalc1MFCDlg::deleteInput)
	ON_BN_CLICKED(btDeleteHisandImput2, &Ccalc1MFCDlg::minus)
	ON_BN_CLICKED(IDC_BUTTON19, &Ccalc1MFCDlg::diviziune)
	ON_BN_CLICKED(IDC_BUTTON20, &Ccalc1MFCDlg::invers)
	ON_BN_CLICKED(btDeleteHisandImput3, &Ccalc1MFCDlg::opus)
END_MESSAGE_MAP()
bool basicbool=true;
// Ccalc1MFCDlg message handlers
BOOL Ccalc1MFCDlg::OnInitDialog()
{
	CButton* pBtn1 = (CButton*)GetDlgItem(IDC_RADIO10);
	pBtn1->SetCheck(1);// uncheck it
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	// TODO: Add extra initialization here
	m_OkCount = 0;
	return TRUE;  // return TRUE  unless you set the focus to a control
}
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void Ccalc1MFCDlg::OnPaint()
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
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Ccalc1MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
bool lastwasop = false;
bool b = false;
void Ccalc1MFCDlg::zerolainceput(char i)
{
	if (m_OkCount == 0&&b==false)
	{
		A[m_OkCount++] = '0';
		buttonNumeric('.');
		b = true;
	}
	else if (b == false)
	{
		buttonNumeric(i);
		b = true;
	}
}
void Ccalc1MFCDlg::afiscasuta(int marime, CString &casuta, char A[])
{
	std::ostringstream ss;
	CString temp;
	for (int j = 0; j < marime; j++)
	{
			ss << A[j];
	}
	std::string s(ss.str());
	temp = (CString)(s.c_str());
	casuta.Format(_T("%s"), (LPCTSTR)temp);
	UpdateData(FALSE);
}
bool dupegal = false;
void Ccalc1MFCDlg::buttonNumeric(char i)
{
	dupegal = false;
	if (b == false || i != '.')
	{
		A[m_OkCount++] = i; lastwasop = false;
	}
	afiscasuta(m_OkCount,count2,A);
}
void Ccalc1MFCDlg::btEnter1()
{
	buttonNumeric('1');
}
void Ccalc1MFCDlg::btEnter2()
{
	buttonNumeric('2');
}
void Ccalc1MFCDlg::btEnter3()
{
	buttonNumeric('3');
}
void Ccalc1MFCDlg::btEnter4()
{
	buttonNumeric('4');
}
void Ccalc1MFCDlg::btEnter5()
{
	buttonNumeric('5');
}
void Ccalc1MFCDlg::btEnter6()
{
	buttonNumeric('6');
}
void Ccalc1MFCDlg::btEnter7()
{
	buttonNumeric('7');
}
void Ccalc1MFCDlg::btEnter8()
{
	buttonNumeric('8');
}
void Ccalc1MFCDlg::btEnter9()
{
	buttonNumeric('9');
}
void Ccalc1MFCDlg::btEnter0()
{
	if(m_OkCount==0)
		zerolainceput('.');
	else
	buttonNumeric('0');
}
void Ccalc1MFCDlg::btEnterPunct()
{
	zerolainceput('.');
}
int bcount = 0;
int ccount = 0;
bool rad = false;
int newlinecount = 0;
void Ccalc1MFCDlg::binop(char i)
{
	if (A[m_OkCount - 1] == '.')
		m_OkCount--;
	if (bcount > 0||m_OkCount>0||rad==true||i=='=')
	{
		afiscasuta(m_OkCount, count2, "");
			rad = false;
		b = false;
		for (int j = 0; j < m_OkCount; j++)
		{
			B[bcount++] = A[j];
		}
		if (m_OkCount + bcount > 39)
		{
			C[ccount++] = '\n';
			newlinecount++;
		}
		for (int k = 0; k < m_OkCount; k++)
		{
			C[ccount++] = A[k];
		}
		if (lastwasop&&i!='r')
		{
			B[bcount - 1] = i;
			C[ccount - 1] = i;
		}
		else if(i != 'r')
		{
			lastwasop = true;
			B[bcount++] = i;
			C[ccount++] = i;
		}
		afiscasuta(ccount, m_EchoText, C);
		m_OkCount = 0;
		count2.Format(_T(""));
	}
}
void Ccalc1MFCDlg::plus()
{
	binop('+');
}
char buf[100];
void Ccalc1MFCDlg::Egalu()
{
	if (A[m_OkCount - 1] == '.')
		m_OkCount--;
	if (dupegal == false&&m_OkCount>0)
	{
		binop('=');
		lastwasop = false;
		Parser p(B, bcount);
		memset(buf, 0, sizeof buf);
		sprintf_s(buf, 100, "%.10f", p.parse());
		for (int j = 0; j < strlen(buf); j++)
		{
			C[ccount++] = buf[j];
		}
		while (C[ccount - 1] == '0')
			ccount--;
		if (C[ccount - 1] == '.')
			ccount--;
		C[ccount++] = '\n';
		newlinecount++;
		int i = 0;
		if (newlinecount > 8)
		{
			char* pos = strchr(C, '\n');
			int z = pos - C;
			strcpy(C, pos+1);
			ccount -= z+1 ;
		}
		afiscasuta(ccount, m_EchoText, C);
		bcount = 0;
		m_OkCount = 0;
		dupegal = true;
	}
}
void Ccalc1MFCDlg::ori()
{
	binop('*');
}
void Ccalc1MFCDlg::pow()
{
	binop('^');
}
void Ccalc1MFCDlg::sqr()
{
	if (m_OkCount > 0)
	{
		binop('^');
		buttonNumeric('2');
	}
}
void Ccalc1MFCDlg::sqrt()
{
	if (m_OkCount > 0)
	{
		binop('^');
		buttonNumeric('0');
		zerolainceput('.');
		buttonNumeric('5');
	}
}
void Ccalc1MFCDlg::OnBnClickedbtdeletehisandimput()
{
	newlinecount = 0;
	m_OkCount = 0;
	bcount = 0;
	ccount = 0;
	afiscasuta(ccount, m_EchoText, C);
	afiscasuta(ccount, count2, C);
	dupegal = false;
	rad = false;
	lastwasop = false;
	b = false;
}
void Ccalc1MFCDlg::deleteInput()
{
	m_OkCount = 0;
	afiscasuta(m_OkCount, count2, A);
	b = false;
	rad = false;
}
void Ccalc1MFCDlg::radiobasic()
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_RADIO9);
	pBtn->SetCheck(1);
	CButton* pBtn1 = (CButton*)GetDlgItem(IDC_RADIO10);
	pBtn1->SetCheck(0);
	this->GetDlgItem(IDC_BUTTON17)->ShowWindow(SW_HIDE);
	this->GetDlgItem(IDC_BUTTON15)->ShowWindow(SW_HIDE);
	this->GetDlgItem(IDC_BUTTON16)->ShowWindow(SW_HIDE);
	this->GetDlgItem(IDC_BUTTON20)->ShowWindow(SW_HIDE);
	const char* foo1 = "Calculator - Basic";
	SetWindowText((LPCTSTR)foo1);
}
void Ccalc1MFCDlg::radioscientific()
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_RADIO9);
	pBtn->SetCheck(0);
	CButton* pBtn1 = (CButton*)GetDlgItem(IDC_RADIO10);
	pBtn1->SetCheck(1);
	this->GetDlgItem(IDC_BUTTON17)->ShowWindow(SW_SHOW);
	this->GetDlgItem(IDC_BUTTON15)->ShowWindow(SW_SHOW);
	this->GetDlgItem(IDC_BUTTON16)->ShowWindow(SW_SHOW);
	this->GetDlgItem(IDC_BUTTON20)->ShowWindow(SW_SHOW);
	const char* foo = "Calculator - Scientific";
	SetWindowText((LPCTSTR)foo);
}
void Ccalc1MFCDlg::minus()
{
	binop('-');
}
void Ccalc1MFCDlg::diviziune()
{
	binop('/');
}
void Ccalc1MFCDlg::invers()
{
	if (m_OkCount > 0)
	{
		char Atemp[100];
		Atemp[0] = '1';
		Atemp[1] = '/';
		for (int i = 2; i < m_OkCount + 2; i++)
			Atemp[i] = A[i - 2];
		for (int j = 0; j < m_OkCount + 2; j++)
			A[j] = Atemp[j];
		m_OkCount += 2;
		binop('r');
		rad = true;
	}
}
void Ccalc1MFCDlg::opus()
{
	if (m_OkCount > 0)
	{
		char Atemp[100];
		if (A[0] != '-')
		{
			char Atemp[100];
			Atemp[0] = '-';
			for (int i = 1; i < m_OkCount + 1; i++)
				Atemp[i] = A[i - 1];
			for (int j = 0; j < m_OkCount + 1; j++)
				A[j] = Atemp[j];
			m_OkCount += 1;
		}
		else
		{
			for (int j = 1; j < m_OkCount; j++)
				A[j - 1] = A[j];
			m_OkCount--;
		}
	}
	else
		A[m_OkCount++] = '-';
	afiscasuta(m_OkCount, count2, A);
}
