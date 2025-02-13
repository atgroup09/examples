# @page SQLite: SELECT WHERE LIMIT

# https://sqlitebrowser.org/
# https://habr.com/ru/articles/754400/

# Select latest data by 'ts' with virtual/calculated 'ts_delta'
# python.exe 006-select-where-calc-latest.py
# python.exe 006-select-where-calc-latest.py <tag-name>

# Example - select all rows:
# python.exe 006-select-where-calc-latest.py

# Example - select rows by tag-name 'A1':
# python.exe 006-select-where-calc-latest.py A1

import sys;
import sqlite3;
import time;

# set connection with DB
connection = sqlite3.connect("my_database.db");
cursor     = connection.cursor();

# test input arguments
# arg0 - the script name
# arg1 - tag/variable name
if len(sys.argv) < 2:
    # select all data from the database-table
    cursor.execute("SELECT res_main.tag AS tag, res_sub.val AS val, CURRENT_TIMESTAMP AS ts_curr, res_sub.ts AS ts, TIME(STRFTIME('%s',CURRENT_TIMESTAMP)-STRFTIME('%s',res_sub.ts), 'unixepoch') AS ts_delta FROM my_table AS res_main JOIN (SELECT tag, MAX(ts) AS ts, val FROM my_table GROUP BY tag) AS res_sub ON res_main.tag = res_sub.tag AND res_main.ts = res_sub.ts");
else:
    # select data from the database-table by a tag-name
    cursor.execute("SELECT res_main.tag AS tag, res_sub.val AS val, CURRENT_TIMESTAMP AS ts_curr, res_sub.ts AS ts, TIME(STRFTIME('%s',CURRENT_TIMESTAMP)-STRFTIME('%s',res_sub.ts), 'unixepoch') AS ts_delta FROM my_table AS res_main JOIN (SELECT tag, MAX(ts) AS ts, val FROM my_table GROUP BY tag) AS res_sub ON res_main.tag = res_sub.tag AND res_main.ts = res_sub.ts WHERE res_main.tag=?", (sys.argv[1],));

# copy read rows into result-list
result = cursor.fetchall();

# print the result
for row in result:
    print(row);

# close connection
connection.close();
