#pragma once
#ifndef __GENERICFUNCTIONS_H__
#define __GENERICFUNCTIONS_H__
//////////////////////////////////////////////////////////////////////////
BOOL RemoveLeadingPath(CString& path)
{
	//////////////////////////////////////////////////////////////////////////
	INT pos=path.GetLength();
	INT pos2=path.ReverseFind(L'\\');
	if(pos2==-1){
		pos2=path.ReverseFind(L'/');
		if(pos2==-1){
			pos2=-1;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	path=path.Right(pos-((pos2==-1)?0:pos2+1));
	//////////////////////////////////////////////////////////////////////////
	return TRUE;
	//////////////////////////////////////////////////////////////////////////

}
//////////////////////////////////////////////////////////////////////////
#endif//__GENERICFUNCTIONS_H__