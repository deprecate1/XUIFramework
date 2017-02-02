//--------------------------------------------------------------------------//
//                                                                          //
// Using the property control in a view                                     //
//                                                                          //
// 1) Create a new default CView inherited class                            //
// 2) Change baseclass of your new class from CView to EPropView            //
//        Dont forget to change base class in IMPLEMENT_DYNCREATE() etc..   //
// 3) Make sure your project links to propertylib                           //
//        Set dependency on the propertylib for your project, and linker    //
//        will be able to find the .lib                                     //
//--------------------------------------------------------------------------//

#ifndef EPROPVIEW_H
#define EPROPVIEW_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class EProperty;
class IPropertyHost;

#include "EPropCtrl.h"

class EPropView : public CView , public IPropertyChangeListener
{

protected:

	EPropCtrl m_PropCtrl;

	EPropView();

public:
		
	virtual ~EPropView();
	virtual void GetIDRange( int& nID_PROPERTY_RANGE_BEG , int& nID_PROPERTY_RANGE_END );

	DECLARE_DYNCREATE(EPropView);

	//{{AFX_VIRTUAL(EPropView)
	public:
	virtual void OnDraw(CDC* pDC);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(EPropView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP();

public:

	void SetPropertyHost( IPropertyHost* pHost );
	void RefreshHostList();

	//
	// IPropertyChangeListener
	//

	// This is called when user has edited a property, and someone needs
	// to be notified on the change (eg other views). the default
	// implementation updates all views.
	virtual void PropertyChanged();

};

//{{AFX_INSERT_LOCATION}}

#endif
