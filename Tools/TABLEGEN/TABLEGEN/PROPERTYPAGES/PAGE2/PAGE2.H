#pragma once
#ifndef __PAGE2_H__
#define __PAGE2_H__
//////////////////////////////////////////////////////////////////////////
#include "../../HTL/HTLRESIZE.H"
#include "../../RESOURCEDEF.H"
//////////////////////////////////////////////////////////////////////////
#define GRNMAUTOLOADSAVE_REGISTRY_SECTION									L"GRNM AUTO LOAD SAVE"
#define GRNMAUTOLOADSAVE_REGISTRY_KEY										L"AUTO ON"
#define GRNMAUTOLOADSAVE_DEFAULT											0
//////////////////////////////////////////////////////////////////////////
extern DWORD TABLE_TYPE_CHANGED;
//////////////////////////////////////////////////////////////////////////
class CPropertyPage2 :
	public CResizablePropertyPageImpl<CPropertyPage2>
{

public:

	//////////////////////////////////////////////////////////////////////////
	UINT64&																m_TableTypeId;
	//////////////////////////////////////////////////////////////////////////

public:

	//////////////////////////////////////////////////////////////////////////
	typedef CPropertyPage2												thisClass;
	typedef CResizablePropertyPageImpl<CPropertyPage2>					baseClass;
	typedef CResizablePropertyPageImpl									baseClassNoParent;
	//////////////////////////////////////////////////////////////////////////
	enum { IDD = IDD_PAGE2 };
	//////////////////////////////////////////////////////////////////////////
	CPropertyPage2(UINT64& id, ATL::_U_STRINGorID title = (LPCTSTR)NULL, bool IsExterior = false, bool EnableDoubleBuffer = false);
	~CPropertyPage2(VOID);
	//////////////////////////////////////////////////////////////////////////
	BOOL OnSetActive(VOID);
	LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);
	BOOL OnQueryCancel(VOID);
	//////////////////////////////////////////////////////////////////////////
	BEGIN_MSG_MAP_EX(baseClassNoParent)
		MSG_WM_INITDIALOG(OnInitDialog)
		CHAIN_MSG_MAP(baseClass)
		CHAIN_MSG_MAP(CDialogResize<thisClass>)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()
	//////////////////////////////////////////////////////////////////////////
	BEGIN_DLGRESIZE_MAP_EX(thisClass)
		//////////////////////////////////////////////////////////////////////////
		DLGRESIZE_CONTROL_EX(IDC_STATIC_UNKNOWN_TYPE, DLSZ_SIZE_Y | DLSZ_SIZE_X)
		//////////////////////////////////////////////////////////////////////////
	END_DLGRESIZE_MAP_EX()
	//////////////////////////////////////////////////////////////////////////

};
//////////////////////////////////////////////////////////////////////////
#endif//__PAGE2_H__