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
	, casutaHistory(_T(""))
	, casutaImput(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void Ccalc1MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ECHO_AREA, casutaHistory);
	DDX_Text(pDX, IDC_ECHO_AREA1, casutaImput);
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
	ON_BN_CLICKED(IDC_BUTTON2, &Ccalc1MFCDlg::btPlus)
	ON_BN_CLICKED(IDC_BUTTON3, &Ccalc1MFCDlg::btEgal)
	ON_BN_CLICKED(IDC_BUTTON14, &Ccalc1MFCDlg::btOri)
	ON_BN_CLICKED(IDC_BUTTON15, &Ccalc1MFCDlg::btPow)
	ON_BN_CLICKED(IDC_BUTTON16, &Ccalc1MFCDlg::btSqr)
	ON_BN_CLICKED(IDC_BUTTON17, &Ccalc1MFCDlg::btSqrt)
	ON_BN_CLICKED(btDeleteHisandImput, &Ccalc1MFCDlg::btdeleteHistoryAndImput)
	ON_BN_CLICKED(IDC_RADIO9, &Ccalc1MFCDlg::radioBasic)
	ON_BN_CLICKED(IDC_RADIO10, &Ccalc1MFCDlg::radioScientific)
	ON_BN_CLICKED(IDC_BUTTON18, &Ccalc1MFCDlg::btDeleteInput)
	ON_BN_CLICKED(btDeleteHisandImput2, &Ccalc1MFCDlg::btMinus)
	ON_BN_CLICKED(IDC_BUTTON19, &Ccalc1MFCDlg::btDiviziune)
	ON_BN_CLICKED(IDC_BUTTON20, &Ccalc1MFCDlg::btInvers)
	ON_BN_CLICKED(btDeleteHisandImput3, &Ccalc1MFCDlg::btOpus)
END_MESSAGE_MAP()
bool basicbool = true;
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
	imputSize = 0;
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
bool lastWasInvers = false;
bool lastWasOp = false;
bool lastWasPunct = false;
bool lastWasEgal = false;
bool lastWasRadical = false;
int newLineCount = 0;

void Ccalc1MFCDlg::caseZeroLaInceput(char i)
{
	if (imputSize == 0 && lastWasPunct == false)
	{
		currentImput[imputSize++] = '0';
		btNumeric('.');
		lastWasPunct = true;
	}
	else if (lastWasPunct == false)
	{
		btNumeric(i);
		lastWasPunct = true;
	}
}

void Ccalc1MFCDlg::afiseazaInStaticText(int marime, CString &casuta, char string[])
{
	std::ostringstream ss;
	CString temp;
	for (int j = 0; j < marime; j++)
	{
		ss << string[j];
	}
	std::string s(ss.str());
	temp = (CString)(s.c_str());
	casuta.Format(_T("%s"), (LPCTSTR)temp);
	UpdateData(FALSE);
}

void Ccalc1MFCDlg::btNumeric(char i)
{
	lastWasEgal = false;
	if ((lastWasPunct == false || i != '.') && (imputSize+1 < maxImputSize))
	{
		currentImput[imputSize++] = i; lastWasOp = false;
	}
	afiseazaInStaticText(imputSize, casutaImput, currentImput);
}

void Ccalc1MFCDlg::btEnter1()
{
	btNumeric('1');
}

void Ccalc1MFCDlg::btEnter2()
{
	btNumeric('2');
}

void Ccalc1MFCDlg::btEnter3()
{
	btNumeric('3');
}

void Ccalc1MFCDlg::btEnter4()
{
	btNumeric('4');
}

void Ccalc1MFCDlg::btEnter5()
{
	btNumeric('5');
}

void Ccalc1MFCDlg::btEnter6()
{
	btNumeric('6');
}

void Ccalc1MFCDlg::btEnter7()
{
	btNumeric('7');
}

void Ccalc1MFCDlg::btEnter8()
{
	btNumeric('8');
}

void Ccalc1MFCDlg::btEnter9()
{
	btNumeric('9');
}

void Ccalc1MFCDlg::btEnter0()
{
	if (imputSize == 0)
		caseZeroLaInceput('.');
	else
		btNumeric('0');
}

void Ccalc1MFCDlg::btEnterPunct()
{
	caseZeroLaInceput('.');
}

