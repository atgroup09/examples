# @page SQLite: SELECT WHERE

# https://sqlitebrowser.org/
# https://habr.com/ru/articles/754400/

# Select rows from the database table by a tag-name and calc delta-timestamp
# python.exe 005-select-where-calc.py
# python.exe 005-select-where-calc.py <tag-name>

# delta-timestamp = current-timestamp - tag-timestamp

# Example - select all rows:
# python.exe 005-select-where-calc.py

# Example - select rows by tag-name 'A1':
# python.exe 005-select-where-calc.py A1

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
    cursor.execute("SELECT tag, CURRENT_TIMESTAMP AS ts_curr, ts, TIME(STRFTIME('%s',CURRENT_TIMESTAMP)-STRFTIME('%s',ts), 'unixepoch') as ts_delta, val FROM my_table");
else:
    # select data from the database-table by a tag-name
    cursor.execute("SELECT tag, CURRENT_TIMESTAMP AS ts_curr, ts, TIME(STRFTIME('%s',CURRENT_TIMESTAMP)-STRFTIME('%s',ts), 'unixepoch') as ts_delta, val FROM my_table WHERE tag=?", (sys.argv[1],));

# copy read rows into result-list
result = cursor.fetchall();

# print the result
for row in result:
    print(row);

# close connection
connection.close();
