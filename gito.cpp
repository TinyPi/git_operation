#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <Python.h>

#include "gito.h"
using namespace std;

void gito_help()
{
	cout << YELLOW "usage: gito [-h|p|P|a|s|auto|v]" NONE << endl << endl;
	cout << "\t-h," UNDER_LINE "--help" NONE << endl;
	cout << "\t\tshow this message" << endl;
	cout << "\t-p," UNDER_LINE "--push" NONE << endl;
	cout << "\t\tpush current branch changes to gerrit" << endl;
	cout << "\t-P," UNDER_LINE "--pull" NONE << endl;
	cout << "\t\tsync from remote commit of incurrent branch" << endl;
	cout << "\t-a," UNDER_LINE "--add" NONE << endl;
	cout << "\t\tgit add ." << endl;
	cout << "\t-s," UNDER_LINE "--status" NONE << endl;
	cout << "\t\tgit status ." << endl;
	cout << "\tauto," NONE << endl;
	cout << "\t\tgit add and push automatically" << endl;

	cout << "\t-v," UNDER_LINE "--version" NONE << endl;
	cout << "\t\tshow gito version" << endl;
}
void git_operation(int cmd, char* para)
{
    Py_Initialize();//初始化python

	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('/cktdisk/01-work/05-mysh/git_operation')");

	PyObject *pModule = NULL;
	PyObject *pFunc = NULL;
	PyObject *pArg = NULL;
    pModule = PyImport_ImportModule("git_operation");//引入模块

	switch (cmd)
	{
		case 0:
		pFunc = PyObject_GetAttrString(pModule, "git_op_version");//直接获取模块中的函数
		break;

		case 1:
		pFunc = PyObject_GetAttrString(pModule, "git_push");//直接获取模块中的函数
		break;

		case 2:
		pFunc = PyObject_GetAttrString(pModule, "git_pull");//直接获取模块中的函数
		break;

		case 3:
		pFunc = PyObject_GetAttrString(pModule, "git_add");//直接获取模块中的函数
		break;

		case 4:
		pFunc = PyObject_GetAttrString(pModule, "git_status");//直接获取模块中的函数
		break;

		case 5:
		pFunc = PyObject_GetAttrString(pModule, "git_auto");//直接获取模块中的函数
		break;

		default:
	    cout << "No python function found!!" << endl;
		break;
	}

	if(para)
		pArg = Py_BuildValue("(s)", para); //参数类型转换，传递一个字符串。将c/c++类型的字符串转换为python类型，元组中的python类型查看python文档
	if (pFunc)
    	PyEval_CallObject(pFunc, pArg); //调用直接获得的函数，并传递参数

    Py_Finalize(); //释放python
    return;
}

int main (int argc, char *argv[])
{
	int para = 0;
	if(( 1 == argc) || !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help" ))
	{
		goto show_help;
	}

	if( (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version")) && 2 == argc)
		git_operation(0, NULL);
	else if ( (!strcmp(argv[1], "-p") || !strcmp(argv[1], "--push")) && 2 == argc)
		git_operation(1, NULL);
	else if( (!strcmp(argv[1], "-P") || !strcmp(argv[1], "--pull")) && 2 == argc)
		git_operation(2, NULL);
	else if( (!strcmp(argv[1], "-a") || !strcmp(argv[1], "--add")) && 2 == argc)
		git_operation(3, NULL);
	else if( (!strcmp(argv[1], "-s") || !strcmp(argv[1], "--status")) && 2 == argc)
		git_operation(4, NULL);
	else if( !strcmp(argv[1], "auto") && 2 == argc)
		git_operation(5, NULL);
	else
		goto show_help;
	return 0;
show_help:
	gito_help();
	return 0;
}
