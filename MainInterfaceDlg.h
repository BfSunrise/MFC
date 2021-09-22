#pragma once


// MainInterfaceDlg 对话框

class MainInterfaceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MainInterfaceDlg)

public:
	MainInterfaceDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MainInterfaceDlg();
	_ConnectionPtr adodbConnection;
	_RecordsetPtr adodbRecordset;
	_variant_t vUsername, vBirthday, vID, vOld;


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_mainInterface };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl userlist;
	void RefreshData();
	UINT uID;
	CString uname;
	UINT uage;
	COleDateTime ubirthday;
	void AddDate();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnNMClickList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedAlter();
};