void Ccalc1MFCDlg::binOp(char i)
{
	if (imputSize + historySize < maxHistorySize)
	{
		if (currentImput[imputSize - 1] == '.')
			imputSize--;
		if (equationSize > 0 || imputSize > 0 || lastWasRadical == true || i == '=')
		{
			afiseazaInStaticText(imputSize, casutaImput, "");
			lastWasRadical = false;
			lastWasPunct = false;
			for (int j = 0; j < imputSize; j++)
			{
				currentEquation[equationSize++] = currentImput[j];
			}
			if (imputSize + equationSize > maxLineSize)
			{
				currentHistory[historySize++] = '\n';
				newLineCount++;
			}
			for (int k = 0; k < imputSize; k++)
			{
				currentHistory[historySize++] = currentImput[k];
			}
			if (lastWasOp&&i != 'r')
			{
				currentEquation[equationSize - 1] = i;
				currentHistory[historySize - 1] = i;
			}
			else if (i != 'r')
			{
				lastWasOp = true;
				currentEquation[equationSize++] = i;
				currentHistory[historySize++] = i;
			}
			afiseazaInStaticText(historySize, casutaHistory, currentHistory);
			imputSize = 0;
			casutaImput.Format(_T(""));
		}
	}
}

void Ccalc1MFCDlg::btPlus()
{
	binOp('+');
}


void Ccalc1MFCDlg::btEgal()
{
	if (imputSize + historySize < maxHistorySize)
	{
		if (currentImput[imputSize - 1] == '.')
			imputSize--;
		if (lastWasEgal == false && (imputSize > 0 || lastWasInvers == true))
		{
			binOp('=');
			lastWasOp = false;
			Parser p(currentEquation, equationSize);
			memset(rezultatEquatie, 0, sizeof rezultatEquatie);
			double rezultatEqDouble = p.parse();

			sprintf_s(rezultatEquatie, maxImputSize, "%.10f", rezultatEqDouble);
			for (int j = 0; j < strlen(rezultatEquatie); j++)
			{
				currentHistory[historySize++] = rezultatEquatie[j];
			}
			while (currentHistory[historySize - 1] == '0')
				historySize--;
			if (currentHistory[historySize - 1] == '.')
				historySize--;
			currentHistory[historySize++] = '\n';
			newLineCount++;
			if (newLineCount > 8)
			{
				char* pos = strchr(currentHistory, '\n');
				int z = pos - currentHistory;
				strcpy(currentHistory, pos + 1);
				historySize -= z + 1;
			}
			afiseazaInStaticText(historySize, casutaHistory, currentHistory);
			equationSize = 0;
			imputSize = 0;
			lastWasEgal = true;
			lastWasInvers = false;
		}
	}
}

void Ccalc1MFCDlg::btOri()
{
	binOp('*');
}

void Ccalc1MFCDlg::btPow()
{
	binOp('^');
}

void Ccalc1MFCDlg::btSqr()
{
	if (imputSize > 0)
	{
		binOp('^');
		btNumeric('2');
	}
}

void Ccalc1MFCDlg::btSqrt()
{
	if (imputSize > 0)
	{
		binOp('^');
		btNumeric('0');
		caseZeroLaInceput('.');
		btNumeric('5');
	}
}

void Ccalc1MFCDlg::btdeleteHistoryAndImput()
{
	newLineCount = 0;
	imputSize = 0;
	equationSize = 0;
	historySize = 0;
	afiseazaInStaticText(historySize, casutaHistory, currentHistory);
	afiseazaInStaticText(historySize, casutaImput, currentHistory);
	lastWasEgal = false;
	lastWasRadical = false;
	lastWasOp = false;
	lastWasPunct = false;
	lastWasInvers = false;
}

void Ccalc1MFCDlg::btDeleteInput()
{
	imputSize = 0;
	afiseazaInStaticText(imputSize, casutaImput, currentImput);
	lastWasPunct = false;
	lastWasRadical = false;
}

void Ccalc1MFCDlg::radioBasic()
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

void Ccalc1MFCDlg::radioScientific()
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

void Ccalc1MFCDlg::btMinus()
{
	binOp('-');
}

void Ccalc1MFCDlg::btDiviziune()
{
	binOp('/');
}

void Ccalc1MFCDlg::btInvers()
{
	if (imputSize > 0)
	{
		lastWasInvers = true;
		char temporaryImput[maxImputSize];
		temporaryImput[0] = '1';
		temporaryImput[1] = '/';
		for (int i = 2; i < imputSize + 2; i++)
			temporaryImput[i] = currentImput[i - 2];
		for (int j = 0; j < imputSize + 2; j++)
			currentImput[j] = temporaryImput[j];
		imputSize += 2;
		binOp('r');
		lastWasRadical = true;
	}
}

void Ccalc1MFCDlg::btOpus()
{
	if (imputSize > 0)
	{
		char temporaryImput[maxImputSize];
		if (currentImput[0] != '-')
		{
			temporaryImput[0] = '-';
			for (int i = 1; i < imputSize + 1; i++)
				temporaryImput[i] = currentImput[i - 1];
			for (int j = 0; j < imputSize + 1; j++)
				currentImput[j] = temporaryImput[j];
			imputSize += 1;
		}
		else
		{
			for (int j = 1; j < imputSize; j++)
				currentImput[j - 1] = currentImput[j];
			imputSize--;
		}
	}
	else
		currentImput[imputSize++] = '-';
	afiseazaInStaticText(imputSize, casutaImput, currentImput);
}
