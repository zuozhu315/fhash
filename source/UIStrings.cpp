#include "stdafx.h"
#include "UIStrings.h"

const TCHAR *SHELL_EXT_UUID = _T("{2B1ADB34-87ED-40E4-84E2-012D298F5370}");
const TCHAR *SHELL_EXT_REGESTRY = _T("*\\shellex\\ContextMenuHandlers\\fHashShellExt");
const TCHAR *SHELL_EXT_EXEPATH = _T("fHashPath");
const TCHAR *SHELL_EXT_ITEM_EN_US = _T("Hash with fHash");
const TCHAR *SHELL_EXT_ITEM_ZH_CN = _T("使用 fHash 计算哈希");

const TCHAR *CONTEXT_MENU_ITEM_EN_US = _T("Hash it with fHash");
const TCHAR *CONTEXT_MENU_ITEM_ZH_CN = _T("使用 fHash 计算哈希");
const TCHAR *CONTEXT_MENU_REGESTRY_ZH_CN = _T("*\\shell\\使用 fHash 计算哈希\\command");
const TCHAR *CONTEXT_MENU_REGESTRY_EN_US = _T("*\\shell\\Hash it with fHash\\command");

#ifdef ZH_CN
// Global Strings
const TCHAR *FILE_STRING = _T("文件");
const TCHAR *BYTE_STRING = _T("字节");
const TCHAR *HASHVALUE_STRING = _T("Hash 值:");
const TCHAR *FILENAME_STRING = _T("文件名:");
const TCHAR *FILESIZE_STRING = _T("文件大小:");
const TCHAR *MODIFYTIME_STRING = _T("修改日期:");
const TCHAR *VERSION_STRING = _T("版本:");
const TCHAR *SECOND_STRING = _T("秒");
const TCHAR *BUTTON_OK = _T("确定");
const TCHAR *BUTTON_CANCEL = _T("取消");

// Main Dialog Strings
const TCHAR *MAINDLG_INITINFO = _T("将文件拖入或点击打开，开始计算。");
const TCHAR *MAINDLG_WAITING_START = _T("准备开始计算。");
const TCHAR *MAINDLG_CONTEXT_INIT = _T("需要管理员权限");
const TCHAR *MAINDLG_ADD_SUCCEEDED = _T("添加成功");
const TCHAR *MAINDLG_ADD_FAILED = _T("添加失败");
const TCHAR *MAINDLG_REMOVE_SUCCEEDED = _T("移除成功");
const TCHAR *MAINDLG_REMOVE_FAILED = _T("移除失败");
const TCHAR *MAINDLG_REMOVE_CONTEXT_MENU = _T("移除右键菜单");
const TCHAR *MAINDLG_ADD_CONTEXT_MENU = _T("添加右键菜单");
const TCHAR *MAINDLG_CLEAR = _T("清除(&R)");
const TCHAR *MAINDLG_CLEAR_VERIFY = _T("清除验证(&R)");
const TCHAR *MAINDLG_CALCU_TERMINAL = _T("计算终止");
const TCHAR *MAINDLG_FIND_IN_RESULT = _T("在结果中搜索");
const TCHAR *MAINDLG_RESULT = _T("匹配的结果:");
const TCHAR *MAINDLG_NORESULT = _T("无匹配结果");
const TCHAR *MAINDLG_FILE_PROGRESS = _T("文件进度");
const TCHAR *MAINDLG_TOTAL_PROGRESS = _T("总体进度");
const TCHAR *MAINDLG_UPPER_HASH = _T("大写 Hash");
const TCHAR *MAINDLG_TIME_TITLE = _T("计算时间:");
const TCHAR *MAINDLG_OPEN = _T("打开(&O)...");
const TCHAR *MAINDLG_STOP = _T("停止(&S)");
const TCHAR *MAINDLG_COPY = _T("全部复制(&C)");
const TCHAR *MAINDLG_VERIFY = _T("验证(&V)");
const TCHAR *MAINDLG_ABOUT = _T("关于(&A)");
const TCHAR *MAINDLG_EXIT = _T("退出(&X)");

// Find Dialog Strings
const TCHAR *FINDDLG_TITLE = _T("验证");

// About Dialog Strings
const TCHAR *ABOUTDLG_TITLE = _T("关于 fHash");
const TCHAR *ABOUTDLG_INFO_TITLE = _T("fHash: 文件 Hash 计算器 ");
const TCHAR *ABOUTDLG_INFO_RIGHT = _T("Copyright (C) 2007-2014 SUN Junwen.");
const TCHAR *ABOUTDLG_INFO_MD5 = _T("MD5 算法是由 RSA Data Security, Inc.编写。Copyright (C) RSA Data Security, Inc.");
const TCHAR *ABOUTDLG_INFO_SHA256 = _T("SHA256 算法是由 Niels Moller 编写。Copyright (C) Niels Moller");
const TCHAR *ABOUTDLG_INFO_CRC32 = _T("CRC32 算法是由 Dominik Reichl 编写。Copyright (C) Dominik Reichl");
const TCHAR *ABOUTDLG_INFO_RIGHTDETAIL = _T("详细授权信息见开发者网站。");
const TCHAR *ABOUTDLG_INFO_OSTITLE = _T("当前操作系统:");
const TCHAR *ABOUTDLG_PROJECT_SITE = _T("<a>项目主页</a>");

