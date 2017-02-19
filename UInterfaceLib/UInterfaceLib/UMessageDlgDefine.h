#pragma once
/************************************************* 
Copyright:forour
Author: 
Date:2015-06-28
Description:消息窗口操作接口 
**************************************************/  


/************************************************* 
Function:				InitMessageDlg
Description:		初始化消息显示对话框
Input:					void 
Return:					int：成功后返回1，否则为错误
Others:					NULL
*************************************************/  
extern "C" __declspec(dllimport) int  InitMessageDlg();

/************************************************* 
Function:				ShowWindow
Description:		窗口显示操作
Input:					int： SW_HIDE,SW_NORMAL,SW_SHOW,详见对话框ShowWindow参数
Return:					int：成功后返回1，否则为错误
Others:					NULL
*************************************************/  
extern "C" __declspec(dllimport) int ShowMessageWindow(int iShowMode);

/************************************************* 
Function:				ShowMessage
Description:		消息显示操作
Input:					CString：要显示的消息内容  
								int：显示模式，区别在于颜色
										SHOW_MESSAGE_COLOR_SYS：系统消息
										SHOW_MESSAGE_COLOR_SEND ： 发送消息
										SHOW_MESSAGE_COLOR_RECV：接收消息
Return:					int：成功后返回1，否则为错误
Others:					NULL
*************************************************/  
extern "C" __declspec(dllimport) int ShowMessage(CString csMessage, int iMode);

/************************************************* 
Function:				ShowMessage
Description:		消息窗口移动
Input:					CRect：要显示的范围  
Return:					int：成功后返回1，否则为错误
Others:					NULL
*************************************************/  
extern "C" __declspec(dllimport) int MoveMessageWindow(CRect rect);