// mem.h
//
//////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


void *AllocPtr(int nSize);
void *ReAllocPtr(void *p, int nSize);
void FreePtr(void *p);
