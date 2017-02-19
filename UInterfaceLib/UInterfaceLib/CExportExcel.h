#pragma once
class  CExportExcel
{
public:
	CExportExcel(void);
	~CExportExcel(void);

public :
	void SetExtraNum(int iNum);
	void SetExportMode(int iMode);

	void InitExcel();
	void ShowExcel(CFormatData clsData);
	void Realease();
	void InitExportToExcel(CFormatData clsData);
	
protected:
	CApplication m_exlApp;  
	CWorkbook m_exlBook;  
	CWorkbooks m_exlBooks;  
	CWorksheet m_exlSheet;  
	CWorksheets m_exlSheets;  
	CRange m_exlRge;
	CRange m_usedRange;

	int m_iExtraSheetsNum;
	int m_iMode;

private:
};


