#! /usr/bin/python

# -* - coding: UTF-8 -* -

import os,re
#from Tkinter import *

def git_push():
    """push changes of current branch to gerrit"""
    cur_branch_f = os.popen('git symbolic-ref --short -q HEAD')
    current_branch = cur_branch_f.read()
    current_branch = current_branch.strip('\n')
    git_push_command = '%s%s%s%s' % ('git push origin ', current_branch, ':refs/for/', current_branch)
    print(git_push_command)

    os.system(git_push_command)
    cur_branch_f.close()

def git_pull():
    """pull remote changes to lative"""
    os.system("git pull --rebase")

def git_add():
    """git add"""
    os.system("git add .")

def git_status():
    """git status"""
    os.system("git status .")

def git_auto():
    """git push automatically"""
    print("In git status progress....")
    git_s = os.popen('git status')
    modfied_list = git_s.read()
    git_s.close()

    no_change = "nothing to commit"
    if (modfied_list.find(no_change) == 0):
        print("No changes in your repository")
        return
    else:
        print("Pleas select which files you want to add")

    git_s.close()

def git_op_version():
    """show version"""
    print("*****************************")
    print("*      version:1.0          *")
    print("*          Tiny             *")
    print("*****************************")

