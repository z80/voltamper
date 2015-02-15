// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef HELLO_CLIENT_DLG_H
#define HELLO_CLIENT_DLG_H

#include "Hello.h"
#include <IceE/IceE.h>

#pragma once

class CHelloClientDlg : public CDialog
{
public:

    CHelloClientDlg(const Ice::CommunicatorPtr&, CWnd* = NULL);

    enum { IDD = IDD_HELLOCLIENT_DIALOG };

protected:

    virtual void DoDataExchange(CDataExchange*);    // DDX/DDV support

protected:

    Ice::CommunicatorPtr _communicator;
    CEdit* _host;
    CComboBox* _mode;
    CButton* _timeout;
    CButton* _delay;
    CStatic* _status;
    Demo::HelloPrx _proxy;
    Demo::HelloPrx _currentProxy;
    int _currentMode;
    std::string _hostname;
    bool _useTimeout;
    HICON _hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnClose();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnSayHello();
    afx_msg void OnFlush();
    afx_msg void OnShutdown();
    afx_msg LRESULT OnAMIException(WPARAM, LPARAM);
    afx_msg LRESULT OnAMISayHelloResponse(WPARAM, LPARAM);
    afx_msg LRESULT OnAMISayHelloSent(WPARAM, LPARAM);
    afx_msg LRESULT OnAMIFlushBatchRequestsSent(WPARAM, LPARAM);
    afx_msg LRESULT OnAMIShutdownSent(WPARAM, LPARAM);
    DECLARE_MESSAGE_MAP()

    void updateProxy();
    void handleException(const IceUtil::Exception&);

private:

    HANDLE _connection;
};

#endif
