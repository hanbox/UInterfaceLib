#pragma  once

//define
#define lib_max(a,b)            (((a) > (b)) ? (a) : (b))
#define lib_min(a,b)            (((a) < (b)) ? (a) : (b))

#define  VIDEO_WIDTH		640
#define  VIDEO_HEIGHT		480

#define FORMAT_HEX			1
#define FORMAT_ASC			2
#define FORMAT_HEX_SPACE	3
#define FORMAT_ASC_SPACE	4

enum ULIB_RETURN
{
	ULIB_RETURN_FALSE			= -1,
	ULIB_RETURN_TRUE			= 0,
	ULIB_RETURN_PARAMETER_NULL 	= 2,
};

#define ULIB_FALSE		-1
#define ULIB_TRUE		0

#define ULIB_DB_TYPE_SQLITE						1
#define ULIB_DB_TYPE_MYSQL						2
#define ULIB_DB_TYPE_SQLSERVICE					3
#define ULIB_DB_TYPE_MONGODB					4

#include <string>
using namespace std;
#include <vector>
#include <map>

#include "UInterface/UOwnCtrlDefine.h"
#include "UInterface/UDataBase.h"
#include "UInterface/UCommonToolsDefine.h"
#pragma comment(lib, "UInterface/UInterfaceLib.lib")


/*************************************************
Author：			Liuxin
Description：	软件更新
Input:			【CString】：软件路径
Return：			【CString】：返回信息
**************************************************/
extern "C" __declspec(dllimport) CString  UpdateCheck(CString csFilePath);


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
extern "C" __declspec(dllimport) int  ShowMessageWindow(int iShowMode);

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
#define SHOW_MESSAGE_COLOR_SYS		0
#define SHOW_MESSAGE_COLOR_SEND		1
#define SHOW_MESSAGE_COLOR_RECV		2
extern "C" __declspec(dllimport) int  ShowMessage(CString csMessage, int iMode);

/************************************************* 
Function:				ShowMessage
Description:		消息窗口移动
Input:					CRect：要显示的范围  
Return:					int：成功后返回1，否则为错误
Others:					NULL
*************************************************/  
extern "C" __declspec(dllimport) int  MoveMessageWindow(CRect rect);