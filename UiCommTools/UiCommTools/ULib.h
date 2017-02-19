#pragma once

//define
#define lib_max(a,b)            (((a) > (b)) ? (a) : (b))
#define lib_min(a,b)            (((a) < (b)) ? (a) : (b))

#include <string>
#include <sstream>
#include <vector>
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

#include "resource.h"
#include "CommTools.h"
#include "CDShowMessage.h"

#define ULIB_FALSE		-1
#define ULIB_TRUE		0

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
