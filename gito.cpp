#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <getopt.h>

extern "C"
{
#include "Python.h"
}

#include "gito.h"

#define MAX_PY_ENV_PATH_LEN 1028
#ifdef CURPATH
#define MAX_PATH_LEN 256
char script_file_path[MAX_PATH_LEN] = CURPATH;
#endif

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
	cout << "\t-A," UNDER_LINE "--auto" NONE << endl;
	cout << "\t\tgit add and push automatically" << endl;

	cout << "\t-v," UNDER_LINE "--version" NONE << endl;
	cout << "\t\tshow gito version" << endl;
}

int python_initialize()
{
    Py_Initialize();//init python
	if(!Py_IsInitialized()) {
		cout << "Py initial fail!!!";
		return -1;
	}
}

void python_finalize()
{
	Py_Finalize(); //release python
}

void git_operation(char cmd, char* para)
{
	char pyenv[MAX_PY_ENV_PATH_LEN];
	int ret = python_initialize();
	if (-1 == ret) {
		cout << "[ERROR] Python env init error" << endl;
		return;
	}

	PyRun_SimpleString("import sys");
	sprintf(pyenv,"sys.path.append('%s')",script_file_path);
	PyRun_SimpleString(pyenv); //Add the path of python file to system path
	//PyRun_SimpleString("print sys.path");
	PyObject* pName = PyString_FromString("git_operation");
    PyObject* pModule = PyImport_Import(pName);//Import git_operation module
	if(!pModule) {
		cout << "pModule is NULL" << endl;
		python_finalize();
		return;
	}
	PyObject* pFunc = PyObject_GetAttrString(pModule, "git_op");//get the function name in module
	if(!pFunc || !PyCallable_Check(pFunc)) {
		cout << "pFunc is NULL" << endl;
		python_finalize();
		return;
	}
	PyObject* pArg = NULL;
	if(para) {
		pArg = Py_BuildValue("(c,s)", cmd, para); //change c++ parameter type to python
	} else {
		pArg = Py_BuildValue("c,s", cmd, "NULL"); //change c++ parameter type to python
	}

	//PyObject* pArg = Py_BuildValue("(c,s)", cmd, para); //change c++ parameter type to python
	if(!pArg) {
		cout << "pArg is NULL" << endl;
		python_finalize();
		return;
	}
   	PyEval_CallObject(pFunc, pArg); //call function in python and transfer parameter

    python_finalize();
    return;
}

#define MAX_PARA 64
static char short_para[MAX_PARA]="aAhpAsv";
static struct option long_para[] = {
	{ "auto", 0, NULL, 'A' },
	{ "push", 0, NULL, 'p' },
	{ "pull", 0, NULL, 'P' },
	{ "add", 0, NULL, 'a' },
	{ "version", 2, NULL, 'v' },
	{ "help", 0, NULL, 'h' },
	{ 0, 0, 0, 0},
};

int main (int argc, char *argv[])
{
	int opt;
	if( 1 == argc) {
		goto show_help;
	}

	while(-1 != (opt = getopt_long(argc, argv, short_para, long_para, NULL))) {
		switch (opt) {
			case 'h':
				goto show_help;
			default:
				git_operation(char(opt), optarg);
				break;
		}
	}
	return 0;
show_help:
	gito_help();
	return 0;
}
