#pragma once

//define
#define lib_max(a,b)            (((a) > (b)) ? (a) : (b))
#define lib_min(a,b)            (((a) < (b)) ? (a) : (b))

#include <string>
#include <sstream>
using namespace std;

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

#include <boost/shared_ptr.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include <highgui.h>
#include <cv.h>
#include <cvaux.h>

extern "C"
{
#include "sqlite/sqlite3.h"
};
#include "sqlite/CppSQLite3U.h"
#pragma comment(lib,"sqlite/sqlite3.lib") 

#ifdef _DEBUG
#pragma  comment(lib, "opencv_highgui248d.lib")
#pragma  comment(lib, "opencv_core248d.lib")
#pragma  comment(lib, "opencv_imgproc248d.lib")
#else
#pragma  comment(lib, "opencv_highgui248.lib")
#pragma  comment(lib, "opencv_core248.lib")
#pragma  comment(lib, "opencv_imgproc248.lib")
#endif

#include "resource.h"
#include "CommTools.h"
#include "CvvImage.h"
#include "COwnerPicSta.h"
#include "COwnerListBox.h"
#include "COwnerListCtrl.h"

#include "CDShowMessage.h"

#include "CCamDealData.h"
#include "CCaptureVideo.h"

#define ULIB_FALSE		-1
#define ULIB_TRUE		0

#define ULIB_DB_TYPE_SQLITE						1
#define ULIB_DB_TYPE_MYSQL						2
#define ULIB_DB_TYPE_SQLSERVICE			3
#define ULIB_DB_TYPE_MONGODB				4
#include "CDBbase.h"
#include "CSqliteCtrl.h"

//excel
#include "excel/CWorksheets.h"  
#include "excel/CWorksheet.h"  
#include "excel/CWorkBooks.h"  
#include "excel/CWorkBook.h"  
#include "excel/CRange.h"
#include "excel/CApplication.h"
#include "CExportExcel.h"

//获取物理地址
#include <winsock2.h>
#include <iphlpapi.h>
#pragma comment(lib, "IPHLPAPI.lib")

//更新
#include "CCProjectInfo.h"
#include "CCFtpCtrl.h"
#include "CCSoftUpdate.h"

//配置文件
#include<boost/filesystem.hpp>  
#include "CCFileXml.h"
#include "CCFileIni.h"
#include "CConfigBase.h"

#define COM_BUF_LEN 256
//串口操作
#include "SerialTools/CSerialCom.h"
#include "SerialTools/CCmdStation.h"
