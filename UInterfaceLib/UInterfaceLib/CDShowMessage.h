#pragma once
#include "afxdialogex.h"
// CDShowMessage dialog

class CDShowMessage : public CDialogEx
{
	DECLARE_DYNAMIC(CDShowMessage)

public:
	CDShowMessage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDShowMessage();

// Dialog Data
	enum { IDD = IDD_DLG_SHOWMESSAGE };

public:
	void ShowMessage(CString csMessage, int iMode);
	void SetTitle(CString csTitle)
	{
		this->m_csTitle = csTitle;
	}

	virtual BOOL OnInitDialog();
	afx_msg void OnMenuShowmessageClearn();
	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMenuCopy();
	afx_msg LRESULT ShowMessage(WPARAM wParam, LPARAM lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMenuMessageShowmessage();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	COwnerListBox m_List;
	CString m_csTitle;
	HMENU m_hMenu;
	CString m_csMessage;
	CFont	m_font;
	int m_iBGChange;

private:	
	void DealRMenu(CListBox *pList);
	void CopyMessage();
};
