#!/usr/bin/python
#############################################################################################################
#
# Desc: Checks system memory
# Auth: Salah Chohan
# Date: 25-Nov-2024
# Use: python ~/script/memory.py
# Pre-req: . ~/script/servers.sh
#
#############################################################################################################
import os, sys, inspect, subprocess, pipes, getpass
#import Popen, PIPE
#from time import sleep
import time
from datetime import datetime, timedelta
import util as U


def check_memory(env, servers):
  U.logInfo("@@ Calling " + inspect.stack()[0][3])

  insert_str = """INSERT INTO memory
                  (date, time, env, host, total, used, free, shared, cache, available, hugepage)
                  VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"""
  DT = datetime.now().strftime("%Y%m%d")
  TM = datetime.now().strftime("%H%M%S")

  fields = ["total", "used", "free", "shared", "buff/cache", "available", "hugepage"]
  U.dbOpen()
  U.dbDelete("delete from memory where Env='" + env + "'")
  for i in range(len(servers)):
    server = servers[i]
    U.logInfo("\n\n\n##### " + server + " #####")

    # Running command
    res = ['excp', 'excp', 'excp', 'excp', 'excp', 'excp', 'excp']
    #cmd = " free -h|grep Mem:|sed 's/Mem://g'"
    cmd = " \"echo -n \$(free -h|grep Mem:|sed 's/Mem://g'); echo -n ' '; cat /proc/sys/vm/nr_hugepages\" "
    COMMAND = U.SSH_COMMAND + server + cmd
    U.logDbug("Command: " + COMMAND)
    try:
      p = subprocess.Popen(COMMAND, shell=True, stderr=subprocess.STDOUT, stdout=subprocess.PIPE)
      time.sleep(0.1)
      res = p.communicate()[0].decode('utf-8').split()
      if len(res) != 7:
        RES = ['err', 'err', 'err', 'err', 'err', 'err', 'err']
    except Exception as ex:
      U.logExcp(repr(ex))
    U.logInfo("%s" %(res))
    server_short_name = server[0:3] + server[10:12] + server[7]
    values_tuple = (DT, TM, env, server, res[0], res[1], res[2], res[3], res[4], res[5], res[6])
    U.logDbug(str(values_tuple))
    U.dbInsert(insert_str, values_tuple)
  U.dbClose()


#############################################################################################################
if __name__ == '__main__':
  U.logInfB("@@@ Calling: %s" % sys.argv[0])

  # delete records for today as otherwise there will be uplication
  DATE = datetime.now().strftime("%Y%m%d")
  os.system("/usr/bin/sqlite3 U.DB_FILE \"delete from memory where date=" + DATE + ";\"")
  check_memory('dev', os.getenv('DEV_ALL').split())
  check_memory('prd', os.getenv('PRD_ALL').split())