// Shell ext
const TCHAR *SHELL_EXT_TOO_MANY_FILES = _T("选择的文件太多");

#else
// Global Strings
const TCHAR *FILE_STRING = _T("File");
const TCHAR *BYTE_STRING = _T("Byte(s)");
const TCHAR *HASHVALUE_STRING = _T("Hash:");
const TCHAR *FILENAME_STRING = _T("Name:");
const TCHAR *FILESIZE_STRING = _T("File Size:");
const TCHAR *MODIFYTIME_STRING = _T("Modified Date:");
const TCHAR *VERSION_STRING = _T("Version:");
const TCHAR *SECOND_STRING = _T("s");
const TCHAR *BUTTON_OK = _T("OK");
const TCHAR *BUTTON_CANCEL = _T("Cancel");

// Main Dialog Strings
const TCHAR *MAINDLG_INITINFO = _T("Drag files here or click open to start calculate.");
const TCHAR *MAINDLG_WAITING_START = _T("Prepare to start calculation.");
const TCHAR *MAINDLG_CONTEXT_INIT = _T("Need Administrator");
const TCHAR *MAINDLG_ADD_SUCCEEDED = _T("Add Succeeded");
const TCHAR *MAINDLG_ADD_FAILED = _T("Add Failed");
const TCHAR *MAINDLG_REMOVE_SUCCEEDED = _T("Remove Succeeded");
const TCHAR *MAINDLG_REMOVE_FAILED = _T("Remove Failed");
const TCHAR *MAINDLG_REMOVE_CONTEXT_MENU = _T("Remove Context Menu");
const TCHAR *MAINDLG_ADD_CONTEXT_MENU = _T("Add to Context Menu");
const TCHAR *MAINDLG_CLEAR = _T("Clea&r");
const TCHAR *MAINDLG_CLEAR_VERIFY = _T("Clea&r Verify");
const TCHAR *MAINDLG_CALCU_TERMINAL = _T("Terminated");
const TCHAR *MAINDLG_FIND_IN_RESULT = _T("Verify");
const TCHAR *MAINDLG_RESULT = _T("Result:");
const TCHAR *MAINDLG_NORESULT = _T("Nothing Found");
const TCHAR *MAINDLG_FILE_PROGRESS = _T("File");
const TCHAR *MAINDLG_TOTAL_PROGRESS = _T("Total");
const TCHAR *MAINDLG_UPPER_HASH = _T("Uppercase");
const TCHAR *MAINDLG_TIME_TITLE = _T("Time Used:");
const TCHAR *MAINDLG_OPEN = _T("&Open...");
const TCHAR *MAINDLG_STOP = _T("&Stop");
const TCHAR *MAINDLG_COPY = _T("&Copy");
const TCHAR *MAINDLG_VERIFY = _T("&Verify");
const TCHAR *MAINDLG_ABOUT = _T("&About");
const TCHAR *MAINDLG_EXIT = _T("E&xit");

// Find Dialog Strings
const TCHAR *FINDDLG_TITLE = _T("Verify");

// About Dialog Strings
const TCHAR *ABOUTDLG_TITLE = _T("About fHash");
const TCHAR *ABOUTDLG_INFO_TITLE = _T("fHash: Files' Hash Calculator ");
const TCHAR *ABOUTDLG_INFO_RIGHT = _T("Copyright (C) 2007-2014 SUN Junwen.");
const TCHAR *ABOUTDLG_INFO_MD5 = _T("MD5 Algorithm is writtend by RSA Data Security, Inc. Copyright (C) RSA Data Security, Inc.");
const TCHAR *ABOUTDLG_INFO_SHA256 = _T("SHA256 Algorithm is writtend by Niels Moller. Copyright (C) Niels Moller");
const TCHAR *ABOUTDLG_INFO_CRC32 = _T("CRC32 Algorithm is writtend by Dominik Reichl. Copyright (C) Dominik Reichl");
const TCHAR *ABOUTDLG_INFO_RIGHTDETAIL = _T("More details are on Project Site.");
const TCHAR *ABOUTDLG_INFO_OSTITLE = _T("Operating System:");
const TCHAR *ABOUTDLG_PROJECT_SITE = _T("<a>Project Home</a>");

// Shell ext
const TCHAR *SHELL_EXT_TOO_MANY_FILES = _T("Selected too many files");

#endif
