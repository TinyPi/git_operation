#! /usr/bin/python

# -* - coding: UTF-8 -* -

import sys,os,re
import getopt
import chardet
import re
#from Tkinter import *

def git_push():
  '''push changes of current branch to gerrit'''
  cur_branch_f = os.popen('git symbolic-ref --short -q HEAD')
  current_branch = cur_branch_f.read()
  current_branch = current_branch.strip('\n')
  git_push_command = '%s%s%s%s' % ('git push origin ', current_branch, ':refs/for/', current_branch)
  print(git_push_command)

  os.system(git_push_command)
  cur_branch_f.close()

def git_pull():
  '''pull remote changes to lative'''
  os.system("git pull --rebase")

def git_add():
  '''git add'''
  os.system("git add .")

def git_status():
  '''git status'''
  os.system("git status .")

def git_auto():
  '''git push automatically'''
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
  '''show version'''
  print("*****************************")
  print("*      version:1.0          *")
  print("*          Tiny             *")
  print("*****************************")

def git_op(cmd,para):
  '''entry'''
  #print cmd,para
  if cmd == "p":
    git_push() 
  elif cmd == "P":
    git_pull()
  elif cmd == "a":
    git_add()
  elif cmd == "s":
    git_status()
  elif cmd == "A":
    git_auto()
  elif cmd == "v":
    git_op_version()
  else:
    print (cmd, " not suppot")
'''
    elif opt in ("-o", "--ofile"):
      outputfile = args
'''
def main():
  git_op('v',"100")
if __name__ == "__main__":
  '''git_op(sys.argv[1:])'''
  main()

