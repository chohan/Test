import os, sys, time
import cx_Oracle as db


query = """
select * from table;
"""

con = db.connect("TNA/TNA//localhost:1521/ora")
print(con.version)
cur = con.cursor()
cur.execute(query)      # to execute single query
cur.executemany()       # to execute parameterized query

cur.fetchone()          # fetch one rwo
cur.fetchmany(n)        # fetch n number of rows
cur.fetchall()          # fetch all rows

con.commit()
con.rollback()

cur.close()
con.close()


