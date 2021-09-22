// MainInterfaceDlg.cpp: 实现文件
//

#include "pch.h"
#include "2020619004温国亮.h"
#include "MainInterfaceDlg.h"
#include "afxdialogex.h"


// MainInterfaceDlg 对话框

IMPLEMENT_DYNAMIC(MainInterfaceDlg, CDialogEx)

MainInterfaceDlg::MainInterfaceDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_mainInterface, pParent)
	, uID(0)
	, uname(_T(""))
	, uage(0)
	, ubirthday(COleDateTime::GetCurrentTime())
{

}

MainInterfaceDlg::~MainInterfaceDlg()
{
}

void MainInterfaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, userlist);
	DDX_Text(pDX, IDC_ID, uID);
	DDX_Text(pDX, IDC_name, uname);
	DDX_Text(pDX, IDC_age, uage);
	DDX_DateTimeCtrl(pDX, IDC_birthday, ubirthday);
}


BEGIN_MESSAGE_MAP(MainInterfaceDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ADD, &MainInterfaceDlg::OnBnClickedAdd)
	ON_NOTIFY(NM_CLICK, IDC_LIST3, &MainInterfaceDlg::OnNMClickList3)
	ON_BN_CLICKED(IDC_DELETE, &MainInterfaceDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_ALTER, &MainInterfaceDlg::OnBnClickedAlter)
END_MESSAGE_MAP()


// MainInterfaceDlg 消息处理程序


BOOL MainInterfaceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	::SendMessage(userlist.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); //高亮
//////////为列表控件添加列//////////
	userlist.InsertColumn(0, _T("用户ID"), LVCFMT_LEFT, 60);
	userlist.InsertColumn(1, _T("用户名"), LVCFMT_LEFT, 100);
	userlist.InsertColumn(2, _T("年龄"), LVCFMT_LEFT, 60);
	userlist.InsertColumn(3, _T("生日"), LVCFMT_LEFT, 130);

	HRESULT hr;
	try
	{
		hr = adodbConnection.CreateInstance(_T("ADODB.Connection"));///创建Connection对象
		if (SUCCEEDED(hr))
		{
			hr = adodbConnection->Open("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=C:\\Users\\Bob\\test1.accdb", "", "", adModeUnknown);///连接数据库
		}
	}
	catch (_com_error e)///捕捉异常
	{
		CString errormessage;
		errormessage.Format(_T("连接数据库失败!\r\n错误信息:%s"), e.ErrorMessage());
		AfxMessageBox(errormessage);///显示错误信息
		return FALSE;
	}
	RefreshData();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void MainInterfaceDlg::RefreshData()
{
	
		int i = 0;
		userlist.DeleteAllItems();
		try
		{
			adodbRecordset.CreateInstance("ADODB.Recordset");
			adodbRecordset->Open("SELECT * FROM users", _variant_t((IDispatch*)adodbConnection, true), adOpenStatic, adLockOptimistic, adCmdText);
			//m_bSuccess = TRUE;
			while (!adodbRecordset->adoEOF)
			{
				vID = adodbRecordset->GetCollect("ID");
				vUsername = adodbRecordset->GetCollect("username");
				vOld = adodbRecordset->GetCollect("old");
				vBirthday = adodbRecordset->GetCollect("birthday");
				userlist.InsertItem(i, (_bstr_t)vID);
				userlist.SetItemText(i, 1, (_bstr_t)vUsername);
				userlist.SetItemText(i, 2, (_bstr_t)vOld);
				userlist.SetItemText(i, 3, (_bstr_t)vBirthday);

				adodbRecordset->MoveNext();
				i++;
			}
		}
		catch (_com_error e)///捕捉异常
		{
			MessageBox(_T("读取数据库失败!"));///显示错误信息
		}

}


void MainInterfaceDlg::OnBnClickedAdd()
{
	AddDate();// TODO: 在此添加控件通知处理程序代码
}


//添加函数
void MainInterfaceDlg::AddDate()
{
	// TODO: 在此处添加实现代码.
	if (UpdateData())
		if (uname.GetLength() > 0)
		{
			adodbRecordset->AddNew();
			if (!adodbRecordset->adoEOF)
			{
				vID = (long)uID;
				vUsername = uname;
				vOld = (long)uage;
				vBirthday = ubirthday;
				adodbRecordset->PutCollect("ID", vID);
				adodbRecordset->PutCollect("username", vUsername);
				adodbRecordset->PutCollect("old", vOld);
				adodbRecordset->PutCollect("birthday", vBirthday);
				adodbRecordset->Update();
				RefreshData();
			}
		}

}


//点击某一行将信息添加到编辑框中
void MainInterfaceDlg::OnNMClickList3(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	int m_nCurrentSel = userlist.GetSelectionMark();
	adodbRecordset->Move(m_nCurrentSel, _variant_t((long)adBookmarkFirst));
	vID = adodbRecordset->GetCollect("ID");
	vUsername = adodbRecordset->GetCollect("username");
	vOld = adodbRecordset->GetCollect("old");
	vBirthday = adodbRecordset->GetCollect("birthday");
	uID = vID.lVal;
	uname = (LPCTSTR)(_bstr_t)vUsername;
	uage = vOld.lVal;
	ubirthday = vBirthday;
	UpdateData(FALSE);

}

//删除函数
void MainInterfaceDlg::OnBnClickedDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strSQL;
	if (MessageBox(_T("确定删除该记录吗？"), _T("删除记录"), MB_OKCANCEL) == IDOK)
	{
		adodbRecordset.CreateInstance("ADODB.Recordset");
		strSQL.Format(_T("delete from users where username='%s'"), uname);
		adodbRecordset->Open((_bstr_t)strSQL, _variant_t((IDispatch*)adodbConnection, true), adOpenStatic, adLockOptimistic, adCmdText);

		RefreshData();
	}

}


//修改函数
void MainInterfaceDlg::OnBnClickedAlter()
{
	// TODO: 在此添加控件通知处理程序代码
	int m_nCurrentSel = -1;
	m_nCurrentSel = userlist.GetSelectionMark();
	if (m_nCurrentSel >= 0)
	{
		try
		{
			adodbRecordset ->MoveFirst();
			adodbRecordset->Move(long(m_nCurrentSel));
			if (MessageBox(_T("确定修改该记录吗？"), _T("修改记录"), MB_OKCANCEL) == IDOK)
			{
				adodbRecordset->Delete(adAffectCurrent);
				AddDate();
			}
		}
		catch (_com_error e)
		{
			MessageBox(_T("读取数据库失败！"));
		}
	}
	else
	{
		MessageBox(_T("请在列表控件中选择要修改的记录"));
	}
}
